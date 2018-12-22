
active_lerps = {}
next_lerp_id = 0

function AddLerp(obj, var_name, target_val, t, onfinish)
  local cur_val = obj[var_name]

  lerp = {
    obj = obj,
    var_name = var_name,
    delta = 1 / t,
    start = cur_val,
    target = target_val,
    t = 0,
    onfinish = onfinish
  }

  local lerp_id = next_lerp_id
  active_lerps[lerp_id] = lerp
  next_lerp_id = next_lerp_id + 1

  return lerp_id
end

function ClearLerp(obj, var_name)
  for k, v in pairs(active_lerps) do
    if v.obj == obj and v.var_name == var_name then
      active_lerps[k] = nil
      return
    end
  end
end

function ProcessLerps(dt)
  for k, v in pairs(active_lerps) do
    local elem = v.obj
    local cur_val = elem[v.var_name]
    v.t = v.t + v.delta * dt

    if v.t >= 1 then
      elem[v.var_name] = v.target

      if v.onfinish ~= nil then
        v.onfinish()
      end

      active_lerps[k] = nil
    else
      v.obj[v.var_name] = (v.target * v.t) + (v.start * (1 - v.t))
    end
  end
end