class fanbus_rgb_fan
{
	public:
		fanbus_rgb_fan(char addr);

		//Get Device Information (FanBus 2.0)
		char get_device_type();
		void get_device_name(char * name);
		
		//Set New Address (reserved for FanBus 2.0 protocol)
		void set_addr(char addr);

		//Set and Get Fan Speed
		void set_fan(char spd);
		char get_fan();

		//Set and Get LED Value
		void set_led(char led, char val);
		char get_led(char led);

		//Update LED's (reserved for FanBus 2.0 protocol)
		void update_leds();
		
		//Save state to device
		void save_state();

		//Load from device
		void load_state();
		
	private:
		serial_port port;
}
