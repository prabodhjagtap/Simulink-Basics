#include "Subsystem.h"

/* Block states (default storage) */
DW_Subsystem_T Subsystem_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Subsystem_T Subsystem_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Subsystem_T Subsystem_Y;

/* Real-time model */
static RT_MODEL_Subsystem_T Subsystem_M_;
RT_MODEL_Subsystem_T *const Subsystem_M = &Subsystem_M_;

/* Model output function */
void Subsystem_output(void)
{
  /* Outputs for Atomic SubSystem: '<Root>/Subsystem' */
  /* Switch: '<S1>/Switch' incorporates:
   *  Inport: '<Root>/Inport'
   *  Switch: '<S1>/Switch1'
   */
  if (Subsystem_U.Inport >= 5.0) {
    /* Outport: '<Root>/Out1' incorporates:
     *  Constant: '<S1>/Constant'
     */
    Subsystem_Y.Out1 = 1.0;
  } else if (Subsystem_U.Inport > -5.0) {
    /* Switch: '<S1>/Switch1' incorporates:
     *  Delay: '<S1>/Delay'
     *  Outport: '<Root>/Out1'
     */
    Subsystem_Y.Out1 = Subsystem_DW.Delay_DSTATE[0];
  } else {
    /* Outport: '<Root>/Out1' incorporates:
     *  Constant: '<S1>/Constant2'
     *  Switch: '<S1>/Switch1'
     */
    Subsystem_Y.Out1 = 0.0;
  }

  /* End of Switch: '<S1>/Switch' */
  /* End of Outputs for SubSystem: '<Root>/Subsystem' */
}

/* Model update function */
void Subsystem_update(void)
{
  /* Update for Atomic SubSystem: '<Root>/Subsystem' */
  /* Update for Delay: '<S1>/Delay' incorporates:
   *  Outport: '<Root>/Out1'
   */
  Subsystem_DW.Delay_DSTATE[0] = Subsystem_DW.Delay_DSTATE[1];
  Subsystem_DW.Delay_DSTATE[1] = Subsystem_Y.Out1;

  /* End of Update for SubSystem: '<Root>/Subsystem' */
}

/* Model initialize function */
void Subsystem_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void Subsystem_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
