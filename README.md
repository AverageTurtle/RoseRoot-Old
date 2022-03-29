# Project Rose
A easy to use Game engine and Editor!<br>

<img src="https://media.discordapp.net/attachments/918981027538567278/957977029440069662/Rose.png" alt="drawing" width="200"/>

**Features**
-
Easy to learn LUA Scripting (Rose Stem)
```lua
pos = Vec2.new()
size = Vec2.new()
color = CreateColor(1, 1, 0, 1)

size.x = 1
size.y = 1

log("Hello from lua")

function Init()
	log("Init")
end

function Update(ts)
	pos.x = 0;
	Renderer2D.DrawSimpleQuad(pos, size, color)
end
```

Fast clean C++ API (Rose Root)
```C++
//In your layer update function
RoseRoot::RenderCommand::SetClearColor({0.2, 0.0, 0.2, 1.0});
RoseRoot::RenderCommand::Clear();
RoseRoot::Renderer2D::BeginScene(m_EditorCamera);

//Draws a white quad at the center of the screen
Renderer2D::DrawQuad({ 0.f, 0.f }, { 1.f, 1.f }, { 1.f, 1.f, 1.f, 1.f });

RoseRoot::Renderer2D::EndScene();```