
#define	WHOAMI_LPS25_PRS	0xBD	/*	Expctd content for WAI	*/

/*	CONTROL REGISTERS	/
#define	REF_P_XL	0x08	/	pressure reference	/
#define	REF_P_L	0x09	/	pressure reference	/
#define	REF_P_H	0x0A	/	pressure reference	/
#define	REF_T_L	0x0B	/	temperature reference	/
#define	REF_T_H	0x0C	/	temperature reference	*/

#define	WHO_AM_I	0x0F	/*	WhoAmI register	*/

#define	RESOL_CONF	0x10	/*	Pres Temp resolution set*/
#define	TP_RESOL	0x10	/*	Pres Temp resolution set*/

#define	DGAIN_L	0x18	/*	Dig Gain (3 regs)	*/

#define	CTRL_REG1	0x20	/*	power / ODR control reg	/
#define	CTRL_REG2	0x21	/	boot reg	/
#define	CTRL_REG3	0x22	/	interrupt control reg	/
#define	CTRL_REG4	0x23	/	interrupt control reg	/
#define	INT_CFG_REG	0x24	/	interrupt config reg	/
#define	INT_SRC_REG	0x25	/	interrupt source reg	*/

#define	STATUS_REG	0X27	/*	status reg	*/

#define	PRESS_OUT_XL	0x28	/*	press output (3 regs)	/
#define	TEMP_OUT_L	0x2B	/	temper output (2 regs)	*/

#define	FIFO_CTRL	0x2E
#define	FIFO_STATUS	0x2F

#define	THS_P_L	0x30	/*	pressure threshold	/
#define	THS_P_H	0x31	/	pressure threshold	*/

#define	RPDS_TRM_L	0x39	/*	NEW	/
#define	RPDS_TRM_H	0x3A	/	NEW	*/

/*	REGISTERS ALIASES	*/
#define	P_REF_INDATA_REG	REF_P_XL
#define	T_REF_INDATA_REG	REF_T_L
#define	P_THS_INDATA_REG	THS_P_L
#define	P_OUTDATA_REG	PRESS_OUT_XL
#define	T_OUTDATA_REG	TEMP_OUT_L
#define	OUTDATA_REG	PRESS_OUT_XL

/* /
#define	ENABLE_MASK	0x80	/ ctrl_reg1 /
#define	ODR_MASK	0x70	/ ctrl_reg1 /
#define	DIFF_MASK	0x08	/ ctrl_reg1 /
#define	BDU_MASK	0x04	/ ctrl_reg1 /
#define	RESET_AZ	0x02	/ ctrl_reg1 */

#define	AUTOZ_MASK	0x02	/* ctrl_reg2 /
#define	AUTOZ_ON	0x02	/ Enab AutoZero Function /
#define	AUTOZ_OFF	0x00	/ Disab Difference Function /
/ Pressure Sensor Operating Mode */
#define	AUTOZ_ENABLE	1
#define	AUTOZ_DISABLE	0

#define	LPS25_PRS_DELTA_EN_MASK	0x02	/* ctrl_reg1 /
#define	LPS25_PRS_AUTOZ_MASK	0x02	/ ctrl_reg2 */

#define	LPS25_PRS_RESET_AZ_MASK	0x02	/* ctrl_reg1 */

#define	PM_NORMAL	0x80	/* Power Normal Mode*/
#define	PM_OFF	0x00	/* Power Down */

#define	LPS25_PRS_DIFF_ON	0x08	/* En Difference circuitry /
#define	LPS25_PRS_DIFF_OFF	0x00	/ Dis Difference circuitry */

#define	LPS25_PRS_AUTOZ_ON	0x02	/* En AutoZero Function /
#define	LPS25_PRS_AUTOZ_OFF	0x00	/ Dis Difference Function */

#define	LPS25_PRS_BDU_ON	0x04	/* En BDU Block Data Upd */

#define	RES_AVGTEMP_064	0X0C
#define	RES_AVGTEMP_032	0X08

#define	RES_AVGPRES_512	0X03
#define	RES_AVGPRES_128	0X02

#define	RES_MAX	(RES_AVGTEMP_064 | RES_AVGPRES_512)	/* Max Resol. */

#define	LPS25_PRS_DELTA_EN_ON	0x02	/* En Delta Press registers */

#define	FUZZ	0
#define	FLAT	0

#define FIFO_MODE_MASK	0xE0	// 3 MSB FIFO_CTRL: Mode
#define FIFO_SAMPLE_MASK	0x1F	// 5 LSB FIFO_CTRL: Num Samples

#define	I2C_AUTO_INCREMENT	0x80

#define I2C_RETRY_DELAY	5
#define I2C_RETRIES	5

/* RESUME STATE INDICES */
#define	RES_REF_P_XL	0
#define	RES_REF_P_L	1
#define	RES_REF_P_H	2
#define	RES_REFT_L	3
#define	RES_REFT_H	4
//#define	LPS25_RES_TP_RESOL	5
#define	RES_RESOL_CONF	5
#define	RES_CTRL_REG1	6
#define	RES_CTRL_REG2	7
#define	RES_CTRL_REG3	8
#define	RES_CTRL_REG4	9
#define	RES_INT_CFG_REG	10
#define	RES_FIFO_CTRL	11
#define	RES_THS_P_L	12
#define	RES_THS_P_H	13
#define	RES_RPSD_TRIM_L	14
#define	RES_RPSD_TRIM_H	15

#define	RESUME_ENTRIES	16

/* end RESUME STATE INDICES */

/* Pressure Sensor Operating Mode */
#define	LPS25_PRS_DIFF_ENABLE	1
#define LPS25_PRS_DIFF_DISABLE	0
#define	LPS25_PRS_AUTOZ_ENABLE	1
#define	LPS25_PRS_AUTOZ_DISABLE	0

#define	BDU_ON	0x04	/* En BDU Block Data Upd */