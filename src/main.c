#include <pebble.h>
#include "main.h"
#include <string.h>

    
#define KEY_BATTERY 0
#define BATTERY_KEY 1
#define KEY_COLOR 2
#define COLOR_KEY 3
  
  int BatteryINT;
  
static void layer_update_callback(Layer *layer, GContext* ctx) {
  // We make sure the dimensions of the GRect to draw into
  // are equal to the size of the bitmap--otherwise the image
  // will automatically tile. Which might be what *you* want.
  GSize image_size = gbitmap_get_bounds(s_image).size;
  graphics_draw_bitmap_in_rect(ctx, s_image, GRect(80, 101, 55, 55));
}

static void layer_update_callback2(Layer *layer, GContext* ctx) {
  // We make sure the dimensions of the GRect to draw into
  // are equal to the size of the bitmap--otherwise the image
  // will automatically tile. Which might be what *you* want.
  GSize image_size = gbitmap_get_bounds(s_image2).size;
  graphics_draw_bitmap_in_rect(ctx, s_image2, GRect(22, 142, 31, 20));
}

static void line_layer_update_callback(Layer *layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorIndigo); //sets color of background block
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}  
  
static void line_layer_update_callback2(Layer *layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorVividCerulean);  //sets color of top block
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
} 

static void line_layer_update_callback3(Layer *layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorIslamicGreen);  //sets color of bottom left block
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
} 

static void line_layer_update_callback3Red(Layer *layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorRed);  //sets color of bottom left block
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
} 

static void line_layer_update_callback3DBlue(Layer *layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorDukeBlue);  //sets color of bottom left block
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
} 

static void line_layer_update_callback4(Layer *layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorChromeYellow);  //sets color of bottom right block
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
} 

static void line_layer_update_callback4Mag(Layer *layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorMagenta);  //sets color of bottom right block
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
} 

static void line_layer_update_callback4DRed(Layer *layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorDarkCandyAppleRed );  //sets color of bottom right block
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
} 

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";
  static char buffer2[] = "Xxx";
  static char buffer2a[] = "00";
  static char buffer3[] = "Xxx";

  strftime(buffer3, sizeof(buffer3), "%a", tick_time);

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
    
      text_layer_set_text(s_time_layer, buffer);
  } else {
  // Use 12 hour format
  strftime(buffer, sizeof(buffer), "%I:%M", tick_time);
  text_layer_set_text(s_time_layer,buffer+(('0' == buffer[0])?1:0));  
}
  
  int bmin = BatteryINT;
  //if (bmin % 2) Even minutes
  
  if (tick_time->tm_min % bmin == 0)  // divisible by 5 if(tick_time->tm_min % 5 == 0)
  {
    layer_set_hidden(s_image_layer, false);
    layer_set_hidden(s_image_layer2, false);
    
    BatteryChargeState charge_state = battery_state_service_peek();
      if (charge_state.is_charging) 
      {
    snprintf(buffer3, sizeof(buffer3), "%d%%", charge_state.charge_percent);
       s_image2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATCHARGING);
       } 
       else if (charge_state.charge_percent==100||charge_state.charge_percent==90) 
      {
    snprintf(buffer3, sizeof(buffer3), "%d%%", charge_state.charge_percent);
       s_image2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT100);
       } 
        else if (charge_state.charge_percent==70||charge_state.charge_percent==80) 
      {
    snprintf(buffer3, sizeof(buffer3), "%d%%", charge_state.charge_percent);
       s_image2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT75);
       }
    else if (charge_state.charge_percent==50||charge_state.charge_percent==40||charge_state.charge_percent==60) 
      {
    snprintf(buffer3, sizeof(buffer3), "%d%%", charge_state.charge_percent);
       s_image2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT50);
       }
    else if (charge_state.charge_percent==20||charge_state.charge_percent==30) 
      {
    snprintf(buffer3, sizeof(buffer3), "%d%%", charge_state.charge_percent);
       s_image2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT25);
       } 
        else if (charge_state.charge_percent==10||charge_state.charge_percent==0) 
      {
    snprintf(buffer3, sizeof(buffer3), "%d%%", charge_state.charge_percent);
       s_image2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT00);
       } 
    else 
      {
    snprintf(buffer3, sizeof(buffer3), "%d%%", charge_state.charge_percent);
       s_image2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAT75);
      }
    
    strftime(buffer2, sizeof(buffer2), "%b", tick_time);    //Month
    text_layer_set_text(s_time_layer2, "");
    text_layer_set_text(s_time_layer2a, "");
    layer_set_update_proc(s_line_layer3, line_layer_update_callback3Red);
    layer_set_update_proc(s_line_layer4, line_layer_update_callback4Mag);
    
    if (bluetooth_connection_service_peek()) 
    {
       s_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BTC55);
    } 
    else 
    {
       s_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BTNC55);
    }
  }
  else           // even
  {
    layer_set_hidden(s_image_layer, true);
    layer_set_hidden(s_image_layer2, true);

    strftime(buffer2, sizeof(buffer2), "%b", tick_time);    //Month
    
    strftime(buffer2a, sizeof(buffer2a), "%e", tick_time);  //date
    strftime(buffer3, sizeof(buffer3), "%A", tick_time);   //day of Week
    text_layer_set_text(s_time_layer2, buffer2);
    text_layer_set_text(s_time_layer2a, buffer2a);
    
    layer_set_update_proc(s_line_layer3, line_layer_update_callback3);
    layer_set_update_proc(s_line_layer4, line_layer_update_callback4);
  }
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer3, buffer3);
}  
  
