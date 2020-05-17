#pragma once

enum BreakpointType : u8 {
    BREAKPOINT_NONE, 
    BREAKPOINT_INTERNAL,
    BREAKPOINT_USER
};

struct Breakpoint {
    BreakpointType type;
    u64 address;
    u8 originalMachineCode;
};

enum {
    SECTION_DEBUG_LINE = 0,
    SECTION_DEBUG_ABBREV,
    SECTION_DEBUG_INFO,
    SECTION_DEBUG_STRING,
    SECTION_DEBUG_ARANGES,

    SECTION_DEBUG_ARRAY_SIZE
};

static char* dwarfTagsStrings[255] = {};
static char* dwarfChilrenStrings[2] = {};
static char* dwarfAttributeStrings[255] = {};
static char* dwarfFormStrings[255] = {};

static inline u64 read64or32BitFromBuffer(u8* buffer, u32* offset){
    u64 result = 0xffffffff;
    u32 lengthCheck;

    ASSIGN_FROM_BUFFER((buffer + *offset), lengthCheck, u32);
    *offset += sizeof(lengthCheck);
    if(lengthCheck < 0xfffffff0){
        result = lengthCheck;
    } else if(lengthCheck == 0xffffffff){
        ASSIGN_FROM_BUFFER((buffer + *offset), result, u64);
        *offset += sizeof(u64);
    } else if(lengthCheck != 0xffffffff) {
        ERROR("Not good format for reading 32 or 64 bit number.\n");
    }

    return result;
}

