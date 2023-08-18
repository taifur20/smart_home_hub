/*
 * grovecam.h
 *
 *  Created on: Aug 17, 2023
 *      Author: khair
 */

#ifndef INC_GROVECAM_H_
#define INC_GROVECAM_H_

#define PIC_PKT_LEN    128                  //data length of each read, dont set this too big because ram is limited
#define PIC_FMT_VGA    7
#define PIC_FMT_CIF    5
#define PIC_FMT_OCIF   3
#define CAM_ADDR       0
#define CAM_SERIAL     Serial

#define PIC_FMT        PIC_FMT_VGA

void initialize();
void CaptureImage();
void GetData();


#endif /* INC_GROVECAM_H_ */
