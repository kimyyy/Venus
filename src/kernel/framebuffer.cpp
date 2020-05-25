
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
    Point points[4] = {rect.begin, rect.begin+Point(rect.width , 0), rect.begin+Point(rect.width, rect.height), rect.begin+Point(0, rect.height)};
    for(int i = 0;i < 4;i++){
        drawLine(points[i], points[(i+1)%4],color);
    }
}

void FrameBuffer::drawRect(Point start, Point end, Color color){
    drawRect(Rect(start, end), color);
}

void FrameBuffer::fillRect(Rect rect, Color color){
    for(uint32_t h = rect.begin.y; h < rect.begin.y + rect.height;h++){
        drawLine(Point(rect.begin.x, h), Point(rect.begin.x + rect.width, h), color);
    }
}

void FrameBuffer::fillRect(Point start, Point end, Color color){
    fillRect(Rect(start, end), color);
}

// implementation of putc
void FrameBuffer::putc(const char* c, Point point, PsfFont font, Color fgcolor, Color bgcolor,  bool transparent){
    for(uint32_t i = 0; i < font.height;i++){
        uint8_t line[32];
        font.getLine(*c, i, line);
        for(uint32_t j = 0;j < font.width;j++){
            Point point_sweep = point + Point(j, i);
            if(line[j] == 1){
                drawPoint(point_sweep, fgcolor);
            }else if(!transparent){
                drawPoint(point_sweep, bgcolor);
            }
        }
    }
}

void FrameBuffer::putc(const char* c,Point point, PsfFont font, Color fgcolor, Color bgcolor){
    putc(c, point, font, fgcolor ,bgcolor, false);
}

void FrameBuffer::putc(const char* c,Point point, PsfFont font, Color fgcolor){
    Color bgcolor_dummy(0, 0, 0);
    putc(c, point, font, fgcolor, bgcolor_dummy, true);
}

// implementation of puts
void FrameBuffer::puts(const char* c,Point point, PsfFont font, Color fgcolor, Color bgcolor, bool transparent){
    Point point_start = point;
    while(*c != '\0'){
        // FIXME: what to do if '\r' ?
        if(*c == '\n'){
            point = point_start + Point(0, font.height);
            point_start = point;
            c++;
            continue;
        }
        putc(c, point, font, fgcolor, bgcolor, transparent);
        c++;
        point = point + Point(font.width, 0);
    }
}

void FrameBuffer::puts(const char* c,Point point, PsfFont font, Color fgcolor, Color bgcolor){
    puts(c, point, font, fgcolor ,bgcolor, false);
}

void FrameBuffer::puts(const char* c,Point point, PsfFont font, Color fgcolor){
    Color bgcolor_dummy(0, 0, 0);
    puts(c, point, font, fgcolor, bgcolor_dummy, true);
}








void FrameBuffer::test(){
    Color green = Pallet::green;
    drawPoint(Point(100, 100), green);
    drawLine(Point(100, 1), Point(100, 100), green);
    Rect rect(Point(100, 100), 50, 50);
    Rect r1(Point(100, 200), Point(200,100));
    drawRect(r1, green);
    fillRect(rect, Pallet::blue);
    fillRect(r1, Pallet::red);

    PsfFont psffont_cyrkoi(PsfInfos::CyrKoi_Terminus16);
    putc("a", Point(200, 100), psffont_cyrkoi, Pallet::white);
    puts("Hello, framebuffer!", Point(200, 200), psffont_cyrkoi, Pallet::white);
    puts("Hello, \nframebuffer!", Point(200, 300), psffont_cyrkoi, Pallet::white);
}
