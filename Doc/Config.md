App:{
    logEnable
}
window:{
    frame:true //有边框，有标题栏
    visible:true //是否可见
    size:{        
        width //宽度
        height //高度
        resizable
        sizeMin:{        
            width //宽度
            height //高度
        }
        sizeMax:{        
            width //宽度
            height //高度
        },
    },
    position:{
        isCenterScreen //是否屏幕正中      
        movable   
        x //x坐标
        y //y坐标
    }
    closable，
    alwaysOnTop,
    fullscreen,
    fullscreenable,
    skipTaskbar,
    title,
    icon,
    parent,
    modal,
    hasShadow,
    opacity,
    devToolsEnable,
    Page
}
Page:{    
    url //首页地址
}
