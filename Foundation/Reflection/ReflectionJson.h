
#include "Foundation\Common.h"
#include "Foundation\Json\Json.h"


template <typename T, typename std::enable_if<
  std::is_arithmetic<T>::value ||
  std::is_same<T, RString>::value
>::type * = 0>
void DecodeJson(T & value, Json & j)
{
  value = j;
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
void DecodeJson(T & value, Json & j)
{
  member_json_decoder_visitor decoder(j);
  VisitEach(value, decoder);
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_enum
>::type * = 0>
void DecodeJson(T & value, Json & j)
{
  value = T::_from_string(j.get<std::string>().data());
}

template <class T>
void DecodeJson(RList<T> & value, Json & j)
{
  value.clear();
  value.reserve(j.size());
  for (auto t : j)
  {
    T new_val;
    DecodeJson(new_val, t);

    value.push_back(new_val);
  }
}

template <class T>
void DecodeJson(RSparseList<T> & value, Json & j)
{
  value.Clear();
  value.Reserve(j.size());
  for (auto t : j)
  {
    T new_val;
    DecodeJson(new_val, t);

    value.PushBack(new_val);
  }
}

template <class T>
void DecodeJson(RMergeList<T> & value, Json & j)
{
  value.Clear();
  value.Reserve(j.size());
  for (Json::iterator it = j.begin(); it != j.end(); ++it)
  {
    T new_val;
    DecodeJson(new_val, it.value());

    int index = std::stoi(it.key());
    value.InsertAt(new_val, index);
  }
}

template <class T>
void DecodeJson(RDictionary<T> & value, Json & j)
{
  value.clear();
  value.reserve(j.size());
  for (Json::iterator it = j.begin(); it != j.end(); it++)
  {
    T new_val;
    DecodeJson(new_val, it.value());

    value[it.value().get<RHash>()] = new_val;
  }
}

struct member_json_decoder_visitor
{
  member_json_decoder_visitor(Json & value)
    : m_Value(value)
  {

  }

  template <class FieldData, class MemType>
  void operator()(FieldData f)
  {
    DecodeJson(f.get(), m_Value[f.name()]);
  }

public:
  Json & m_Value;
};

template <typename T, typename std::enable_if<
  std::is_arithmetic<T>::value ||
  std::is_same<T, RString>::value
>::type * = 0>
Json EncodeJson(const T & value)
{
  return value;
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
Json EncodeJson(const T & value)
{
  Json j_value;
  member_json_encoder_visitor encoder(j_value);

  VisitEach(value, encoder);
  return j_value;
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_enum
>::type * = 0>
Json EncodeJson(const T & value)
{
  return value._to_string();
}

template <class T>
Json EncodeJson(const RList<T> & value)
{
  Json j_value;
  for (auto t : value)
  {
    j_value.push_back(EncodeJson(t));
  }

  return j_value;
}

template <class T>
Json EncodeJson(const RSparseList<T> & value)
{
  Json j_value;
  for (auto t : value)
  {
    j_value.push_back(EncodeJson(t.second));
  }

  return j_value;
}

template <class T>
Json EncodeJson(const RMergeList<T> & value)
{
  Json j_value;
  for (auto t : value)
  {
    j_value[std::to_string(t.first)] = EncodeJson(t.second);
  }

  return j_value;
}

template <class T>
Json EncodeJson(const RDictionary<T> & value)
{
  Json j_value;
  for (std::pair<RHash, T> t : value)
  {
    j_value[t.first] = t.second;
  }

  return j_value;
}

struct member_json_encoder_visitor
{
  member_json_encoder_visitor(Json & value)
    : m_Value(value)
  {
  
  }

  template <class FieldData, class MemType>
  void operator()(FieldData f)
  {
    m_Value[f.name()] = EncodeJson(f.get());
  }

public:
  Json & m_Value;
};
