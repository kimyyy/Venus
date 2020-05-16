
#include "framebuffer.hpp"

FrameBuffer::FrameBuffer(FrameBufferInfo info){
    m_base = reinterpret_cast<PixelFormat *>(info.base);
    m_size = info.size;
    m_hr = info.hr;
    m_vr = info.vr;
}

PixelFormat *FrameBuffer::getPixelFormat(Point point){
    // TODO: check if Point is out of screen
    return m_base + (m_hr * point.y) + point.x;
}

void FrameBuffer::drawPoint(Point point, Color color){
    PixelFormat *p = getPixelFormat(point);
    
    p->SetColor(color);
}

void FrameBuffer::drawLine(Point start, Point end, Color color){
    if(start.x == end.x){
       uint32_t lower_y = (start.y < end.y)? start.y:end.y;
       uint32_t greater_y = (start.y >= end.y)? start.y:end.y;
       for(;lower_y <= greater_y;lower_y++){
            drawPoint(Point(start.x, lower_y), color);
       }

    }else if(start.y == end.y){
       uint32_t lower_x = (start.x < end.x)? start.x:end.x;
       uint32_t greater_x = (start.x >= end.x)? start.x:end.x;
       for(;lower_x <= greater_x;lower_x++){
            drawPoint(Point(lower_x, start.y), color);
       }
    }else{
        // TODO: DBG warning:invalid call
        return;
    }
}

void FrameBuffer::drawRect(Rect rect, Color color){
    for(uint32_t h = rect.begin.y; h < rect.begin.y + rect.height;h++){
        drawLine(Point(rect.begin.x, h), Point(rect.begin.x + rect.width, h), color);
    }
}

void FrameBuffer::drawRect(Point start, Point end, Color color){
    if(!(start.x <= end.x && start.y <= end.y)){
        Point tmp = start;
        start = end;
        end = tmp;
    }
    uint32_t width = end.x - start.x;
    uint32_t height = end.y - start.y;
    drawRect(Rect(start, width, height), color);
}

void FrameBuffer::testFrameBuffer(){
    Pallet pallet;
    Color green = pallet.green;
    drawPoint(Point(100, 100), green);
    drawLine(Point(100, 1), Point(100, 100), green);
    Rect rect = {Point(100, 100), 50, 50};
    drawRect(rect, pallet.blue);
    drawRect(Point(200, 200), Point(300, 400), pallet.red);
}
