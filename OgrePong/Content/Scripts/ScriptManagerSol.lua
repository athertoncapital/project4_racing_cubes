-- Our quick and dirty script system.  We maintain a global array of scripts.  
-- The Ogre Frame Listener calls our ScriptManagerThink function, which in turn
-- calls the Think methods on all active scripts.

-- A more robust scripting system would have an eaiser way of indexing scripts, and
-- activating / deactivating / removing scripts.  This is just quick and dirty enough
-- to work for now.


-- Our table of running scripts
GlobalScripts = { }

-- Method to add a script.
function addScript(script)
    table.insert(GlobalScripts, script)
end

function ScriptManagerThink(time)
    for i, v in ipairs(GlobalScripts) do	   
	   if v:Active() then
			v:Think(time)
	   end
    end
end


-- Handy print method.  Use print instead of debugOutput, to avoid crashes 
-- for nil values and non-string values.
function print(x)
    debugOutput(tostring(x))
end



----------------------------
-- Script "Class" -- pretty straighforward for now, scripts have a Think method
-- and an Active method by default, and nothing else
-----------------------------
Script = {}

function Script.Active(this)
	return this.isActive
end

function Script.Think(this, time)

end

function Script.create()
	local s  = {}
	s.isActive = true	
	s.Active = Script.Active;
	s.Think = Script.Think
	return s
end


-- A function to create a seeker object.  We create an object, and then create a script to manipulate it
function createSeeker(name, x, y, z) 
	if name == nil then
		print("createSeeker:  name required!")
		return
	end
	x = x or 0
	y = y or 0
	z = z or 0
	
	print("Creating Seeker: ID = " .. name .. ",  Location: " .. tostring(x) .. ", " .. tostring(y) .. ",  " .. tostring(z))
	createObject("MyCube.mesh", name)
	setPosition(name, x, y, z)
	local seekerScript = Script.create()
	seekerScript.Think = function(this, time)
		local pX, pY, pZ = getPosition("player")
		local mX, mY, mZ =  getPosition(name)
		local deltaX, deltaY, deltaZ = pX-mX, pY-mY, pZ - mZ
		setVelocity(name, deltaX , deltaY, deltaZ)
	end	
	addScript(seekerScript)
end


--  Note that the above script uses closures to keep track of the variable name.  Instead, we could have 
--  used something more akin to instance variables:
-- function createSeeker(name, x, y, z) 
	-- x = x or 0
	-- y = y or 0
	-- z = z or 0
	
	-- print("Creating Seeker: ID = " .. name .. ",  Location: " .. tostring(x) .. ", " .. tostring(y) .. ",  " .. tostring(z))
	-- createObject("MyCube.mesh", name)
	-- setPosition(name, x, y, z)
	-- seekerScript = Script.create()
	-- seekerScript.objectName = name
	-- seekerScript.Think = function(this, time)
		-- local pX, pY, pZ = getPosition("player")
		-- local mX, mY, mZ =  getPosition(name)
		-- local deltaX, deltaY, deltaZ = pX-mX, pY-mY, pZ - mZ
		-- setVelocity(this.objectName, deltaX , deltaY, deltaZ)
	-- end	
	-- addScript(seekerScript)
-- end


function length(x,y,z)
	return math.sqrt(x*x + y*y + z*z)
end

-- A function to create a shy object.  Shy objects want to always be a given distance away
--  from a target.  If no target is given, the target defaults to "player".  If no distance
--  is given, the distance defaults to 30
function createShyObject(name, distance, target, x, y, z)
	if name == nil then 
	    print("Name Required")
		return
	end
	target = target or "player"
	distance = distance or 30
	x = x or 0
	y = y or 0
	z = z or 0
	
	print("Creating shy: ID = " .. name .. ", Target = " .. target .. ",  Location: " .. tostring(x) .. ", " .. tostring(y) .. ",  " .. tostring(z))

	createObject("MyCube.mesh", name)
	setPosition(name, x, y, z)
	local shyScript = Script.create()
	shyScript.Think = function(this, time)
		local pX, pY, pZ = getPosition(target)
		local mX, mY, mZ =  getPosition(name)
		local deltaX, deltaY, deltaZ = pX-mX, pY-mY, pZ - mZ
		if (length(deltaX, deltaY, deltaZ) < distance ) then
			setVelocity(name, -deltaX , -deltaY, -deltaZ)		
		else
			setVelocity(name, deltaX , deltaY, deltaZ)		
		
		end
	end	
	addScript(shyScript)
	
	
end