static inline void initializeDebugStrings(){
    dwarfTagsStrings[0x01] = "DW_TAG_array_type";
    dwarfTagsStrings[0x02] = "DW_TAG_class_type";
    dwarfTagsStrings[0x03] = "DW_TAG_entry_point";
    dwarfTagsStrings[0x04] = "DW_TAG_enumeration_type";
    dwarfTagsStrings[0x05] = "DW_TAG_formal_parameter";
    dwarfTagsStrings[0x08] = "DW_TAG_imported_declaration";
    dwarfTagsStrings[0x0a] = "DW_TAG_label";
    dwarfTagsStrings[0x0b] = "DW_TAG_lexical_block";
    dwarfTagsStrings[0x0d] = "DW_TAG_member";
    dwarfTagsStrings[0x0f] = "DW_TAG_pointer_type";
    dwarfTagsStrings[0x10] = "DW_TAG_reference_type";
    dwarfTagsStrings[0x11] = "DW_TAG_compile_unit";
    dwarfTagsStrings[0x12] = "DW_TAG_string_type";
    dwarfTagsStrings[0x13] = "DW_TAG_structure_type";
    dwarfTagsStrings[0x15] = "DW_TAG_subroutine_type";
    dwarfTagsStrings[0x16] = "DW_TAG_typedef";
    dwarfTagsStrings[0x17] = "DW_TAG_union_type";
    dwarfTagsStrings[0x18] = "DW_TAG_unspecified_parameters";
    dwarfTagsStrings[0x19] = "DW_TAG_variant";
    dwarfTagsStrings[0x1a] = "DW_TAG_common_block";
    dwarfTagsStrings[0x1b] = "DW_TAG_common_inclusion";
    dwarfTagsStrings[0x1c] = "DW_TAG_inheritance";
    dwarfTagsStrings[0x1d] = "DW_TAG_inlined_subroutine";
    dwarfTagsStrings[0x1e] = "DW_TAG_module";
    dwarfTagsStrings[0x1f] = "DW_TAG_ptr_to_member_type";
    dwarfTagsStrings[0x20] = "DW_TAG_set_type";
    dwarfTagsStrings[0x21] = "DW_TAG_subrange_type";
    dwarfTagsStrings[0x22] = "DW_TAG_with_stmt";
    dwarfTagsStrings[0x23] = "DW_TAG_access_declaration";
    dwarfTagsStrings[0x24] = "DW_TAG_base_type";
    dwarfTagsStrings[0x25] = "DW_TAG_catch_block";
    dwarfTagsStrings[0x26] = "DW_TAG_const_type";
    dwarfTagsStrings[0x27] = "DW_TAG_constant";
    dwarfTagsStrings[0x28] = "DW_TAG_enumerator";
    dwarfTagsStrings[0x29] = "DW_TAG_file_type";
    dwarfTagsStrings[0x2a] = "DW_TAG_friend";
    dwarfTagsStrings[0x2b] = "DW_TAG_namelist";
    dwarfTagsStrings[0x2c] = "DW_TAG_namelist_item";
    dwarfTagsStrings[0x2d] = "DW_TAG_packed_type";
    dwarfTagsStrings[0x2e] = "DW_TAG_subprogram";
    dwarfTagsStrings[0x2f] = "DW_TAG_template_type_parameter";
    dwarfTagsStrings[0x30] = "DW_TAG_template_value_parameter";
    dwarfTagsStrings[0x31] = "DW_TAG_thrown_type";
    dwarfTagsStrings[0x32] = "DW_TAG_try_block";
    dwarfTagsStrings[0x33] = "DW_TAG_variant_part";
    dwarfTagsStrings[0x34] = "DW_TAG_variable";
    dwarfTagsStrings[0x35] = "DW_TAG_volatile_type";
    dwarfTagsStrings[0x36] = "DW_TAG_dwarf_procedure";
    dwarfTagsStrings[0x37] = "DW_TAG_restrict_type";
    dwarfTagsStrings[0x38] = "DW_TAG_interface_type";
    dwarfTagsStrings[0x39] = "DW_TAG_namespace";
    dwarfTagsStrings[0x3a] = "DW_TAG_imported_module";
    dwarfTagsStrings[0x3b] = "DW_TAG_unspecified_type";
    dwarfTagsStrings[0x3c] = "DW_TAG_partial_unit";
    dwarfTagsStrings[0x3d] = "DW_TAG_imported_unit";
    dwarfTagsStrings[0x3f] = "DW_TAG_condition";
    dwarfTagsStrings[0x40] = "DW_TAG_shared_type";
    dwarfTagsStrings[0x41] = "DW_TAG_type_unit";
    dwarfTagsStrings[0x42] = "DW_TAG_rvalue_reference_type";
    dwarfTagsStrings[0x43] = "DW_TAG_template_alias";

    dwarfChilrenStrings[0x00] = "DW_CHILDREN_no";
    dwarfChilrenStrings[0x01] = "DW_CHILDREN_yes";

    dwarfAttributeStrings[0x01] = "DW_AT_sibling";
    dwarfAttributeStrings[0x02] = "DW_AT_location";
    dwarfAttributeStrings[0x03] = "DW_AT_name";
    dwarfAttributeStrings[0x09] = "DW_AT_ordering";
    dwarfAttributeStrings[0x0b] = "DW_AT_byte_size";
    dwarfAttributeStrings[0x0c] = "DW_AT_bit_offset";
    dwarfAttributeStrings[0x0d] = "DW_AT_bit_size";
    dwarfAttributeStrings[0x10] = "DW_AT_stmt_list";
    dwarfAttributeStrings[0x11] = "DW_AT_low_pc";
    dwarfAttributeStrings[0x12] = "DW_AT_high_pc";
    dwarfAttributeStrings[0x13] = "DW_AT_language";
    dwarfAttributeStrings[0x15] = "DW_AT_discr";
    dwarfAttributeStrings[0x16] = "DW_AT_discr_value";
    dwarfAttributeStrings[0x17] = "DW_AT_visibility";
    dwarfAttributeStrings[0x18] = "DW_AT_import";
    dwarfAttributeStrings[0x19] = "DW_AT_string_length";
    dwarfAttributeStrings[0x1a] = "DW_AT_common_reference";
    dwarfAttributeStrings[0x1b] = "DW_AT_comp_dir";
    dwarfAttributeStrings[0x1c] = "DW_AT_const_value";
    dwarfAttributeStrings[0x1d] = "DW_AT_containing_type";
    dwarfAttributeStrings[0x1e] = "DW_AT_default_value";
    dwarfAttributeStrings[0x20] = "DW_AT_inline";
    dwarfAttributeStrings[0x21] = "DW_AT_is_optional";
    dwarfAttributeStrings[0x22] = "DW_AT_lower_bound";
    dwarfAttributeStrings[0x25] = "DW_AT_producer";
    dwarfAttributeStrings[0x27] = "DW_AT_prototyped";
    dwarfAttributeStrings[0x2a] = "DW_AT_return_addr";
    dwarfAttributeStrings[0x2c] = "DW_AT_start_scope";
    dwarfAttributeStrings[0x2e] = "DW_AT_bit_stride";
    dwarfAttributeStrings[0x2f] = "DW_AT_upper_bound";
    dwarfAttributeStrings[0x31] = "DW_AT_abstract_origin";
    dwarfAttributeStrings[0x32] = "DW_AT_accessibility";
    dwarfAttributeStrings[0x33] = "DW_AT_address_class";
    dwarfAttributeStrings[0x34] = "DW_AT_artificial";
    dwarfAttributeStrings[0x35] = "DW_AT_base_types";
    dwarfAttributeStrings[0x36] = "DW_AT_calling_convention";
    dwarfAttributeStrings[0x37] = "DW_AT_count";
    dwarfAttributeStrings[0x38] = "DW_AT_data_member_location";
    dwarfAttributeStrings[0x39] = "DW_AT_decl_column";
    dwarfAttributeStrings[0x3a] = "DW_AT_decl_file";
    dwarfAttributeStrings[0x3b] = "DW_AT_decl_line";
    dwarfAttributeStrings[0x3c] = "DW_AT_declaration";
    dwarfAttributeStrings[0x3d] = "DW_AT_discr_list";
    dwarfAttributeStrings[0x3e] = "DW_AT_encoding";
    dwarfAttributeStrings[0x3f] = "DW_AT_external";
    dwarfAttributeStrings[0x40] = "DW_AT_frame_base";
    dwarfAttributeStrings[0x41] = "DW_AT_friend";
    dwarfAttributeStrings[0x42] = "DW_AT_identifier_case";
    dwarfAttributeStrings[0x43] = "DW_AT_macro_info";
    dwarfAttributeStrings[0x44] = "DW_AT_namelist_item";
    dwarfAttributeStrings[0x45] = "DW_AT_priority";
    dwarfAttributeStrings[0x46] = "DW_AT_segment";
    dwarfAttributeStrings[0x47] = "DW_AT_specification";
    dwarfAttributeStrings[0x48] = "DW_AT_static_link";
    dwarfAttributeStrings[0x49] = "DW_AT_type";
    dwarfAttributeStrings[0x4a] = "DW_AT_use_location";
    dwarfAttributeStrings[0x4b] = "DW_AT_variable_parameter";
    dwarfAttributeStrings[0x4c] = "DW_AT_virtuality";
    dwarfAttributeStrings[0x4d] = "DW_AT_vtable_elem_location";
    dwarfAttributeStrings[0x4e] = "DW_AT_allocated";
    dwarfAttributeStrings[0x4f] = "DW_AT_associated";
    dwarfAttributeStrings[0x50] = "DW_AT_data_location";
    dwarfAttributeStrings[0x51] = "DW_AT_byte_stride";
    dwarfAttributeStrings[0x52] = "DW_AT_entry_pc";
    dwarfAttributeStrings[0x53] = "DW_AT_use_UTF8";
    dwarfAttributeStrings[0x54] = "DW_AT_extension";
    dwarfAttributeStrings[0x55] = "DW_AT_ranges";
    dwarfAttributeStrings[0x56] = "DW_AT_trampoline";
    dwarfAttributeStrings[0x57] = "DW_AT_call_column";
    dwarfAttributeStrings[0x58] = "DW_AT_call_file";
    dwarfAttributeStrings[0x59] = "DW_AT_call_line";
    dwarfAttributeStrings[0x5a] = "DW_AT_description";
    dwarfAttributeStrings[0x5b] = "DW_AT_binary_scale";
    dwarfAttributeStrings[0x5c] = "DW_AT_decimal_scale";
    dwarfAttributeStrings[0x5d] = "DW_AT_small";
    dwarfAttributeStrings[0x5e] = "DW_AT_decimal_sign";
    dwarfAttributeStrings[0x5f] = "DW_AT_digit_count";
    dwarfAttributeStrings[0x60] = "DW_AT_picture_string";
    dwarfAttributeStrings[0x61] = "DW_AT_mutable";
    dwarfAttributeStrings[0x62] = "DW_AT_threads_scaled";
    dwarfAttributeStrings[0x63] = "DW_AT_explicit";
    dwarfAttributeStrings[0x64] = "DW_AT_object_pointer";
    dwarfAttributeStrings[0x65] = "DW_AT_endianity";
    dwarfAttributeStrings[0x66] = "DW_AT_elemental";
    dwarfAttributeStrings[0x67] = "DW_AT_pure";
    dwarfAttributeStrings[0x68] = "DW_AT_recursive";
    dwarfAttributeStrings[0x69] = "DW_AT_signature";
    dwarfAttributeStrings[0x6a] = "DW_AT_main_subprogram";
    dwarfAttributeStrings[0x6b] = "DW_AT_data_bit_offset";
    dwarfAttributeStrings[0x6c] = "DW_AT_const_expr";
    dwarfAttributeStrings[0x6d] = "DW_AT_enum_class";
    dwarfAttributeStrings[0x6e] = "DW_AT_linkage_name";

    dwarfFormStrings[0x01] = "DW_FORM_addr";
    dwarfFormStrings[0x03] = "DW_FORM_block2";
    dwarfFormStrings[0x04] = "DW_FORM_block4";
    dwarfFormStrings[0x05] = "DW_FORM_data2";
    dwarfFormStrings[0x06] = "DW_FORM_data4";
    dwarfFormStrings[0x07] = "DW_FORM_data8";
    dwarfFormStrings[0x08] = "DW_FORM_string";
    dwarfFormStrings[0x09] = "DW_FORM_block";
    dwarfFormStrings[0x0a] = "DW_FORM_block1";
    dwarfFormStrings[0x0b] = "DW_FORM_data1";
    dwarfFormStrings[0x0c] = "DW_FORM_flag";
    dwarfFormStrings[0x0d] = "DW_FORM_sdata";
    dwarfFormStrings[0x0e] = "DW_FORM_strp";
    dwarfFormStrings[0x0f] = "DW_FORM_udata";
    dwarfFormStrings[0x10] = "DW_FORM_ref_addr";
    dwarfFormStrings[0x11] = "DW_FORM_ref1";
    dwarfFormStrings[0x12] = "DW_FORM_ref2";
    dwarfFormStrings[0x13] = "DW_FORM_ref4";
    dwarfFormStrings[0x14] = "DW_FORM_ref8";
    dwarfFormStrings[0x15] = "DW_FORM_ref_udata";
    dwarfFormStrings[0x16] = "DW_FORM_indirect";
    dwarfFormStrings[0x17] = "DW_FORM_sec_offset";
    dwarfFormStrings[0x18] = "DW_FORM_exprloc";
    dwarfFormStrings[0x19] = "DW_FORM_flag_present";
    dwarfFormStrings[0x20] = "DW_FORM_ref_sig8";
};


