
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#include "engine.h"

void Util__ctx_type_3_init(Util__ctx_type_3 &_output_){
   Util__ctx_type_3 _ctx;
   _ctx.y1 = 0.0f;
   _ctx.x1 = 0.0f;
   _output_ = _ctx;
   return ;
}

float Util_dcblock(Util__ctx_type_3 &_ctx, float x0){
   float y0;
   y0 = (x0 + (- _ctx.x1) + (0.995f * _ctx.y1));
   _ctx.x1 = x0;
   _ctx.y1 = y0;
   return y0;
}

void Adsr__ctx_type_0_init(Adsr__ctx_type_0 &_output_){
   Adsr__ctx_type_0 _ctx;
   _ctx.target = 0.0f;
   _ctx.state = 0;
   _ctx.scale = 0.0f;
   _ctx.rate = 0.0f;
   _ctx.out = 0.0f;
   Util__ctx_type_4_init(_ctx._inst955);
   Util__ctx_type_0_init(_ctx._inst251);
   _output_ = _ctx;
   return ;
}

float Adsr_do(Adsr__ctx_type_0 &_ctx, float gate, float a, float d, float s, float r){
   float a_rate;
   a_rate = (1.f / (0.01f + (100.f * a)));
   float d_rate;
   d_rate = (1.f / (0.01f + (100.f * d)));
   float r_rate;
   r_rate = (1.f / (0.01f + (100.f * r)));
   _ctx.out = (_ctx.out + (0.004f * _ctx.rate * (_ctx.target + (- _ctx.out))));
   uint8_t bgate;
   bgate = (gate > 0.0f);
   if(_ctx.state == 0){
      if(Util_edge(_ctx._inst251,bgate)){
         _ctx.state = 1;
         _ctx.scale = (0.2f * gate);
      }
      _ctx.rate = r_rate;
      _ctx.target = 0.0f;
   }
   if(_ctx.state == 1){
      if(bool_not(bgate)){
         _ctx.state = 0;
      }
      if(_ctx.out > 1024.f){
         _ctx.state = 2;
      }
      _ctx.rate = a_rate;
      _ctx.target = 1228.8f;
   }
   if(_ctx.state == 2){
      if(bool_not(bgate)){
         _ctx.state = 0;
      }
      _ctx.rate = d_rate;
      _ctx.target = (1024.f * s);
   }
   return (Util_smooth(_ctx._inst955,_ctx.scale) * float_clip((0.0009765625f * _ctx.out),0.0f,1.f));
}

void Adsr__ctx_type_1_init(Adsr__ctx_type_1 &_output_){
   Adsr__ctx_type_1 _ctx;
   _ctx.knob4 = 0.0f;
   _ctx.knob3 = 0.0f;
   _ctx.knob2 = 0.0f;
   _ctx.knob1 = 0.0f;
   Adsr__ctx_type_0_init(_ctx._inst16);
   _output_ = _ctx;
   return ;
}

void Adsr_controlChange(Adsr__ctx_type_1 &_ctx, int control, int value, int channel){
   if(control == 1){
      _ctx.knob1 = (0.00787401574803f * int_to_float(value));
   }
   if(control == 2){
      _ctx.knob2 = (0.00787401574803f * int_to_float(value));
   }
   if(control == 3){
      _ctx.knob3 = (0.00787401574803f * int_to_float(value));
   }
   if(control == 4){
      _ctx.knob4 = (0.00787401574803f * int_to_float(value));
   }
}

void Svf__ctx_type_4_init(Svf__ctx_type_4 &_output_){
   Svf__ctx_type_4 _ctx;
   _ctx.z2 = 0.0f;
   _ctx.z1 = 0.0f;
   _ctx.inv_den = 0.0f;
   _ctx.g = 0.0f;
   Util__ctx_type_1_init(_ctx._inst23b);
   Util__ctx_type_1_init(_ctx._inst13b);
   _ctx.R = 0.0f;
   Svf_default(_ctx);
   _output_ = _ctx;
   return ;
}

float Svf_process(Svf__ctx_type_4 &_ctx, float x, float cv, float q, int sel){
   q = (0.5f + q);
   if(Util_change(_ctx._inst13b,cv) || Util_change(_ctx._inst23b,q)){
      _ctx.g = Svf_calc_g(cv);
      _ctx.R = (1.f / (2.f * (1e-18f + q)));
      _ctx.inv_den = (1.f / (1.f + (2.f * _ctx.R * _ctx.g) + (_ctx.g * _ctx.g)));
   }
   float high;
   high = (_ctx.inv_den * (x + (- _ctx.z2) + (- (_ctx.z1 * (_ctx.g + (2.f * _ctx.R))))));
   float band;
   band = (_ctx.z1 + (_ctx.g * high));
   float low;
   low = (_ctx.z2 + (_ctx.g * band));
   float notch;
   notch = (high + low);
   _ctx.z1 = (band + (_ctx.g * high));
   _ctx.z2 = (low + (_ctx.g * band));
   float output;
   switch(sel) {
      case 0:
         output = low;
      break;
      case 1:
         output = high;
      break;
      case 2:
         output = band;
      break;
    default: 
      output = notch;
   }
   return Saturate_soft_process(output);
}

