function init()
-- You **MUST** declare what inputs you want to use at some point
    self:addBinding("move_up")
    self:addBinding("move_down")
    self:addBinding("move_left")
    self:addBinding("move_right")

    self:addBinding("move_up_fast")
    self:addBinding("move_down_fast")
    self:addBinding("move_left_fast")
    self:addBinding("move_right_fast")

    self:refreshBindings()

-- This function call may not work as it __may__ be overwritten by some internal calls
-- (in the init function, it works elsewhere)
--    resetRotPos()

    xStep = 0
    yStep = 0
end

function main()
    xStep = xStep * 0.99
    yStep = yStep * 0.99



    if not (parent == nil) then
        self.rotX = parent.x - self.realX
        self.rotY = parent.y - self.realY
    end
    if parent == nil then
        if(self:isPressed("move_up"))
        then
            yStep = yStep - 0.25
        end
        if(self:isPressed("move_down"))
        then
            yStep = yStep + 0.25
        end

        if(self:isPressed("move_left"))
        then
            xStep = xStep - 0.25
        end
        if(self:isPressed("move_right"))
        then
            xStep = xStep + 0.25
        end

        if(self:isPressed("move_up_fast"))
        then
            yStep = yStep - 1
        end
        if(self:isPressed("move_down_fast"))
        then
            yStep = yStep + 1
        end

        if(self:isPressed("move_left_fast"))
        then
            xStep = xStep - 1
        end
        if(self:isPressed("move_right_fast"))
        then
            xStep = xStep + 1
        end

        if(self.x + xStep > 0 and self.x + xStep < EW - 200)
        then
            self.x = self.x + xStep
        else
            xStep = xStep * -1
            self.x = self.x + xStep
            self.hflip = not self.hflip;
            self:playAnim(2, 1)
        end

        if(self.y + yStep > 0 and self.y + yStep < EH - 82)
        then
            self.y = self.y + yStep
        else
            yStep = yStep * -1
            self.y = self.y + yStep
            self.vflip = not self.vflip;
            self:playAnim(2, 1)
        end
    end

    self.rot = self.rot + 1
end