#define DW_FORM_addr                0x01
#define DW_FORM_block2              0x03
#define DW_FORM_block4              0x04
#define DW_FORM_data2               0x05
#define DW_FORM_data4               0x06
#define DW_FORM_data8               0x07
#define DW_FORM_string              0x08
#define DW_FORM_block               0x09
#define DW_FORM_block1              0x0a
#define DW_FORM_data1               0x0b
#define DW_FORM_flag                0x0c
#define DW_FORM_sdata               0x0d
#define DW_FORM_strp                0x0e
#define DW_FORM_udata               0x0f
#define DW_FORM_ref_addr            0x10
#define DW_FORM_ref1                0x11
#define DW_FORM_ref2                0x12
#define DW_FORM_ref4                0x13
#define DW_FORM_ref8                0x14
#define DW_FORM_ref_udata           0x15
#define DW_FORM_indirect            0x16 
#define DW_FORM_sec_offset          0x17
#define DW_FORM_exprloc             0x18
#define DW_FORM_flag_present        0x19
#define DW_FORM_ref_sig8            0x20

#define DW_AT_sibling               0x01
#define DW_AT_location              0x02
#define DW_AT_name                  0x03
#define DW_AT_ordering              0x09
#define DW_AT_byte_size             0x0b
#define DW_AT_bit_offset            0x0c
#define DW_AT_bit_size              0x0d
#define DW_AT_stmt_list             0x10
#define DW_AT_low_pc                0x11
#define DW_AT_high_pc               0x12
#define DW_AT_language              0x13
#define DW_AT_discr                 0x15
#define DW_AT_discr_value           0x16
#define DW_AT_visibility            0x17
#define DW_AT_import                0x18
#define DW_AT_string_length         0x19
#define DW_AT_common_reference      0x1a
#define DW_AT_comp_dir              0x1b
#define DW_AT_const_value           0x1c
#define DW_AT_containing_type       0x1d
#define DW_AT_default_value         0x1e
#define DW_AT_inline                0x20
#define DW_AT_is_optional           0x21
#define DW_AT_lower_bound           0x22
#define DW_AT_producer              0x25
#define DW_AT_prototyped            0x27
#define DW_AT_return_addr           0x2a
#define DW_AT_start_scope           0x2c
#define DW_AT_bit_stride            0x2e
#define DW_AT_upper_bound           0x2f
#define DW_AT_abstract_origin       0x31
#define DW_AT_accessibility         0x32
#define DW_AT_address_class         0x33
#define DW_AT_artificial            0x34
#define DW_AT_base_types            0x35
#define DW_AT_calling_convention    0x36
#define DW_AT_count                 0x37
#define DW_AT_data_member_location  0x38
#define DW_AT_decl_column           0x39
#define DW_AT_decl_file             0x3a
#define DW_AT_decl_line             0x3b
#define DW_AT_declaration           0x3c
#define DW_AT_discr_list            0x3d
#define DW_AT_encoding              0x3e
#define DW_AT_external              0x3f
#define DW_AT_frame_base            0x40
#define DW_AT_friend                0x41
#define DW_AT_identifier_case       0x42
#define DW_AT_macro_info            0x43
#define DW_AT_namelist_item         0x44
#define DW_AT_priority              0x45
#define DW_AT_segment               0x46
#define DW_AT_specification         0x47
#define DW_AT_static_link           0x48
#define DW_AT_type                  0x49
#define DW_AT_use_location          0x4a
#define DW_AT_variable_parameter    0x4b
#define DW_AT_virtuality            0x4c
#define DW_AT_vtable_elem_location  0x4d
#define DW_AT_allocated             0x4e
#define DW_AT_associated            0x4f
#define DW_AT_data_location         0x50
#define DW_AT_byte_stride           0x51
#define DW_AT_entry_pc              0x52
#define DW_AT_use_UTF8              0x53
#define DW_AT_extension             0x54
#define DW_AT_ranges                0x55
#define DW_AT_trampoline            0x56
#define DW_AT_call_column           0x57
#define DW_AT_call_file             0x58
#define DW_AT_call_line             0x59
#define DW_AT_description           0x5a
#define DW_AT_binary_scale          0x5b
#define DW_AT_decimal_scale         0x5c
#define DW_AT_small                 0x5d
#define DW_AT_decimal_sign          0x5e
#define DW_AT_digit_count           0x5f
#define DW_AT_picture_string        0x60
#define DW_AT_mutable               0x61
#define DW_AT_threads_scaled        0x62 
#define DW_AT_explicit              0x63 
#define DW_AT_object_pointer        0x64
#define DW_AT_endianity             0x65
#define DW_AT_elemental             0x66
#define DW_AT_pure                  0x67 
#define DW_AT_recursive             0x68
#define DW_AT_signature             0x69
#define DW_AT_main_subprogram       0x6a
#define DW_AT_data_bit_offset       0x6b
#define DW_AT_const_expr            0x6c
#define DW_AT_enum_class            0x6d
#define DW_AT_linkage_name          0x6e

