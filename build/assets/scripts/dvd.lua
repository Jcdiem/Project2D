function init()
-- You **MUST** declare what inputs you want to use at some point
    addBinding("move_up")
    addBinding("move_down")
    addBinding("move_left")
    addBinding("move_right")

    addBinding("move_up_fast")
    addBinding("move_down_fast")
    addBinding("move_left_fast")
    addBinding("move_right_fast")

    self.rotX = 0
    self.rotY = 0

    resetRotPos()

    xStep = 0
    yStep = 0
end

function main()
    xStep = xStep * 0.99
    yStep = yStep * 0.99

    if(isPressed("move_up"))
    then
        yStep = yStep - 0.25
    end
    if(isPressed("move_down"))
    then
        yStep = yStep + 0.25
    end

    if(isPressed("move_left"))
    then
        xStep = xStep - 0.25
    end
    if(isPressed("move_right"))
    then
        xStep = xStep + 0.25
    end

    if(isPressed("move_up_fast"))
    then
        yStep = yStep - 1
    end
    if(isPressed("move_down_fast"))
    then
        yStep = yStep + 1
    end

    if(isPressed("move_left_fast"))
    then
        xStep = xStep - 1
    end
    if(isPressed("move_right_fast"))
    then
        xStep = xStep + 1
    end

    if(self.x + xStep > 0 and self.x + xStep < self.EW - 200)
    then
        self.x = self.x + xStep
    else
        xStep = xStep * -1
        self.x = self.x + xStep
        self.hflip = not self.hflip;
        playAnim(2, 1)
    end

    if(self.y + yStep > 0 and self.y + yStep < self.EH - 82)
    then
        self.y = self.y + yStep
    else
        yStep = yStep * -1
        self.y = self.y + yStep
        self.vflip = not self.vflip;
        playAnim(2, 1)
    end

    self.rot = self.rot + 1
end