void Sawcore__ctx_type_0_init(Sawcore__ctx_type_0 &_output_){
   Sawcore__ctx_type_0 _ctx;
   _ctx.ptr_w2_ret_1 = 0.0f;
   _ctx.ptr_w2_ret_0 = false;
   _output_ = _ctx;
   return ;
}

void Sawcore_ptr_w2(Sawcore__ctx_type_0 &_ctx, float phase, float rate){
   _tuple___bool_real__ out;
   float s1;
   s1 = rate;
   float s2;
   s2 = (rate + s1);
   if(phase < s1){
      float d;
      d = (phase / rate);
      float t2;
      t2 = (0.0009765625f * s2);
      {
         out.field_0 = false;
         out.field_1 = (1.f + (d * (t2 + (- d))));
      }
   }
   else
   {
      if(phase < s2){
         float d;
         d = (phase / rate);
         float t2;
         t2 = (0.0009765625f * s2);
         {
            out.field_0 = false;
            out.field_1 = (3.f + (d * (-4.f + d + t2)));
         }
      }
      else
      {
         out.field_0 = true;
         out.field_1 = 0.0f;
      }
   }
   _ctx.ptr_w2_ret_0 = out.field_0;_ctx.ptr_w2_ret_1 = out.field_1;
   return ;
}

void Sawcore__ctx_type_1_init(Sawcore__ctx_type_1 &_output_){
   Sawcore__ctx_type_1 _ctx;
   _ctx.reset_state = false;
   _ctx.reset_phase = 0.0f;
   _ctx.rate = 0.0f;
   _ctx.phase = 0.0f;
   Sawcore__ctx_type_0_init(_ctx._inst622);
   Util__ctx_type_0_init(_ctx._inst351);
   Util__ctx_type_1_init(_ctx._inst13b);
   Sawcore_default(_ctx);
   _output_ = _ctx;
   return ;
}

float Sawcore_process(Sawcore__ctx_type_1 &_ctx, float cv, float reset){
   float transition;
   transition = 0.0f;
   float out;
   out = 0.0f;
   if(Util_change(_ctx._inst13b,cv)){
      _ctx.rate = Util_cvToRate_1024(cv);
   }
   float new_phase;
   new_phase = (_ctx.phase + _ctx.rate);
   uint8_t do_reset;
   do_reset = Util_edge(_ctx._inst351,(reset > 0.0f));
   uint8_t do_wrap;
   do_wrap = (new_phase > 1024.f);
   if(do_reset || do_wrap){
      _ctx.reset_phase = _ctx.phase;
      if(do_wrap){
         new_phase = (-1024.f + new_phase);
      }
      else
      {
         new_phase = 0.0f;
      }
      _ctx.reset_state = true;
   }
   _ctx.phase = new_phase;
   out = _ctx.phase;
   if(_ctx.reset_state){
      uint8_t done;
      float ptr;
      Sawcore_ptr_w2(_ctx._inst622,_ctx.phase,_ctx.rate);
      done = Sawcore_ptr_w2_ret_0(_ctx._inst622);
      ptr = Sawcore_ptr_w2_ret_1(_ctx._inst622);
      transition = (0.5f * _ctx.reset_phase * (1.f + ptr));
      if(done){
         _ctx.reset_state = false;
      }
      else
      {
         out = transition;
      }
   }
   return (-1.f + (0.001953125f * out));
}

float Fold_do(float signal, float level){
   float sign;
   if(signal > 0.0f){
      sign = 1.f;
   }
   else
   {
      sign = -1.f;
   }
   float amp;
   amp = (fabsf(signal) * (1.f + (8.f * level)));
   float base;
   base = floorf(amp);
   float delta;
   delta = (amp + (- base));
   float out;
   if((float_to_int(base) % 2) != 0){
      out = (1.f + (- delta));
   }
   else
   {
      out = delta;
   }
   return (out * sign);
}

