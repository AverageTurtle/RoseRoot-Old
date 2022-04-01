speed = 4
rotspeed = 2
vel = Vec2.new()
rot = 0
pos = Vec3.new()
pos = rself.position
rself:SetGravityScale(0)
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
	if Input.IsKeyPressed(Key.e) then
		rot = rot - (rotspeed* ts)
	end
	if Input.IsKeyPressed(Key.q) then
		rot = rot + (rotspeed* ts)
	end
	rself.rotation.z = rot
	rself.position = pos
	rself:SetLinearVelocity(vel)
	rself:SetAnglearVelocity(0) 
end