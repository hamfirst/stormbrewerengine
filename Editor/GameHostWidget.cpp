
#include "GameHostWidget.h"
#include "EditorContainer.h"



GameHostWidget::GameHostWidget(EditorContainer * editor, int number_of_clients, QWidget *parent) :
  QWidget(parent),
  m_Editor(editor)
{
  m_Layout = std::make_unique<QGridLayout>();

  for (int index = 0; index < number_of_clients; ++index)
  {
    m_Clients.emplace_back(std::make_unique<GameClientWidget>(editor, index, false, this));
  }

  m_Server = std::make_unique<GameServerWidget>(this);

  if (number_of_clients == 1)
  {
    m_Layout->setColumnStretch(0, 2);
    m_Layout->setColumnStretch(1, 1);

    m_Layout->addWidget(m_Clients[0].get(), 0, 0);
    m_Layout->addWidget(m_Server.get(), 0, 1);
  }
  else
  {
    int cols = (number_of_clients + 1) / 2;
    for (int index = 0; index < cols; ++index)
    {
      m_Layout->setColumnStretch(index, 2);
    }

    for (int index = 0; index < number_of_clients; ++index)
    {
      m_Layout->addWidget(m_Clients[index].get(), index / 2, index % 2);
    }

    m_Layout->addWidget(m_Server.get(), 0, cols, 2, 1);
  }

  setMinimumSize(1066, 600);
  setLayout(m_Layout.get());
}

void GameHostWidget::closeEvent(QCloseEvent * ev)
{
  m_Editor->NotifyClientWindowClosed(this);
}

void GameHostWidget::resizeEvent(QResizeEvent * ev)
{
  
}