static void main_window_load(Window *window) {
       
  g_Color = GColorWhite;
    if (persist_exists(COLOR_KEY)) 
{
  char colorname[20];
  persist_read_string(COLOR_KEY, colorname, sizeof(colorname));
  if(strcmp(colorname, "GColorWhite") == 0){g_Color = GColorWhite;}
  else {g_Color = GColorBlack;}
    }
  
  //Creates Colored blocks
  GRect line_frame = GRect(0, 0, 144, 168);//Position for background block
  s_line_layer = layer_create(line_frame);  
  layer_set_update_proc(s_line_layer, line_layer_update_callback);
  layer_add_child(window_get_root_layer(window), s_line_layer);
  
  GRect line_frame2 = GRect(5, 5, 134, 84);//Position for top block
  s_line_layer2 = layer_create(line_frame2);
  layer_set_update_proc(s_line_layer2, line_layer_update_callback2);
  layer_add_child(window_get_root_layer(window), s_line_layer2);
  
  GRect line_frame3 = GRect(5, 94, 67, 69);//Position for bottom left block
  s_line_layer3 = layer_create(line_frame3);
  layer_set_update_proc(s_line_layer3, line_layer_update_callback3);
  layer_add_child(window_get_root_layer(window), s_line_layer3);
  
  GRect line_frame4 = GRect(77, 94, 62, 69);//Position for bottom right block
  s_line_layer4 = layer_create(line_frame4);
  layer_set_update_proc(s_line_layer4, line_layer_update_callback4);
  layer_add_child(window_get_root_layer(window), s_line_layer4);
  
  // Create top time TextLayer
  s_time_layer = text_layer_create(GRect(0, 13, 144, 80)); //Coordinates for Top Time display
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, g_Color); //Sets color for Top Time
  text_layer_set_text(s_time_layer, "15:45");
    // Improve the layout to be more like a watchface
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
    // Create GFont  
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SEGOE_NORMAL_52));
  //s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_HELVETICA_LIGHT_50));



    // Create top time TextLayer
  s_time_layer2 = text_layer_create(GRect(67, 90, 80, 50)); //Coordinates for Bottom Right Month display
  text_layer_set_background_color(s_time_layer2, GColorClear);
  text_layer_set_text_color(s_time_layer2, g_Color); //Sets color for bottom right month
  text_layer_set_text(s_time_layer2, "Jan");
    // Improve the layout to be more like a watchface
  text_layer_set_text_alignment(s_time_layer2, GTextAlignmentCenter);
  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer2));
    // Create GFont  
    s_time_font3 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SEGOE_NORMAL_30));
    //s_time_font3 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_HELVETICA_LIGHT_30));

  
    // Create top time TextLayer
  s_time_layer2a = text_layer_create(GRect(78, 118, 62, 50)); //Coordinates for Bottom right date display
  text_layer_set_background_color(s_time_layer2a, GColorClear);
  text_layer_set_text_color(s_time_layer2a, g_Color); //Sets color for bottom right date
  text_layer_set_text(s_time_layer2a, "15");
    // Improve the layout to be more like a watchface
  text_layer_set_text_alignment(s_time_layer2a, GTextAlignmentCenter);
  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer2a));
    s_time_font2 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SEGOE_NORMAL_40));
    //s_time_font2 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_HELVETICA_LIGHT_45));


    // Create top time TextLayer
  s_time_layer3 = text_layer_create(GRect(8, 108, 62, 50)); //Coordinates for Bottom left day display
  text_layer_set_background_color(s_time_layer3, GColorClear);
  text_layer_set_text_color(s_time_layer3, g_Color); //Sets color for bottom left day
  text_layer_set_text(s_time_layer3, "Mon");
    // Improve the layout to be more like a watchface
  text_layer_set_text_alignment(s_time_layer3, GTextAlignmentCenter);
  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer3));


