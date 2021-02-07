function init()
    xStep = 1
    yStep = 1
end

function main()
--     todo: de-hardcode values

    if(x() + 200 > EW())
    then
        xStep = -1
    end
    if(y() + 82 > EH())
    then
        yStep = -1
    end
    if(x() < 0)
    then
        xStep = 1
    end
    if(y() < 0)
    then
        yStep = 1
    end

    setX(x() + xStep)
    setY(y() + yStep)
end