void Aurora__ctx_type_0_init(Aurora__ctx_type_0 &_output_){
   Aurora__ctx_type_0 _ctx;
   _ctx.x4 = 0.0f;
   _ctx.x3 = 0.0f;
   _ctx.x2 = 0.0f;
   _output_ = _ctx;
   return ;
}

float Aurora_soft(Aurora__ctx_type_0 &_ctx, float x1){
   float o;
   o = (0.25f * (_ctx.x2 + _ctx.x3 + _ctx.x4 + x1));
   float _tmp_1_0;
   _tmp_1_0 = x1;
   float _tmp_1_1;
   _tmp_1_1 = _ctx.x2;
   float _tmp_1_2;
   _tmp_1_2 = _ctx.x3;
   _ctx.x2 = _tmp_1_0;
   _ctx.x3 = _tmp_1_1;
   _ctx.x4 = _tmp_1_2;
   return o;
}

void Aurora__ctx_type_1_init(Aurora__ctx_type_1 &_output_){
   Aurora__ctx_type_1 _ctx;
   _ctx.rate = 0.0f;
   _ctx.phase = 0.0f;
   Aurora__ctx_type_0_init(_ctx._inst560);
   Util__ctx_type_0_init(_ctx._inst351);
   Util__ctx_type_1_init(_ctx._inst13b);
   _output_ = _ctx;
   return ;
}

float Aurora_lfo(Aurora__ctx_type_1 &_ctx, float cv, float shape, float reset){
   if(Util_change(_ctx._inst13b,cv)){
      _ctx.rate = Util_cvToRate((-0.3f + cv));
   }
   _ctx.phase = (_ctx.phase + _ctx.rate);
   if(_ctx.phase > 2.f){
      _ctx.phase = (-2.f + _ctx.phase);
   }
   uint8_t breset;
   breset = (reset > 0.0f);
   if(Util_edge(_ctx._inst351,breset)){
      _ctx.phase = 0.0f;
   }
   float tmp;
   tmp = (-1.f + _ctx.phase);
   float o;
   if(shape < 1.f){
      o = tmp;
   }
   else
   {
      if(shape < 2.f){
         o = (-1.f + (2.f * fabsf(tmp)));
      }
      else
      {
         if(tmp > 0.0f){
            o = 1.f;
         }
         else
         {
            o = 0.0f;
         }
      }
   }
   return Aurora_soft(_ctx._inst560,o);
}

void Aurora__ctx_type_3_init(Aurora__ctx_type_3 &_output_){
   Aurora__ctx_type_3 _ctx;
   _ctx.process_ret_5 = 0.0f;
   _ctx.process_ret_4 = 0.0f;
   _ctx.process_ret_3 = 0.0f;
   _ctx.process_ret_2 = 0.0f;
   _ctx.process_ret_1 = 0.0f;
   _ctx.process_ret_0 = 0.0f;
   _ctx.param8 = 0.0f;
   _ctx.param7 = 0.0f;
   _ctx.param6 = 0.0f;
   _ctx.param5 = 0.0f;
   _ctx.param4 = 0.0f;
   _ctx.param3 = 0.0f;
   _ctx.param2 = 0.0f;
   _ctx.param1 = 0.0f;
   Svf__ctx_type_4_init(_ctx._inst912);
   Aurora__ctx_type_2_init(_ctx._inst8df);
   Aurora__ctx_type_2_init(_ctx._inst7df);
   Aurora__ctx_type_2_init(_ctx._inst6df);
   Adsr__ctx_type_0_init(_ctx._inst56);
   Adsr__ctx_type_0_init(_ctx._inst46);
   Sawcore__ctx_type_1_init(_ctx._inst31b);
   Sawcore__ctx_type_1_init(_ctx._inst21b);
   Aurora__ctx_type_1_init(_ctx._inst196);
   _output_ = _ctx;
   return ;
}