// Apply to TextLayer
text_layer_set_font(s_time_layer, s_time_font);
text_layer_set_font(s_time_layer2, s_time_font3);  
text_layer_set_font(s_time_layer2a, s_time_font2);  
text_layer_set_font(s_time_layer3, s_time_font3);  
  
  Layer *window_layer = window_get_root_layer(s_main_window);
  GRect bounds = layer_get_frame(window_layer);

  s_image_layer = layer_create(bounds);
  layer_set_update_proc(s_image_layer, layer_update_callback);
  layer_add_child(window_layer, s_image_layer);
  
  s_image_layer2 = layer_create(bounds);
  layer_set_update_proc(s_image_layer2, layer_update_callback2);
  layer_add_child(window_layer, s_image_layer2);
  
  if (persist_exists(BATTERY_KEY)) 
{
  char Battery_name[20];
  persist_read_string(BATTERY_KEY, Battery_name, sizeof(Battery_name));
  if(strcmp(Battery_name, "Never") == 0){}
      else if(strcmp(Battery_name, "Odd_Minutes") == 0){BatteryINT=2;}
      else if(strcmp(Battery_name, "3_Minutes") == 0){BatteryINT=3;}
      else if(strcmp(Battery_name, "5_Minutes") == 0){BatteryINT=5;}
      else if(strcmp(Battery_name, "10_Minutes") == 0){BatteryINT=10;}
      else if(strcmp(Battery_name, "15_Minutes") == 0){BatteryINT=15;}
      else {BatteryINT=2;}
}
}

static void main_window_unload(Window *window) {
    // Destroy TextLayer
    text_layer_destroy(s_time_layer);
    text_layer_destroy(s_time_layer2);
    text_layer_destroy(s_time_layer2a);
    text_layer_destroy(s_time_layer3);

    // Unload GFont
    fonts_unload_custom_font(s_time_font);
    fonts_unload_custom_font(s_time_font2);
    fonts_unload_custom_font(s_time_font3);

  // Unload blocks
    layer_destroy(s_line_layer);
    layer_destroy(s_line_layer2);
    layer_destroy(s_line_layer3);
    layer_destroy(s_line_layer4);
  
  gbitmap_destroy(s_image);
  layer_destroy(s_image_layer);
  
  gbitmap_destroy(s_image2);
  layer_destroy(s_image_layer2);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void in_recv_handler(DictionaryIterator *iterator, void *context)
{
  //Get Tuple
  Tuple *t = dict_read_first(iterator);

    // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
      case KEY_COLOR:
      if(strcmp(t->value->cstring, "GColorWhite") == 0)
      {
        //Set and save the color 
        g_Color = GColorWhite;
        
        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else
      {
        //Set and save the color 
        g_Color = GColorBlack;
        
        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      text_layer_set_text_color(s_time_layer, g_Color); //Sets color for Top Time
      text_layer_set_text_color(s_time_layer3, g_Color); //Sets color for bottom left day
      text_layer_set_text_color(s_time_layer2, g_Color); //Sets color for bottom right date
      text_layer_set_text_color(s_time_layer2a, g_Color); //Sets color for bottom right date

      break;
    case KEY_BATTERY:
      //It's the KEY_COLOR key
      if(strcmp(t->value->cstring, "Never") == 0)
      {
        //Set and save the battery times 
        BatteryINT=100;
        persist_write_string(BATTERY_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "Odd_Minutes") == 0)
      {
        //Set and save the battery times 
        BatteryINT=2;
        persist_write_string(BATTERY_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "3_Minutes") == 0)
      {
        //Set and save the battery times 
        BatteryINT=3;
        persist_write_string(BATTERY_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "5_Minutes") == 0)
      {
        //Set and save the battery times 
        BatteryINT=5;
        persist_write_string(BATTERY_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "10_Minutes") == 0)
      {
        //Set and save the battery times 
        BatteryINT=10;
        persist_write_string(BATTERY_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "15_Minutes") == 0)
      {
        //Set and save the battery times 
        BatteryINT=15;
        persist_write_string(BATTERY_KEY, t->value->cstring);
      }
      else {BatteryINT=2;persist_write_string(BATTERY_KEY, t->value->cstring);}
      break;
    }
          // Look for next item
    t = dict_read_next(iterator);
  }
}
  
static void init() {
  
  // Create main Window element and assign to pointer
  s_main_window = window_create();
  
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  app_message_register_inbox_received((AppMessageInboxReceived) in_recv_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Make sure the time is displayed from the start
  update_time();
}

static void deinit() {
  
    // Destroy Window
    window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}