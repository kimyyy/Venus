
#include "psf.hpp"


PsfFont::PsfFont(PsfVersion version, PsfSymbol* start, PsfSymbol* end, PsfSymbol* size){
    assert((uint64_t)end - (uint64_t)start, (uint64_t)size);
    // parse psf header
    if(version==PsfVersion::Version1){
        Psf1Header *psf_header = reinterpret_cast<Psf1Header*>(start);
        // TODO: if magic is not match, throw error
        assert(psf_header->magic[0], psf1_magic[0]);
        assert(psf_header->magic[1], psf1_magic[1]);
        if(IsBitmatch(psf_header->mode, psf1_mode512)){
            num_glyph = 512;
        }else{
            num_glyph = 256;
        }
        hasUnicodeTable = IsBitmatch(psf_header->mode, psf1_modehastab);
        width = 8;
        height = psf_header->charsize;
        bytes_perglyph = psf_header->charsize;
        datasize = reinterpret_cast<uint64_t>(size);
        glyphs_startaddr = reinterpret_cast<void *>((uint64_t)start + sizeof(Psf1Header));
    }else if(version==PsfVersion::Version2){
        Psf2Header *psf_header = reinterpret_cast<Psf2Header*>(start);
        // TODO: throw error if magic is not match
        height = psf_header->height;
        width = psf_header->width;
        hasUnicodeTable = psf_header->flags == 1? true:false;
        num_glyph = psf_header->numglyph;
        bytes_perglyph = psf_header->bytesperglyph;
        datasize = reinterpret_cast<uint64_t>(size);
        glyphs_startaddr = reinterpret_cast<void *>((uint64_t)start + psf_header->headersize);
    }
}

uint32_t PsfFont::getGlyphIndex(uint32_t c){
    // TODO: convert UTF-8 to Unicode ID and get Index from Unicodetable(if Unicodetable is available)
    // In PoC, we must use acsii char
    return c;
}

uint8_t *PsfFont::getGlyphaddr(uint32_t index) {
    // throw error is index is over num_glyph
    assert(index <= num_glyph);
    uint8_t *ret = reinterpret_cast<uint8_t *>((uint64_t)glyphs_startaddr + index * bytes_perglyph);
    return ret;
}

void PsfFont::getLine(uint32_t c, uint32_t lineheight, uint8_t line[]){
    uint8_t *glyphAddr = getGlyphaddr(getGlyphIndex(c));
    uint32_t bytes_in_line = (width - 1) / 8 + 1;
    glyphAddr += lineheight * bytes_in_line;
    uint32_t counter_width = 0;
    for (uint32_t i = 0; i < bytes_in_line && counter_width < width; i++) {
        for (uint32_t j = 0; j < 8 && counter_width < width; j++) {
            line[j + i * 8] =
                IsBitmatch(*glyphAddr, uint8_t(1 << (8 - j - 1))) ? 1 : 0;
            counter_width++;
        }
        glyphAddr++;
    }
}

namespace PsfInfos {
    void init(){
        CyrKoi_Terminus32x16 = PsfInfo(PsfVersion::Version2,  &_binary_resources_CyrKoi_Terminus32x16_psf_start,&_binary_resources_CyrKoi_Terminus32x16_psf_end, &_binary_resources_CyrKoi_Terminus32x16_psf_size);
        CyrKoi_Terminus16 = PsfInfo(PsfVersion::Version1, &_binary_resources_CyrKoi_Terminus16_psf_start,&_binary_resources_CyrKoi_Terminus16_psf_end,&_binary_resources_CyrKoi_Terminus16_psf_size);
    }
}


void PsfFont::test(){
    PsfInfos::init();
    // parse psf header version: 1
    PsfFont psffont_cyrkoi16(PsfInfos::CyrKoi_Terminus16);
    assert(psffont_cyrkoi16.width == 8);
    assert(psffont_cyrkoi16.height == 16);
    assert(psffont_cyrkoi16.bytes_perglyph == 16);
    assert(psffont_cyrkoi16.hasUnicodeTable = true);
    assert(psffont_cyrkoi16.num_glyph = 256);

    // parse psf header version 2
    PsfFont psffont_cyrkoi32x16(PsfInfos::CyrKoi_Terminus32x16);
    assert(psffont_cyrkoi32x16.height, (uint32_t)32);
    assert(psffont_cyrkoi32x16.width, (uint32_t)16);
    assert(psffont_cyrkoi32x16.hasUnicodeTable, true);
    assert(psffont_cyrkoi32x16.bytes_perglyph, (uint32_t)64);
    assert(psffont_cyrkoi32x16.num_glyph, (uint32_t)256);

    // getLine test
    uint8_t line_0_expect[] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0};
    uint8_t line_0_actual[16];
    psffont_cyrkoi32x16.getLine('0', 6, line_0_actual);
    assert(line_0_actual, line_0_expect, 16);
    uint8_t line_A_expect[] = {0, 0, 1, 1, 1, 1, 0, 0};
    uint8_t line_A_actual[8];
    psffont_cyrkoi16.getLine('A', 2, line_A_actual);
    assert(line_A_actual, line_A_expect, 8);
}