void Aurora_process(Aurora__ctx_type_3 &_ctx, float in1, float in2, float in3, float in4, float in5, float in6, float in7, float in8, float gate1, float gate2, float fs){
   float lfo_val;
   lfo_val = (0.01f * Aurora_lfo(_ctx._inst196,_ctx.param1,gate1,0.0f));
   float o1;
   o1 = (0.5f * Sawcore_process(_ctx._inst21b,in1,0.0f));
   float o2;
   o2 = (0.5f * Sawcore_process(_ctx._inst31b,(-0.1f + in2),0.0f));
   float osc_mix;
   osc_mix = (o1 + o2);
   float env_vcf;
   env_vcf = (4.f * Adsr_do(_ctx._inst46,gate1,_ctx.param1,(10.f * _ctx.param2),_ctx.param5,_ctx.param6));
   float env_vca;
   env_vca = (4.f * Adsr_do(_ctx._inst56,gate1,0.0f,0.7f,0.8f,0.6f));
   float out1;
   out1 = env_vcf;
   float out2;
   out2 = env_vca;
   float out3;
   out3 = lfo_val;
   float out4;
   out4 = 0.0f;
   float osc_out;
   osc_out = Fold_process(osc_mix,Aurora_smooth_cv(_ctx._inst6df,in3));
   float filter_frequency;
   filter_frequency = float_clip((env_vcf + Aurora_smooth_cv(_ctx._inst7df,_ctx.param3)),0.0f,1.f);
   float filter_out_pre;
   filter_out_pre = Svf_process(_ctx._inst912,osc_out,filter_frequency,(5.5f * Aurora_smooth_cv(_ctx._inst8df,_ctx.param4)),0);
   float filter_out;
   filter_out = Saturate_process(filter_out_pre);
   float mono_output;
   mono_output = (env_vca * filter_out);
   float audio_l;
   audio_l = mono_output;
   float audio_r;
   audio_r = mono_output;
   _ctx.process_ret_0 = audio_l;
   _ctx.process_ret_1 = audio_r;
   _ctx.process_ret_2 = out1;
   _ctx.process_ret_3 = out2;
   _ctx.process_ret_4 = out3;
   _ctx.process_ret_5 = out4;
   return ;
}

void Filter__ctx_type_7_init(Filter__ctx_type_7 &_output_){
   Filter__ctx_type_7 _ctx;
   _ctx.p3 = 0.0f;
   _ctx.p2 = 0.0f;
   _ctx.p1 = 0.0f;
   _ctx.p0 = 0.0f;
   _output_ = _ctx;
   return ;
}

float Filter_heun(Filter__ctx_type_7 &_ctx, float input, float fh, float res){
   float wt0;
   wt0 = Filter_clipper((input + (-4.f * _ctx.p3 * res)));
   float dpt0;
   dpt0 = (fh * (wt0 + (- _ctx.p0)));
   float dpt1;
   dpt1 = (fh * (_ctx.p0 + (- _ctx.p1)));
   float dpt2;
   dpt2 = (fh * (_ctx.p1 + (- _ctx.p2)));
   float dpt3;
   dpt3 = (fh * (_ctx.p2 + (- _ctx.p3)));
   float pt0;
   pt0 = (_ctx.p0 + dpt0);
   float pt1;
   pt1 = (_ctx.p1 + dpt1);
   float pt2;
   pt2 = (_ctx.p2 + dpt2);
   float pt3;
   pt3 = (_ctx.p3 + dpt3);
   float w0;
   w0 = Filter_clipper((input + (-4.f * pt3 * res)));
   float dp0;
   dp0 = (fh * (w0 + (- pt0)));
   float dp1;
   dp1 = (fh * (pt0 + (- pt1)));
   float dp2;
   dp2 = (fh * (pt1 + (- pt2)));
   float dp3;
   dp3 = (fh * (pt2 + (- pt3)));
   _ctx.p0 = (_ctx.p0 + (0.5f * (dp0 + dpt0)));
   _ctx.p1 = (_ctx.p1 + (0.5f * (dp1 + dpt1)));
   _ctx.p2 = (_ctx.p2 + (0.5f * (dp2 + dpt2)));
   _ctx.p3 = (_ctx.p3 + (0.5f * (dp3 + dpt3)));
   return _ctx.p3;
}

void Filter__ctx_type_8_init(Filter__ctx_type_8 &_output_){
   Filter__ctx_type_8 _ctx;
   Filter__ctx_type_7_init(_ctx.h);
   Filter__ctx_type_0_init(_ctx._inst2fa);
   Util__ctx_type_4_init(_ctx._inst155);
   _output_ = _ctx;
   return ;
}

float Filter_ladder(Filter__ctx_type_8 &_ctx, float input, float cut_in, float res_in){
   float res;
   res = Filter_polylog(res_in);
   float comp;
   comp = Util_map(res,0.9f,1.f,0.0f,0.25f);
   float limit;
   if(comp > 0.0f){
      limit = (0.9f + (- comp));
   }
   else
   {
      limit = 0.9f;
   }
   float cut;
   cut = float_clip(cut_in,0.0f,limit);
   float fh;
   fh = Filter_tune(Util_smooth(_ctx._inst155,cut));
   Filter_heun(_ctx.h,input,fh,res);
   float noise;
   noise = (0.005f * Filter_simple_noise(_ctx._inst2fa));
   float out;
   out = Filter_heun(_ctx.h,(input + noise),fh,(1.1f * res));
   return out;
}