#define DW_AT_lo_user               0x2000
#define DW_AT_hi_user               0x3fff

#define DW_CHILDREN_no      0x00
#define DW_CHILDREN_yes     0x01

#define DW_TAG_array_type               0x01
#define DW_TAG_class_type               0x02
#define DW_TAG_entry_point              0x03
#define DW_TAG_enumeration_type         0x04
#define DW_TAG_formal_parameter         0x05
#define DW_TAG_imported_declaration     0x08
#define DW_TAG_label                    0x0a
#define DW_TAG_lexical_block            0x0b
#define DW_TAG_member                   0x0d
#define DW_TAG_pointer_type             0x0f
#define DW_TAG_reference_type           0x10
#define DW_TAG_compile_unit             0x11
#define DW_TAG_string_type              0x12
#define DW_TAG_structure_type           0x13
#define DW_TAG_subroutine_type          0x15
#define DW_TAG_typedef                  0x16 
#define DW_TAG_union_type               0x17
#define DW_TAG_unspecified_parameters   0x18
#define DW_TAG_variant                  0x19
#define DW_TAG_common_block             0x1a
#define DW_TAG_common_inclusion         0x1b
#define DW_TAG_inheritance              0x1c
#define DW_TAG_inlined_subroutine       0x1d
#define DW_TAG_module                   0x1e
#define DW_TAG_ptr_to_member_type       0x1f
#define DW_TAG_set_type                 0x20
#define DW_TAG_subrange_type            0x21
#define DW_TAG_with_stmt                0x22
#define DW_TAG_access_declaration       0x23
#define DW_TAG_base_type                0x24
#define DW_TAG_catch_block              0x25
#define DW_TAG_const_type               0x26
#define DW_TAG_constant                 0x27
#define DW_TAG_enumerator               0x28
#define DW_TAG_file_type                0x29
#define DW_TAG_friend                   0x2a 
#define DW_TAG_namelist                 0x2b
#define DW_TAG_namelist_item            0x2c
#define DW_TAG_packed_type              0x2d
#define DW_TAG_subprogram               0x2e
#define DW_TAG_template_type_parameter  0x2f
#define DW_TAG_template_value_parameter 0x30
#define DW_TAG_thrown_type              0x31
#define DW_TAG_try_block                0x32
#define DW_TAG_variant_part             0x33
#define DW_TAG_variable                 0x34
#define DW_TAG_volatile_type            0x35
#define DW_TAG_dwarf_procedure          0x36
#define DW_TAG_restrict_type            0x37
#define DW_TAG_interface_type           0x38
#define DW_TAG_namespace                0x39
#define DW_TAG_imported_module          0x3a
#define DW_TAG_unspecified_type         0x3b
#define DW_TAG_partial_unit             0x3c
#define DW_TAG_imported_unit            0x3d
#define DW_TAG_condition                0x3f
#define DW_TAG_shared_type              0x40
#define DW_TAG_type_unit                0x41
#define DW_TAG_rvalue_reference_type    0x42
#define DW_TAG_template_alias           0x43

#define DW_TAG_lo_user                  0x4080
#define DW_TAG_hi_user                  0xffff

#define DW_LNE_end_sequence         1
#define DW_LNE_set_address          2
#define DW_LNE_define_file          3
#define DW_LNE_set_discriminator    4

#define DW_LNS_extended_op          0
#define DW_LNS_copy                 1
#define DW_LNS_advance_pc           2
#define DW_LNS_advance_line         3
#define DW_LNS_set_file             4
#define DW_LNS_set_column           5
#define DW_LNS_negate_stmt          6
#define DW_LNS_set_basic_block      7
#define DW_LNS_const_add_pc         8
#define DW_LNS_fixed_advance_pc     9
#define DW_LNS_set_prologue_end     10
#define DW_LNS_set_epilogue_begin   11
#define DW_LNS_set_isa              12

