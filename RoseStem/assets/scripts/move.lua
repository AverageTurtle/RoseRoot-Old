speed = 3
pos = Vec3.new()
log(Key.left)
function Update(ts)
	if Input.IsKeyPressed(Key.right) then
		pos.x = pos.x + (speed* ts)
	end
	if Input.IsKeyPressed(Key.left) then
		pos.x = pos.x - (speed* ts)
	end
	if Input.IsKeyPressed(Key.up) then
		pos.y = pos.y + (speed* ts)
	end
	if Input.IsKeyPressed(Key.down) then
		pos.y = pos.y - (speed* ts)
	end
	rself.position = pos
end