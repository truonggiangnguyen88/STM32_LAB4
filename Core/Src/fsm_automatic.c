/*
 * run_traffic_light.c
 *
 *  Created on: Oct 21, 2024
 *      Author: ASUS
 */
#include "fsm_automatic.h"
#include "global.h"

void fsm_automatic(){
	switch(status){
		case INIT:
			//clear_all_led();
			timeWay1 = timeRed;
			timeWay2 = timeGreen;
			status = RED1_GREEN2;
			mode = 1;
			counter = 4;
			break;

		case RED1_GREEN2:
			red1_and_green2();

				if(counter <= 0){
					counter = 4;

					if(timeWay1 > 0){
						timeWay1--;
					}
					if(timeWay2 > 0){
						timeWay2--;
					}
				}

				scan_7SEG();
				 counter--;
				if(timeWay2 == 0){
					timeWay2 = timeYellow;
					status = RED1_YELLOW2;
					counter = 4;
				}

				if(is_button_pressed(0) == 1){
					status = SETTING_RED;
					mode = 2;
					setTimer(3, 5);
					selected_duration = timeRed;
					duration_red = timeRed;
					clear_all_led();
				}
			break;

		case RED1_YELLOW2:
			red1_and_yellow2();

			if(counter <= 0){
				counter = 4;

				if(timeWay1 > 0){
					timeWay1--;
				}
				if(timeWay2 > 0){
					timeWay2--;
				}
			}
			scan_7SEG();
			 counter--;
			if(timeWay1 == 0){
				timeWay1 = timeGreen;
				timeWay2 = timeRed;
				status = GREEN1_RED2;
				counter = 4;
			}

			if(is_button_pressed(0) == 1){
				status = SETTING_RED;
				mode = 2;
				setTimer(3, 5);
				selected_duration = timeRed;
				duration_red = timeRed;
				clear_all_led();
			}
			break;

		case GREEN1_RED2:
			    green1_and_red2();
				if(counter <= 0){
					counter = 4;

					if(timeWay1 > 0){
						timeWay1--;
					}
					if(timeWay2 > 0){
						timeWay2--;
					}
				}
				scan_7SEG();
				counter--;

				if(timeWay1 == 0){
					timeWay1 = timeYellow;
					status = YELLOW1_RED2;
					counter = 4;
				}

				if(is_button_pressed(0) == 1){
					status = SETTING_RED;
					mode = 2;
					setTimer(3, 5);
					selected_duration = timeRed;
					duration_red = timeRed;
					clear_all_led();
				}
			break;

		case YELLOW1_RED2:
				yellow1_and_red2();
				if(counter <= 0){
					counter = 4;

					if(timeWay1 > 0){
						timeWay1--;
					}
					if(timeWay2 > 0){
						timeWay2--;
					}
				}
				scan_7SEG();
				counter--;

				if(timeWay2 == 0){
					timeWay1 = timeRed;
					timeWay2 = timeGreen;
					status = RED1_GREEN2;
					counter = 4;
				}

				if(is_button_pressed(0) == 1){
					status = SETTING_RED;
					mode = 2;
					setTimer(3, 5);
					selected_duration = timeRed;
					duration_red = timeRed;
					clear_all_led();
				}
			break;

		default:
			break;
		}
}

//void fsm_automatic(){
//	switch(status){
//		case INIT:
//			clear_all_led();
//			timeWay1 = timeRed;
//			timeWay2 = timeGreen;
//			status = RED1_GREEN2;
//			mode = 1;
//			setTimer(0, timeGreen*100);
//			setTimer(1, 5);
//			setTimer(2, 5);
//			setTimer(3, 13);
//			setTimer(4, 17);
//			break;
//
//		case RED1_GREEN2:
//			red1_and_green2();
//			if(timer_flag1[0] == 1){
//				setTimer(0, timeYellow*100);
//				status = RED1_YELLOW2;
//				timeWay2 = timeYellow;
//			}
//
//			if(timer_flag1[1] == 1){
//				setTimer(1, 100);
//				timeWay1--;
//				timeWay2--;
//			}
//
//			if(is_button_pressed(0) == 1){
//				status = SETTING_RED;
//				mode = 2;
//				setTimer(3, 5);
//				selected_duration = timeRed;
//				duration_red = timeRed;
//				clear_all_led();
//			 }
//			scan_7SEG();
//			break;
//
//		case RED1_YELLOW2:
//			red1_and_yellow2();
//			if(timer_flag1[0] == 1){
//				setTimer(0, timeGreen*100);
//				status = GREEN1_RED2;
//				timeWay1 = timeGreen;
//				timeWay2 = timeRed;
//			}
//			if(timer_flag1[1] == 1){
//				setTimer(1, 100);
//				timeWay1--;
//				timeWay2--;
//			}
//
//			if(is_button_pressed(0) == 1){
//				status = SETTING_RED;
//				mode = 2;
//				setTimer(3, 5);
//				selected_duration = timeRed;
//				duration_red = timeRed;
//				clear_all_led();
//			 }
//			scan_7SEG();
//			break;
//
//		case GREEN1_RED2:
//			green1_and_red2();
//			if(timer_flag1[0] == 1){
//				setTimer(0, timeYellow*100);
//				status = YELLOW1_RED2;
//				timeWay1 = timeYellow;
//				//timeWay2 = timeYellow;
//			}
//			if(timer_flag1[1] == 1){
//				setTimer(1, 100);
//				timeWay1--;
//				timeWay2--;
//			}
//
//			if(is_button_pressed(0) == 1){
//				status = SETTING_RED;
//				mode = 2;
//				setTimer(3, 5);
//				selected_duration = timeRed;
//				duration_red = timeRed;
//				clear_all_led();
//			 }
//			scan_7SEG();
//			break;
//
//		case YELLOW1_RED2:
//			yellow1_and_red2();
//			if(timer_flag1[0] == 1){
//				setTimer(0, timeGreen*100);
//				status = RED1_GREEN2;
//				timeWay1 = timeRed;
//				timeWay2 = timeGreen;
//			}
//			if(timer_flag1[1] == 1){
//				setTimer(1, 100);
//				timeWay1--;
//				timeWay2--;
//			}
//
//			if(is_button_pressed(0) == 1){
//				status = SETTING_RED;
//				mode = 2;
//				setTimer(3, 5);
//				selected_duration = timeRed;
//				duration_red = timeRed;
//				clear_all_led();
//			 }
//			scan_7SEG();
//			break;
//		default:
//			break;
//		}
//}
//
