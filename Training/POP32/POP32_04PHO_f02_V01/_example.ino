void example(){
  // 1. No offset / no ramp (defaults to 0)
  trackPDLeft_Time(20, 8, 2, 500);

  // 2. Fixed offset (no ramp ratios passed -> holds constant +15)
  trackPDLeft_Time(20, 8, 2, 500, 15);

  // 3. Single-side ramp for B6 left entry (ramps 0 -> +15 -> 0)
  //    60% ramp up, 15% hold, 25% quick decelerate
  //    Note: trackPD_Left still has "+ 10", so actual boost is 10 -> 25 -> 10
  //    (Pass minOffset = -10 instead of 0 if you want total boost to start/end at 0)
  trackPDLeft_Time(20, 8, 2, 500, 15, 0, 0.60, 0.15);

  // 4. Same idea for a right-side ramp
  trackPDRight_Time(20, 8, 2, 500, 15, 0, 0.60, 0.15);

  // 5. Dual-side ramp (Left brakes 0 -> -5 -> 0, Right boosts 0 -> +15 -> 0)
  trackPDLR_Time(20, 8, 2, 500, 0, -5, 0, 15, 0.60, 0.15);
}