
#include "psf.hpp"

PsfFont::PsfFont(uint8_t version, PsfSymbol& start, PsfSymbol& end, PsfSymbol& size){
        assert((uint64_t)&end - (uint64_t)&start, (uint64_t)&size);
        Psf2Header *psf_header = reinterpret_cast<Psf2Header*>(&start);
        height = psf_header->height;
        width = psf_header->width;
        hasUnicodeTable = psf_header->flags == 1? true:false;
        num_glyph = psf_header->numglyph;
        bytes_perglyph = psf_header->bytesperglyph;
        datasize = reinterpret_cast<uint64_t>(&size);
        glyphs_startaddr = reinterpret_cast<void *>((uint64_t)&start + psf_header->headersize);
}

void *PsfFont::getGlyphaddr(uint32_t offset){
    void *ret = reinterpret_cast<void *>((uint64_t)glyphs_startaddr +  offset * bytes_perglyph);
    return ret;
}

void PsfFont::test(){
    PsfFont psffont_cyrkoi(2, _binary_resources_CyrKoi_Terminus32x16_psf_start, _binary_resources_CyrKoi_Terminus32x16_psf_end, _binary_resources_CyrKoi_Terminus32x16_psf_size);
    assert(psffont_cyrkoi.height, (uint32_t)32);
    assert(psffont_cyrkoi.width, (uint32_t)16);
    assert(psffont_cyrkoi.hasUnicodeTable, true);
    assert(psffont_cyrkoi.bytes_perglyph, (uint32_t)64);
    assert(psffont_cyrkoi.num_glyph, (uint32_t)256);
}
