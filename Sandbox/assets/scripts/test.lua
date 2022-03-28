time = -6;
log("Hello from lua")

function Init()
	log("Init")
	vec2 = Vec2.new()
	vec2.x = 5
	vec2.y = 3
	log(vec2.x..","..vec2.y)
end

function Update(ts)
	time = time + (ts*0.6)
	if time > 6 then
		time = -6
	end
	
	DrawSimpleQuad2D(time, 0, 1, 1, 0.9, 1, 0, 1)
end
