function init()
    xStep = 1
    yStep = 1
end

function main()
--     todo: de-hardcode values
    flipX = false;
    flipY = false;

    if(x() + 200 > EW())
    then
        xStep = -1
        flipX = true;
    end
    if(y() + 82 > EH())
    then
        yStep = -1
        flipY = true;
    end
    if(x() < 0)
    then
        xStep = 1
        flipX = true;
    end
    if(y() < 0)
    then
        yStep = 1
        flipY = true;
    end

    if(flipX and flipY)
    then
        print("Hit the corner!")
    end

    setX(x() + xStep)
    setY(y() + yStep)
end