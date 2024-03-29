float danbai_output;
float danbai_error;
const float danbai_desired=0,danbai_dt=1;
PidObject* danbai;
float kp=1,ki=0.5,kd=1;


pidInit(danbai, danbai_desired, kp,ki,kd, danbai_dt);//初始化


while(1)
{
                  danbai_error=danbai->desired-pitch;
   	  danbai_output=pidUpdate(danbai, danbai_error);


}

void pidInit(PidObject* pid, const float desired, float kp,float ki,float kd, const float dt)
{
	pid->error     = 0;
	pid->prevError = 0;
	pid->integ     = 0;
	pid->deriv     = 0;
	pid->desired = desired;
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	pid->iLimit    = DEFAULT_PID_INTEGRATION_LIMIT;
	pid->iLimitLow = -DEFAULT_PID_INTEGRATION_LIMIT;
	pid->dt        = dt;
}


float pidUpdate(PidObject* pid, const float error)
{
	float output;

	pid->error = error;   

	pid->integ += pid->error * pid->dt;
	if (pid->integ > pid->iLimit)
	{
		pid->integ = pid->iLimit;
	}
	else if (pid->integ < pid->iLimitLow)
	{
		pid->integ = pid->iLimitLow;
	}

	pid->deriv = (pid->error - pid->prevError) / pid->dt;

	pid->outP = pid->kp * pid->error;
	pid->outI = pid->ki * pid->integ;
	pid->outD = pid->kd * pid->deriv;

	output = pid->outP + pid->outI + pid->outD;

	pid->prevError = pid->error;

	return output;
}

typedef struct
{
	float desired;		//< set point
	float error;        //< error
	float prevError;    //< previous error
	float integ;        //< integral
	float deriv;        //< derivative
	float kp;           //< proportional gain
	float ki;           //< integral gain
	float kd;           //< derivative gain
	float outP;         //< proportional output (debugging)
	float outI;         //< integral output (debugging)
	float outD;         //< derivative output (debugging)
	float iLimit;       //< integral limit
	float iLimitLow;    //< integral limit
	float dt;           //< delta-time dt
} PidObject;