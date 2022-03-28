
time = 0;
color = 0;
log("Hello from lua Also")

function Init()
	log("Init 2")
end

function Update(ts)
	time = time + (ts*1.0)
	color = color + (ts*0.1)

	if time > 4 then
		time = -4
	end

	if color > 1 then
		color = 0
	end
	
	DrawSimpleQuad2D(0, time, 1, 1, color, 0.2, 0.8, 1)
end