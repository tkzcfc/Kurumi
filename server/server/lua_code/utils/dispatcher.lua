local dispatcher = class("dispatcher")

function dispatcher:ctor()
	self.msgCall = {}
end

function dispatcher:register(msgKey, func, priority)

	if msgKey == nil or msgKey == "" or type(func) ~= "function" then
		return
	end

	local calls = self.msgCall[msgKey]
	if calls == nil then
		calls = {}
		self.msgCall[msgKey] = calls
	end

	local needsort = false

	if priority == nil then
		if #calls < 1 then
			priority = 0
		else
			priority = calls[#calls].priority + 1
		end
	else
		for k, v in pairs(calls) do
			if v.priority == priority then
				print("dispatcher: priority is wrongful!!!")
				assert(0)
				return
			end
		end
		needsort = true
	end

	for k,v in pairs(calls) do
		if v.func == func then
			print("dispatcher: cur func already registered")
			return
		end
	end

	local newcall = {func = func, priority = priority}
	table.insert(calls, newcall)

	if needsort then
		table.sort(calls, function(a, b) return a.priority < b.priority end)
	end
end

function dispatcher:unRegister(msgKey, func)

	if type(func) ~= "function" then
		return
	end

	if msgKey == nil then
		for _, calls in pairs(self.msgCall) do
			for k, v in pairs(calls) do
				if v.func == func then
					table.remove(calls, k)
					return
				end
			end
		end
	else
		local calls = self.msgCall[msgKey]

		if calls ~= nil then
			for k, v in pairs(calls) do
				if v.func == func then
					table.remove(calls, k)
					return
				end
			end
		end
	end
end

function dispatcher:call(msgKey, ...)
	local calls = self.msgCall[msgKey]

	if calls ~= nil then
		for k, v in pairs(calls) do
			if v.func(...) == true then
				break
			end
		end
	end	
end

return dispatcher

