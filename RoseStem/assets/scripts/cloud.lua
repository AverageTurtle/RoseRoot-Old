pos = Vec3.new()

--rself is how you access the entity the script is attached to!
pos = rself.position
--use log not print for Rose!
log("Hello from lua")

--Called Before the first frame
function Init()
	log("Init")
end

--Called Every Frame
function Update(ts)
	pos.x = pos.x + (ts*0.5)
	rself.position = pos
    if pos.x > 14 then
        pos.x = -14
    end
    
	log(rself.name..": "..rself.position.x)
end
