#ifndef CS123X_H
#define CS123X_H
#define  MD_CS213X_CLK               P0.1
#define  MD_CS123X_DATA              P0.2
#define  MD_CS123X_DATA_DIR          PM0.2
typedef struct _CS123X_COMPONENTS
{
	char desc[32];
	struct _CS123X_COMPONENTS *this;
	void (*const power_down)(void); //
	void (*const restart)(void);// 
	int (*const Init )(unsigned char dat);     
	int (*const read_adc)(long *const ad);   // 
	unsigned char (*const read_reg )(long * ad);         
	void (*const write_reg )(long *ad,unsigned char dat);      
	
}cs123x_comps_t;

extern cs123x_comps_t cs123x_comps;
#endif