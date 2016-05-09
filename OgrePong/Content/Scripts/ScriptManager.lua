-- Our quick and dirty script system.  We maintain a global array of scripts.  
-- The Ogre Frame Listener calls our ScriptManagerThink function, which in turn
-- calls the Think methods on all active scripts.

-- A more robust scripting system would have an eaiser way of indexing scripts, and
-- activating / deactivating / removing scripts.  This is just quick and dirty enough
-- to work for now.


-- Our table of running scripts
GlobalScripts = { }

-- Method to add a script.

function addScript(script, name)
    if name == nil then
		table.insert(GlobalScripts, script)
	else
		GlobalScripts[name] = script
	end
end

function removeScript(name)
	GlobalScripts[name] = nil
end

function ScriptManagerThink(time)
    for i, v in pairs(GlobalScripts) do	   
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









