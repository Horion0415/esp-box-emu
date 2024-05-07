// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.2.3
// LVGL version: 8.2.0
// Project name: menu

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_Screen1;
lv_obj_t *ui_menu_panel;
lv_obj_t *ui_menu_title;
lv_obj_t *ui_resume_btn;
lv_obj_t *ui_Label6;
lv_obj_t *ui_Panel3;
lv_obj_t *ui_volume_mute_btn;
lv_obj_t *ui_Label10;
lv_obj_t *ui_volume_dec_btn;
lv_obj_t *ui_Label11;
lv_obj_t *ui_Bar2;
lv_obj_t *ui_volume_inc_btn;
lv_obj_t *ui_Label8;
lv_obj_t *ui_Panel4;
lv_obj_t *ui_btn_slot_dec;
lv_obj_t *ui_Label2;
lv_obj_t *ui_slot_label;
lv_obj_t *ui_btn_slot_inc;
lv_obj_t *ui_Label1;
lv_obj_t *ui_Panel2;
lv_obj_t *ui_load_btn;
lv_obj_t *ui_Label4;
lv_obj_t *ui_slot_image;
lv_obj_t *ui_Panel1;
lv_obj_t *ui_save_btn;
lv_obj_t *ui_Label3;
lv_obj_t *ui_pause_image;
lv_obj_t *ui_Panel6;
lv_obj_t *ui_Label9;
lv_obj_t *ui_Dropdown2;
lv_obj_t *ui_reset_btn;
lv_obj_t *ui_Label5;
lv_obj_t *ui_quit_btn;
lv_obj_t *ui_Label7;
lv_obj_t *ui____initial_actions0;
lv_obj_t *ui_PanelSetting;
lv_obj_t *ui_PanelSettingLabel;
lv_obj_t *ui_img_muteset;
lv_obj_t *ui_img_plusset;
lv_obj_t *ui_img_reduceset;

LV_IMG_DECLARE(img_mute);
LV_IMG_DECLARE(img_plus);
LV_IMG_DECLARE(img_reduce);

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
ui_Screen1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_menu_panel = lv_obj_create(ui_Screen1);
lv_obj_set_width( ui_menu_panel, lv_pct(100));
lv_obj_set_height( ui_menu_panel, lv_pct(100));
lv_obj_set_align( ui_menu_panel, LV_ALIGN_CENTER );
lv_obj_set_style_bg_color(ui_menu_panel, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT );


