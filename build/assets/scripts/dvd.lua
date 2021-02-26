function init()
    xStep = 0.5
    yStep = 0.5
end

function main()
--     todo: de-hardcode values
    flipX = false
    flipY = false

    if(x() + 200 > EW())
    then
        xStep = -0.5
        flipX = true
        playAnim(2, 1)
    end
    if(y() + 82 > EH())
    then
        yStep = -0.5
        flipY = true
        playAnim(2, 1)
    end
    if(x() < 0)
    then
        xStep = 0.5
        flipX = true
        playAnim(2, 1)
    end
    if(y() < 0)
    then
        yStep = 0.5
        flipY = true
        playAnim(2, 1)
    end

    if(flipX and flipY)
    then
        print("Hit the corner!")
    end

    setX(x() + xStep)
    setY(y() + yStep)
end