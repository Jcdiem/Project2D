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

    xStep = 0
    yStep = 0
end

function main()
    xStep = xStep * 0.99;
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
        yStep = yStep - 0.25
    end
    if(isPressed("move_down_fast"))
    then
        yStep = yStep + 0.25
    end

    if(isPressed("move_left_fast"))
    then
        xStep = xStep - 0.25
    end
    if(isPressed("move_right_fast"))
    then
        xStep = xStep + 0.25
    end

    if(x() + xStep > 0 and x() + xStep < EW() - 200)
    then
        setX(x() + xStep)
    else
        playAnim(2, 1)
        xStep = xStep * -1
        setX(x() + xStep)
    end

    if(y() + yStep > 0 and y() + yStep < EH() - 82)
    then
        setY(y() + yStep)
    else
        playAnim(2, 1)
        yStep = yStep * -1
        setY(y() + yStep)
    end
end
