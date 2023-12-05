// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.2.0
// Project name: menu

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
ui_Screen1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_menu_panel = lv_obj_create(ui_Screen1);
lv_obj_set_width( ui_menu_panel, lv_pct(100));
lv_obj_set_height( ui_menu_panel, lv_pct(100));
lv_obj_set_align( ui_menu_panel, LV_ALIGN_CENTER );

ui_menu_title = lv_label_create(ui_menu_panel);
lv_obj_set_width( ui_menu_title, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_menu_title, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_menu_title, LV_ALIGN_TOP_RIGHT );
lv_label_set_text(ui_menu_title,"Emulation Paused");

ui_fps_label = lv_label_create(ui_menu_panel);
lv_obj_set_width( ui_fps_label, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_fps_label, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_fps_label, 0 );
lv_obj_set_y( ui_fps_label, 20 );
lv_obj_set_align( ui_fps_label, LV_ALIGN_TOP_RIGHT );
lv_label_set_text(ui_fps_label,"200.5 FPS");

ui_resume_btn = lv_btn_create(ui_menu_panel);
lv_obj_set_width( ui_resume_btn, 100);
lv_obj_set_height( ui_resume_btn, 40);
lv_obj_add_flag( ui_resume_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_resume_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label6 = lv_label_create(ui_resume_btn);
lv_obj_set_width( ui_Label6, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label6, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label6, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label6,"Resume");

ui_Panel3 = lv_obj_create(ui_menu_panel);
lv_obj_set_height( ui_Panel3, 50);
lv_obj_set_width( ui_Panel3, lv_pct(100));
lv_obj_set_x( ui_Panel3, 0 );
lv_obj_set_y( ui_Panel3, 50 );
lv_obj_set_align( ui_Panel3, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_Panel3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_Panel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Panel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Panel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Panel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_volume_mute_btn = lv_btn_create(ui_Panel3);
lv_obj_set_width( ui_volume_mute_btn, 30);
lv_obj_set_height( ui_volume_mute_btn, 30);
lv_obj_set_align( ui_volume_mute_btn, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_volume_mute_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_volume_mute_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label10 = lv_label_create(ui_volume_mute_btn);
lv_obj_set_width( ui_Label10, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label10, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label10, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label10,LV_SYMBOL_MUTE);

ui_volume_dec_btn = lv_btn_create(ui_Panel3);
lv_obj_set_width( ui_volume_dec_btn, 30);
lv_obj_set_height( ui_volume_dec_btn, 30);
lv_obj_set_x( ui_volume_dec_btn, 35 );
lv_obj_set_y( ui_volume_dec_btn, 0 );
lv_obj_set_align( ui_volume_dec_btn, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_volume_dec_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_volume_dec_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label11 = lv_label_create(ui_volume_dec_btn);
lv_obj_set_width( ui_Label11, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label11, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label11, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label11,LV_SYMBOL_VOLUME_MID);

ui_Bar2 = lv_bar_create(ui_Panel3);
lv_bar_set_value(ui_Bar2,25,LV_ANIM_OFF);
lv_obj_set_width( ui_Bar2, 150);
lv_obj_set_height( ui_Bar2, 10);
lv_obj_set_x( ui_Bar2, -50 );
lv_obj_set_y( ui_Bar2, 0 );
lv_obj_set_align( ui_Bar2, LV_ALIGN_RIGHT_MID );

ui_volume_inc_btn = lv_btn_create(ui_Panel3);
lv_obj_set_width( ui_volume_inc_btn, 30);
lv_obj_set_height( ui_volume_inc_btn, 30);
lv_obj_set_align( ui_volume_inc_btn, LV_ALIGN_RIGHT_MID );
lv_obj_add_flag( ui_volume_inc_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_volume_inc_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label8 = lv_label_create(ui_volume_inc_btn);
lv_obj_set_width( ui_Label8, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label8, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label8, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label8,LV_SYMBOL_VOLUME_MAX);

ui_Panel5 = lv_obj_create(ui_menu_panel);
lv_obj_set_height( ui_Panel5, 50);
lv_obj_set_width( ui_Panel5, lv_pct(100));
lv_obj_set_x( ui_Panel5, 0 );
lv_obj_set_y( ui_Panel5, 100 );
lv_obj_set_align( ui_Panel5, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_Panel5, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_Panel5, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Panel5, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Panel5, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Panel5, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_brightness_dec_btn = lv_btn_create(ui_Panel5);
lv_obj_set_width( ui_brightness_dec_btn, 30);
lv_obj_set_height( ui_brightness_dec_btn, 30);
lv_obj_set_align( ui_brightness_dec_btn, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_brightness_dec_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_brightness_dec_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label13 = lv_label_create(ui_brightness_dec_btn);
lv_obj_set_width( ui_Label13, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label13, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label13, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label13,LV_SYMBOL_MINUS);

ui_brightness_bar = lv_bar_create(ui_Panel5);
lv_bar_set_value(ui_brightness_bar,25,LV_ANIM_OFF);
lv_obj_set_width( ui_brightness_bar, 185);
lv_obj_set_height( ui_brightness_bar, 10);
lv_obj_set_align( ui_brightness_bar, LV_ALIGN_CENTER );

ui_brightness_inc_btn = lv_btn_create(ui_Panel5);
lv_obj_set_width( ui_brightness_inc_btn, 30);
lv_obj_set_height( ui_brightness_inc_btn, 30);
lv_obj_set_align( ui_brightness_inc_btn, LV_ALIGN_RIGHT_MID );
lv_obj_add_flag( ui_brightness_inc_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_brightness_inc_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label14 = lv_label_create(ui_brightness_inc_btn);
lv_obj_set_width( ui_Label14, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label14, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label14, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label14,LV_SYMBOL_PLUS);

ui_Panel4 = lv_obj_create(ui_menu_panel);
lv_obj_set_height( ui_Panel4, 50);
lv_obj_set_width( ui_Panel4, lv_pct(100));
lv_obj_set_x( ui_Panel4, 0 );
lv_obj_set_y( ui_Panel4, 150 );
lv_obj_set_align( ui_Panel4, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_Panel4, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_Panel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Panel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Panel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Panel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_btn_slot_dec = lv_btn_create(ui_Panel4);
lv_obj_set_width( ui_btn_slot_dec, 30);
lv_obj_set_height( ui_btn_slot_dec, 30);
lv_obj_set_align( ui_btn_slot_dec, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_btn_slot_dec, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_btn_slot_dec, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label2 = lv_label_create(ui_btn_slot_dec);
lv_obj_set_width( ui_Label2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label2, LV_ALIGN_CENTER );
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

ui_Label1 = lv_label_create(ui_btn_slot_inc);
lv_obj_set_width( ui_Label1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label1, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label1,"+");

ui_Panel2 = lv_obj_create(ui_menu_panel);
lv_obj_set_height( ui_Panel2, 100);
lv_obj_set_width( ui_Panel2, lv_pct(100));
lv_obj_set_x( ui_Panel2, 0 );
lv_obj_set_y( ui_Panel2, 200 );
lv_obj_set_align( ui_Panel2, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_Panel2, LV_OBJ_FLAG_EVENT_BUBBLE );   /// Flags
lv_obj_clear_flag( ui_Panel2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_Panel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Panel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Panel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Panel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_load_btn = lv_btn_create(ui_Panel2);
lv_obj_set_width( ui_load_btn, 50);
lv_obj_set_height( ui_load_btn, 40);
lv_obj_set_align( ui_load_btn, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_load_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_load_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label4 = lv_label_create(ui_load_btn);
lv_obj_set_width( ui_Label4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label4, LV_ALIGN_CENTER );
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
lv_obj_set_y( ui_Panel1, 300 );
lv_obj_set_align( ui_Panel1, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_Panel1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_Panel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Panel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Panel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Panel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_save_btn = lv_btn_create(ui_Panel1);
lv_obj_set_width( ui_save_btn, 50);
lv_obj_set_height( ui_save_btn, 40);
lv_obj_set_align( ui_save_btn, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_save_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_save_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label3 = lv_label_create(ui_save_btn);
lv_obj_set_width( ui_Label3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label3, LV_ALIGN_CENTER );
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
lv_obj_set_y( ui_Panel6, 400 );
lv_obj_set_align( ui_Panel6, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_Panel6, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label9 = lv_label_create(ui_Panel6);
lv_obj_set_width( ui_Label9, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label9, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label9, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_Label9,"Video");

ui_Dropdown2 = lv_dropdown_create(ui_Panel6);
lv_dropdown_set_options( ui_Dropdown2, "Original\nFit\nFill" );
lv_obj_set_width( ui_Dropdown2, 150);
lv_obj_set_height( ui_Dropdown2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Dropdown2, LV_ALIGN_RIGHT_MID );
lv_obj_add_flag( ui_Dropdown2, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags



ui_reset_btn = lv_btn_create(ui_menu_panel);
lv_obj_set_width( ui_reset_btn, 100);
lv_obj_set_height( ui_reset_btn, 40);
lv_obj_set_x( ui_reset_btn, 0 );
lv_obj_set_y( ui_reset_btn, 455 );
lv_obj_add_flag( ui_reset_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_reset_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label5 = lv_label_create(ui_reset_btn);
lv_obj_set_width( ui_Label5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label5, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label5,"Reset");

ui_quit_btn = lv_btn_create(ui_menu_panel);
lv_obj_set_width( ui_quit_btn, 100);
lv_obj_set_height( ui_quit_btn, 40);
lv_obj_set_x( ui_quit_btn, 0 );
lv_obj_set_y( ui_quit_btn, 455 );
lv_obj_set_align( ui_quit_btn, LV_ALIGN_TOP_RIGHT );
lv_obj_add_flag( ui_quit_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_quit_btn, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label7 = lv_label_create(ui_quit_btn);
lv_obj_set_width( ui_Label7, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label7, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label7, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label7,"Quit");

}
