
#include "psf.hpp"

PsfFont::PsfFont(uint8_t version, PsfSymbol& start, PsfSymbol& end, PsfSymbol& size){
        // assert: end-start = size
        PSF2_Header *psf_header = reinterpret_cast<PSF2_Header*>(&start);
        height = psf_header->height;
        width = psf_header->width;
        hasUnicodeTable = psf_header->flags == 1? true:false;
        num_glyph = psf_header->numglyph;
        bytes_perglyph = psf_header->bytesperglyph;
        datasize = reinterpret_cast<uint64_t>(&size);
        bitmap_startaddr = reinterpret_cast<void *>((uint64_t)&start + psf_header->headersize);
}

void *PsfFont::getGlyphaddr(uint32_t offset){
    void *ret = reinterpret_cast<void *>((uint64_t)bitmap_startaddr +  offset * bytes_perglyph);
    return ret;
}