// ui_menu_title = lv_label_create(ui_menu_panel);
// lv_obj_set_width( ui_menu_title, LV_SIZE_CONTENT);  /// 1
// lv_obj_set_height( ui_menu_title, LV_SIZE_CONTENT);   /// 1
// lv_obj_set_align( ui_menu_title, LV_ALIGN_TOP_MID );
// lv_label_set_text(ui_menu_title,"Emulation Paused");
ui_PanelSetting = lv_obj_create(ui_menu_panel);
lv_obj_set_width( ui_PanelSetting, 320);
lv_obj_set_height(ui_PanelSetting, 45);
lv_obj_set_style_bg_color(ui_PanelSetting, lv_color_hex(0xec6459), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_align(ui_PanelSetting, LV_ALIGN_TOP_MID, 0, -15);
lv_obj_set_style_border_color(ui_PanelSetting, lv_color_hex(0xec6459), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_PanelSettingLabel = lv_label_create(ui_PanelSetting);
lv_obj_set_align( ui_PanelSettingLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_PanelSettingLabel, "Setting");


ui_resume_btn = lv_btn_create(ui_menu_panel);
lv_obj_set_width( ui_resume_btn, 100);
lv_obj_set_height( ui_resume_btn, 40);
lv_obj_set_x( ui_resume_btn, 0 );
lv_obj_set_y( ui_resume_btn, 40 );
lv_obj_set_align( ui_resume_btn, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_resume_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_resume_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_resume_btn, lv_color_hex(0xec6459), LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_resume_btn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);


ui_Label6 = lv_label_create(ui_resume_btn);
lv_obj_set_width( ui_Label6, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label6, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label6, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label6,"Resume");


ui_Panel3 = lv_obj_create(ui_menu_panel);
lv_obj_set_height( ui_Panel3, 50);
lv_obj_set_width( ui_Panel3, lv_pct(100));
lv_obj_set_x( ui_Panel3, 0 );
lv_obj_set_y( ui_Panel3, 80 );
lv_obj_set_align( ui_Panel3, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_Panel3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_Panel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Panel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Panel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Panel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel3, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Panel3, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_volume_mute_btn = lv_btn_create(ui_Panel3);
lv_obj_set_width( ui_volume_mute_btn, 30);
lv_obj_set_height( ui_volume_mute_btn, 30);
lv_obj_set_align( ui_volume_mute_btn, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_volume_mute_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_volume_mute_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_volume_mute_btn, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_radius(ui_volume_mute_btn, 50, LV_PART_MAIN | LV_STATE_DEFAULT);

// ui_Label10 = lv_label_create(ui_volume_mute_btn);
// lv_obj_set_width( ui_Label10, LV_SIZE_CONTENT);  /// 1
// lv_obj_set_height( ui_Label10, LV_SIZE_CONTENT);   /// 1
// lv_obj_set_align( ui_Label10, LV_ALIGN_CENTER );
// lv_label_set_text(ui_Label10,LV_SYMBOL_MUTE);
ui_img_muteset = lv_img_create(ui_volume_mute_btn);
lv_img_set_src(ui_img_muteset, &img_mute);
lv_obj_set_align( ui_img_muteset, LV_ALIGN_CENTER );


ui_volume_dec_btn = lv_btn_create(ui_Panel3);
lv_obj_set_width( ui_volume_dec_btn, 30);
lv_obj_set_height( ui_volume_dec_btn, 30);
lv_obj_set_x( ui_volume_dec_btn, 35 );
lv_obj_set_y( ui_volume_dec_btn, 0 );
lv_obj_set_align( ui_volume_dec_btn, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_volume_dec_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_volume_dec_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_volume_dec_btn, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_radius(ui_volume_dec_btn, 50, LV_PART_MAIN | LV_STATE_DEFAULT);


// ui_Label11 = lv_label_create(ui_volume_dec_btn);
// lv_obj_set_width( ui_Label11, LV_SIZE_CONTENT);  /// 1
// lv_obj_set_height( ui_Label11, LV_SIZE_CONTENT);   /// 1
// lv_obj_set_align( ui_Label11, LV_ALIGN_CENTER );
// lv_label_set_text(ui_Label11,LV_SYMBOL_VOLUME_MID);
ui_img_reduceset = lv_img_create(ui_volume_dec_btn);
lv_img_set_src(ui_img_reduceset, &img_reduce);
lv_obj_set_align( ui_img_reduceset, LV_ALIGN_CENTER );

ui_Bar2 = lv_bar_create(ui_Panel3);
lv_bar_set_value(ui_Bar2,25,LV_ANIM_OFF);
lv_obj_set_width( ui_Bar2, 150);
lv_obj_set_height( ui_Bar2, 10);
lv_obj_set_x( ui_Bar2, -50 );
lv_obj_set_y( ui_Bar2, 0 );
lv_obj_set_align( ui_Bar2, LV_ALIGN_RIGHT_MID );
lv_obj_set_style_bg_color(ui_Bar2, lv_color_hex(0xc6c6c6), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_color(ui_Bar2, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT );


ui_volume_inc_btn = lv_btn_create(ui_Panel3);
lv_obj_set_width( ui_volume_inc_btn, 30);
lv_obj_set_height( ui_volume_inc_btn, 30);
lv_obj_set_align( ui_volume_inc_btn, LV_ALIGN_RIGHT_MID );
lv_obj_add_flag( ui_volume_inc_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_volume_inc_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_volume_inc_btn, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_radius(ui_volume_inc_btn, 50, LV_PART_MAIN | LV_STATE_DEFAULT);

// ui_Label8 = lv_label_create(ui_volume_inc_btn);
// lv_obj_set_width( ui_Label8, LV_SIZE_CONTENT);  /// 1
// lv_obj_set_height( ui_Label8, LV_SIZE_CONTENT);   /// 1
// lv_obj_set_align( ui_Label8, LV_ALIGN_CENTER );
// lv_label_set_text(ui_Label8,LV_SYMBOL_VOLUME_MAX);
ui_img_plusset = lv_img_create(ui_volume_inc_btn);
lv_img_set_src(ui_img_plusset, &img_plus);
lv_obj_set_align( ui_img_plusset, LV_ALIGN_CENTER );

ui_Panel4 = lv_obj_create(ui_menu_panel);
lv_obj_set_height( ui_Panel4, 50);
lv_obj_set_width( ui_Panel4, lv_pct(100));
lv_obj_set_x( ui_Panel4, 0 );
lv_obj_set_y( ui_Panel4, 130 );
lv_obj_set_align( ui_Panel4, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_Panel4, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_Panel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Panel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Panel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Panel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel4, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Panel4, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_btn_slot_dec = lv_btn_create(ui_Panel4);
lv_obj_set_width( ui_btn_slot_dec, 30);
lv_obj_set_height( ui_btn_slot_dec, 30);
lv_obj_set_align( ui_btn_slot_dec, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_btn_slot_dec, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_btn_slot_dec, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_btn_slot_dec, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_Label2 = lv_label_create(ui_btn_slot_dec);
lv_obj_set_width( ui_Label2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label2, LV_ALIGN_CENTER );
lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0x38393a), LV_STATE_DEFAULT);
lv_label_set_text(ui_Label2,"-");

ui_slot_label = lv_label_create(ui_Panel4);
lv_obj_set_width( ui_slot_label, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_slot_label, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_slot_label, LV_ALIGN_CENTER );
lv_label_set_text(ui_slot_label,"Save Slot 1");

ui_btn_slot_inc = lv_btn_create(ui_Panel4);
lv_obj_set_width( ui_btn_slot_inc, 30);
lv_obj_set_height( ui_btn_slot_inc, 30);
lv_obj_set_align( ui_btn_slot_inc, LV_ALIGN_RIGHT_MID );
lv_obj_add_flag( ui_btn_slot_inc, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_btn_slot_inc, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_btn_slot_inc, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_Label1 = lv_label_create(ui_btn_slot_inc);
lv_obj_set_width( ui_Label1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label1, LV_ALIGN_CENTER );
lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0x38393a), LV_STATE_DEFAULT);
lv_label_set_text(ui_Label1,"+");

ui_Panel2 = lv_obj_create(ui_menu_panel);
lv_obj_set_height( ui_Panel2, 100);
lv_obj_set_width( ui_Panel2, lv_pct(100));
lv_obj_set_x( ui_Panel2, 0 );
lv_obj_set_y( ui_Panel2, 180 );
lv_obj_set_align( ui_Panel2, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_Panel2, LV_OBJ_FLAG_EVENT_BUBBLE );   /// Flags
lv_obj_clear_flag( ui_Panel2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_Panel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Panel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Panel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Panel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_load_btn = lv_btn_create(ui_Panel2);
lv_obj_set_width( ui_load_btn, 50);
lv_obj_set_height( ui_load_btn, 40);
lv_obj_set_align( ui_load_btn, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_load_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_load_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_load_btn, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_Label4 = lv_label_create(ui_load_btn);
lv_obj_set_width( ui_Label4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label4, LV_ALIGN_CENTER );
lv_obj_set_style_text_color(ui_Label4, lv_color_hex(0x38393a), LV_STATE_DEFAULT);
lv_label_set_text(ui_Label4,"Load");

ui_slot_image = lv_img_create(ui_Panel2);
lv_obj_set_width( ui_slot_image, 80);
lv_obj_set_height( ui_slot_image, 60);
lv_obj_set_align( ui_slot_image, LV_ALIGN_RIGHT_MID );
lv_obj_add_flag( ui_slot_image, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_slot_image, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Panel1 = lv_obj_create(ui_menu_panel);
lv_obj_set_height( ui_Panel1, 100);
lv_obj_set_width( ui_Panel1, lv_pct(100));
lv_obj_set_x( ui_Panel1, 0 );
lv_obj_set_y( ui_Panel1, 280 );
lv_obj_set_align( ui_Panel1, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_Panel1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_Panel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Panel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Panel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Panel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_save_btn = lv_btn_create(ui_Panel1);
lv_obj_set_width( ui_save_btn, 50);
lv_obj_set_height( ui_save_btn, 40);
lv_obj_set_align( ui_save_btn, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_save_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_save_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_save_btn, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_Label3 = lv_label_create(ui_save_btn);
lv_obj_set_width( ui_Label3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label3, LV_ALIGN_CENTER );
lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0x38393a), LV_STATE_DEFAULT);
lv_label_set_text(ui_Label3,"Save");

ui_pause_image = lv_img_create(ui_Panel1);
lv_obj_set_width( ui_pause_image, 80);
lv_obj_set_height( ui_pause_image, 60);
lv_obj_set_align( ui_pause_image, LV_ALIGN_RIGHT_MID );
lv_obj_add_flag( ui_pause_image, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_pause_image, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Panel6 = lv_obj_create(ui_menu_panel);
lv_obj_set_height( ui_Panel6, 50);
lv_obj_set_width( ui_Panel6, lv_pct(100));
lv_obj_set_x( ui_Panel6, 0 );
lv_obj_set_y( ui_Panel6, 380 );
lv_obj_set_align( ui_Panel6, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_Panel6, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Panel6, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Panel6, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_Label9 = lv_label_create(ui_Panel6);
lv_obj_set_width( ui_Label9, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label9, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label9, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_Label9,"Video");

ui_Dropdown2 = lv_dropdown_create(ui_Panel6);
lv_dropdown_set_options( ui_Dropdown2, "Original\nFit" );
lv_obj_set_width( ui_Dropdown2, 150);
lv_obj_set_height( ui_Dropdown2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Dropdown2, LV_ALIGN_RIGHT_MID );
lv_obj_add_flag( ui_Dropdown2, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_set_style_bg_color(ui_Dropdown2, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_color(ui_Dropdown2, lv_color_hex(0x6f6f6f), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_reset_btn = lv_btn_create(ui_menu_panel);
lv_obj_set_width( ui_reset_btn, 100);
lv_obj_set_height( ui_reset_btn, 40);
lv_obj_set_x( ui_reset_btn, 20 );
lv_obj_set_y( ui_reset_btn, 400 );
lv_obj_set_align( ui_reset_btn, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_reset_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_reset_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_reset_btn, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_Label5 = lv_label_create(ui_reset_btn);
lv_obj_set_width( ui_Label5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label5, LV_ALIGN_CENTER );
lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0x38393a), LV_STATE_DEFAULT);
lv_label_set_text(ui_Label5,"Reset");


ui_quit_btn = lv_btn_create(ui_menu_panel);
lv_obj_set_width( ui_quit_btn, 100);
lv_obj_set_height( ui_quit_btn, 40);
lv_obj_set_x( ui_quit_btn, -20 );
lv_obj_set_y( ui_quit_btn, 400 );
lv_obj_set_align( ui_quit_btn, LV_ALIGN_RIGHT_MID );
lv_obj_add_flag( ui_quit_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_quit_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_quit_btn, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);


ui_Label7 = lv_label_create(ui_quit_btn);
lv_obj_set_width( ui_Label7, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label7, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label7, LV_ALIGN_CENTER );
lv_obj_set_style_text_color(ui_Label7, lv_color_hex(0x38393a), LV_STATE_DEFAULT);
lv_label_set_text(ui_Label7,"Quit");

}

void menu_ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_Screen1_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_Screen1);
}
