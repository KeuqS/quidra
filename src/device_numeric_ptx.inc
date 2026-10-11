// Generated from device_numeric_kernel.inc. Regenerate with generate_numeric_ptx.py.
const std::string& numeric_kernel_ptx() {
    static const std::string code = [] {
        std::string result;
        result += R"QPTX(
.version 4.2
.target sm_50
.address_size 64
.weak .func _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj
(
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_0,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_1,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_2,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_3,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_4,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_5,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_6,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_7,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_8,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_9,
	.param .b32 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_10,
	.param .b32 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_11,
	.param .b32 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_12,
	.param .b32 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_13,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_14
)
;
.weak .func _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj
(
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_0,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_1,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_2,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_3,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_4,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_5,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_6,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_7,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_8,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_9,
	.param .b32 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_10,
	.param .b32 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_11,
	.param .b32 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_12,
	.param .b32 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_13,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_14
)
;
.weak .func  (.param .b64 func_retval0) _Z7q_roundIdET_S0_i
(
	.param .b64 _Z7q_roundIdET_S0_i_param_0,
	.param .b32 _Z7q_roundIdET_S0_i_param_1
)
;
.weak .func  (.param .align 8 .b8 func_retval0[16]) _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj
(
	.param .align 8 .b8 _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_0[16],
	.param .align 8 .b8 _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_1[16],
	.param .b32 _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_2,
	.param .b32 _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_3,
	.param .b64 _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_4
)
;
.weak .func  (.param .align 4 .b8 func_retval0[8]) _Z6q_readIfE5QPairIT_EPKvyi
(
	.param .b64 _Z6q_readIfE5QPairIT_EPKvyi_param_0,
	.param .b64 _Z6q_readIfE5QPairIT_EPKvyi_param_1,
	.param .b32 _Z6q_readIfE5QPairIT_EPKvyi_param_2
)
;
.weak .func  (.param .b32 func_retval0) _Z7q_roundIfET_S0_i
(
	.param .b32 _Z7q_roundIfET_S0_i_param_0,
	.param .b32 _Z7q_roundIfET_S0_i_param_1
)
;
.weak .func _Z7q_storeIfEvPvy5QPairIT_Ei
(
	.param .b64 _Z7q_storeIfEvPvy5QPairIT_Ei_param_0,
	.param .b64 _Z7q_storeIfEvPvy5QPairIT_Ei_param_1,
	.param .align 4 .b8 _Z7q_storeIfEvPvy5QPairIT_Ei_param_2[8],
	.param .b32 _Z7q_storeIfEvPvy5QPairIT_Ei_param_3
)
;
.weak .func  (.param .align 4 .b8 func_retval0[8]) _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj
(
	.param .align 4 .b8 _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_0[8],
	.param .align 4 .b8 _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_1[8],
	.param .b32 _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_2,
	.param .b32 _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_3,
	.param .b64 _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_4
)
;
.visible .func  (.param .b64 func_retval0) _Z7q_indexv()
{
	.reg .b32 	%r<4>;
	.reg .b64 	%rd<4>;
	mov.u32 %r1, %ctaid.x;
	mov.u32 %r2, %ntid.x;
	mov.u32 %r3, %tid.x;
	mul.wide.u32 	%rd1, %r2, %r1;
	cvt.u64.u32 	%rd2, %r3;
	add.s64 	%rd3, %rd1, %rd2;
	st.param.b64 	[func_retval0], %rd3;
	ret;
}
.visible .func _Z8q_statusPjj(
	.param .b64 _Z8q_statusPjj_param_0,
	.param .b32 _Z8q_statusPjj_param_1
)
{
	.reg .b32 	%r<3>;
	.reg .b64 	%rd<2>;
	ld.param.b64 	%rd1, [_Z8q_statusPjj_param_0];
	ld.param.b32 	%r2, [_Z8q_statusPjj_param_1];
	atom.global.or.b32 %r1, [%rd1], %r2;
	ret;
}
.visible .func  (.param .b32 func_retval0) _Z6q_parti(
	.param .b32 _Z6q_parti_param_0
)
{
	.reg .pred 	%p<6>;
	.reg .b32 	%r<3>;
	ld.param.b32 	%r1, [_Z6q_parti_param_0];
	setp.gt.s32 	%p1, %r1, 15;
	@%p1 bra 	$L__BB2_4;
	mov.b32 	%r2, 12;
	setp.eq.b32 	%p4, %r1, 14;
	@%p4 bra 	$L__BB2_8;
	setp.eq.b32 	%p5, %r1, 15;
	mov.b32 	%r2, %r1;
	@%p5 bra 	$L__BB2_3;
	bra.uni 	$L__BB2_8;
$L__BB2_3:
	mov.b32 	%r2, 13;
	bra.uni 	$L__BB2_8;
$L__BB2_4:
	setp.eq.b32 	%p2, %r1, 16;
	@%p2 bra 	$L__BB2_7;
	setp.ne.b32 	%p3, %r1, 17;
	mov.b32 	%r2, %r1;
	@%p3 bra 	$L__BB2_8;
	mov.b32 	%r2, 9;
	bra.uni 	$L__BB2_8;
$L__BB2_7:
	mov.b32 	%r2, 10;
$L__BB2_8:
	st.param.b32 	[func_retval0], %r2;
	ret;
}
.visible .func  (.param .b32 func_retval0) _Z9q_complexi(
	.param .b32 _Z9q_complexi_param_0
)
{
	.reg .pred 	%p<2>;
	.reg .b32 	%r<4>;
	ld.param.b32 	%r1, [_Z9q_complexi_param_0];
	add.s32 	%r2, %r1, -14;
	setp.lt.u32 	%p1, %r2, 4;
	selp.b32 	%r3, 1, 0, %p1;
	st.param.b32 	[func_retval0], %r3;
	ret;
}
.visible .func  (.param .b32 func_retval0) _Z6q_halfi(
	.param .b32 _Z6q_halfi_param_0
)
{
	.reg .pred 	%p<2>;
	.reg .b32 	%r<4>;
	ld.param.b32 	%r1, [_Z6q_halfi_param_0];
	and.b32 	%r2, %r1, -2;
	setp.eq.b32 	%p1, %r2, 12;
	selp.b32 	%r3, 1, 0, %p1;
	st.param.b32 	[func_retval0], %r3;
	ret;
}
.visible .func  (.param .b32 func_retval0) _Z7q_widthi(
	.param .b32 _Z7q_widthi_param_0
)
{
	.reg .pred 	%p<9>;
	.reg .b32 	%r<15>;
	mov.b32 	%r2, 8;
	ld.param.b32 	%r1, [_Z7q_widthi_param_0];
	setp.gt.u32 	%p1, %r1, 11;
	@%p1 bra 	$L__BB5_4;
	mov.b32 	%r3, 1;
	shl.b32 	%r4, %r3, %r1;
	and.b32 	%r5, %r4, 770;
	setp.ne.b32 	%p2, %r5, 0;
	mov.b32 	%r14, %r2;
	@%p2 bra 	$L__BB5_12;
	and.b32 	%r6, %r4, 2084;
	setp.ne.b32 	%p3, %r6, 0;
	@%p3 bra 	$L__BB5_10;
	bra.uni 	$L__BB5_3;
$L__BB5_10:
	mov.b32 	%r14, 1;
	bra.uni 	$L__BB5_12;
$L__BB5_3:
	mov.b32 	%r7, 1;
	shl.b32 	%r8, %r7, %r1;
	and.b32 	%r9, %r8, 72;
	setp.ne.b32 	%p4, %r9, 0;
	@%p4 bra 	$L__BB5_11;
	bra.uni 	$L__BB5_4;
$L__BB5_11:
	mov.b32 	%r14, 2;
$L__BB5_12:
	st.param.b32 	[func_retval0], %r14;
	ret;
$L__BB5_4:
	and.b32 	%r10, %r1, -2;
	setp.eq.b32 	%p5, %r10, 12;
	mov.b32 	%r14, 2;
	@%p5 bra 	$L__BB5_12;
	setp.gt.u32 	%p6, %r1, 16;
	@%p6 bra 	$L__BB5_9;
	mov.b32 	%r14, 4;
	mov.b32 	%r11, 1;
	shl.b32 	%r12, %r11, %r1;
	and.b32 	%r13, %r12, 50320;
	setp.ne.b32 	%p7, %r13, 0;
	@%p7 bra 	$L__BB5_12;
	setp.eq.b32 	%p8, %r1, 16;
	@%p8 bra 	$L__BB5_8;
	bra.uni 	$L__BB5_9;
$L__BB5_8:
	mov.b32 	%r14, %r2;
	bra.uni 	$L__BB5_12;
$L__BB5_9:
	mov.b32 	%r14, 16;
	bra.uni 	$L__BB5_12;
}
.visible .func  (.param .b32 func_retval0) _Z7q_floatj(
	.param .b32 _Z7q_floatj_param_0
)
{
	.reg .b32 	%r<2>;
	ld.param.b32 	%r1, [_Z7q_floatj_param_0];
	st.param.b32 	[func_retval0], %r1;
	ret;
}
.visible .func  (.param .b32 func_retval0) _Z6q_bitsf(
	.param .b32 _Z6q_bitsf_param_0
)
{
	.reg .b32 	%r<2>;
	ld.param.b32 	%r1, [_Z6q_bitsf_param_0];
	st.param.b32 	[func_retval0], %r1;
	ret;
}
.visible .func  (.param .b64 func_retval0) _Z8q_doubley(
	.param .b64 _Z8q_doubley_param_0
)
{
	.reg .b64 	%rd<2>;
	ld.param.b64 	%rd1, [_Z8q_doubley_param_0];
	st.param.b64 	[func_retval0], %rd1;
	ret;
}
.visible .func  (.param .b64 func_retval0) _Z13q_double_bitsd(
	.param .b64 _Z13q_double_bitsd_param_0
)
{
	.reg .b64 	%rd<2>;
	ld.param.b64 	%rd1, [_Z13q_double_bitsd_param_0];
	st.param.b64 	[func_retval0], %rd1;
	ret;
}
.visible .func  (.param .b32 func_retval0) _Z11q_read_halfti(
	.param .b32 _Z11q_read_halfti_param_0,
	.param .b32 _Z11q_read_halfti_param_1
)
{
	.reg .pred 	%p<5>;
	.reg .b16 	%rs<2>;
	.reg .b32 	%r<22>;
	ld.param.b16 	%rs1, [_Z11q_read_halfti_param_0];
	ld.param.b32 	%r4, [_Z11q_read_halfti_param_1];
	setp.ne.b32 	%p1, %r4, 13;
	cvt.u32.u16 	%r1, %rs1;
	@%p1 bra 	$L__BB10_2;
	shl.b32 	%r21, %r1, 16;
	bra.uni 	$L__BB10_8;
$L__BB10_2:
	cvt.s32.s16 	%r5, %rs1;
	and.b32 	%r21, %r5, -2147483648;
	bfe.u32 	%r2, %r1, 10, 5;
	setp.eq.b32 	%p2, %r2, 31;
	@%p2 bra 	$L__BB10_6;
	and.b32 	%r3, %r1, 1023;
	setp.ne.b32 	%p3, %r2, 0;
	@%p3 bra 	$L__BB10_7;
	setp.eq.b32 	%p4, %r3, 0;
	@%p4 bra 	$L__BB10_8;
	clz.b32 	%r8, %r3;
	xor.b32 	%r9, %r8, 31;
	sub.s32 	%r10, 9, %r9;
	shl.b32 	%r11, %r1, %r10;
	shl.b32 	%r12, %r9, 23;
	shl.b32 	%r13, %r11, 14;
	and.b32 	%r14, %r13, 8372224;
	or.b32 	%r15, %r12, %r14;
	add.s32 	%r16, %r15, %r21;
	add.s32 	%r21, %r16, 864026624;
	bra.uni 	$L__BB10_8;
$L__BB10_6:
	shl.b32 	%r6, %r1, 13;
	or.b32 	%r7, %r21, %r6;
	or.b32 	%r21, %r7, 2139095040;
	bra.uni 	$L__BB10_8;
$L__BB10_7:
	shl.b32 	%r17, %r2, 23;
	shl.b32 	%r18, %r3, 13;
	or.b32 	%r19, %r17, %r18;
	add.s32 	%r20, %r19, %r21;
	add.s32 	%r21, %r20, 939524096;
$L__BB10_8:
	st.param.b32 	[func_retval0], %r21;
	ret;
}
.visible .func  (.param .b64 func_retval0) _Z13q_round_shiftyi(
	.param .b64 _Z13q_round_shiftyi_param_0,
	.param .b32 _Z13q_round_shiftyi_param_1
)
{
	.reg .pred 	%p<8>;
	.reg .b32 	%r<4>;
	.reg .b64 	%rd<12>;
	ld.param.b32 	%r1, [_Z13q_round_shiftyi_param_1];
	ld.param.b64 	%rd1, [_Z13q_round_shiftyi_param_0];
	setp.gt.s32 	%p1, %r1, 0;
	@%p1 bra 	$L__BB11_2;
	bra.uni 	$L__BB11_1;
$L__BB11_2:
	setp.gt.u32 	%p2, %r1, 63;
	mov.b64 	%rd11, 0;
	@%p2 bra 	$L__BB11_4;
	shr.u64 	%rd2, %rd1, %r1;
	mov.b64 	%rd3, -1;
	shl.b64 	%rd4, %rd3, %r1;
	not.b64 	%rd5, %rd4;
	and.b64 	%rd6, %rd1, %rd5;
	add.s32 	%r2, %r1, -1;
	mov.b64 	%rd7, 1;
	shl.b64 	%rd8, %rd7, %r2;
	setp.gt.u64 	%p3, %rd6, %rd8;
	setp.eq.b64 	%p4, %rd6, %rd8;
	and.b64 	%rd9, %rd2, 1;
	setp.ne.b64 	%p5, %rd9, 0;
	and.pred 	%p6, %p4, %p5;
	or.pred 	%p7, %p3, %p6;
	selp.b64 	%rd10, 1, 0, %p7;
	add.s64 	%rd11, %rd2, %rd10;
	bra.uni 	$L__BB11_4;
$L__BB11_1:
	neg.s32 	%r3, %r1;
	shl.b64 	%rd11, %rd1, %r3;
$L__BB11_4:
	st.param.b64 	[func_retval0], %rd11;
	ret;
}
.visible .func  (.param .b32 func_retval0) _Z11q_half_bitsdi(
	.param .b64 _Z11q_half_bitsdi_param_0,
	.param .b32 _Z11q_half_bitsdi_param_1
)
{
	.reg .pred 	%p<20>;
	.reg .b16 	%rs<2>;
	.reg .b32 	%r<33>;
	.reg .b64 	%rd<33>;
	ld.param.b64 	%rd1, [_Z11q_half_bitsdi_param_0];
	shr.u64 	%rd3, %rd1, 48;
	cvt.u32.u64 	%r10, %rd3;
	and.b32 	%r1, %r10, 32768;
	shr.u64 	%rd8, %rd1, 52;
	cvt.u32.u64 	%r11, %rd8;
	and.b32 	%r2, %r11, 2047;
	setp.eq.b32 	%p2, %r2, 0;
	@%p2 bra 	$L__BB12_3;
	ld.param.b32 	%r9, [_Z11q_half_bitsdi_param_1];
	and.b64 	%rd2, %rd1, 4503599627370495;
	setp.eq.b32 	%p1, %r9, 12;
	selp.b32 	%r3, 11, 8, %p1;
	selp.b32 	%r5, 31744, 32640, %p1;
	setp.ne.b32 	%p3, %r2, 2047;
	@%p3 bra 	$L__BB12_4;
	setp.eq.b64 	%p4, %rd2, 0;
	add.s32 	%r12, %r3, -2;
	mov.b32 	%r13, 1;
	shl.b32 	%r14, %r13, %r12;
	selp.b32 	%r15, 0, %r14, %p4;
	or.b32 	%r16, %r5, %r15;
	or.b32 	%r17, %r16, %r1;
	cvt.u16.u32 	%rs1, %r17;
	bra.uni 	$L__BB12_14;
$L__BB12_3:
	cvt.u16.u32 	%rs1, %r1;
	bra.uni 	$L__BB12_14;
$L__BB12_4:
	selp.b32 	%r18, -14, -126, %p1;
	add.s32 	%r6, %r2, -1023;
	or.b64 	%rd4, %rd2, 4503599627370496;
	setp.ge.s32 	%p5, %r6, %r18;
	@%p5 bra 	$L__BB12_10;
	and.b64 	%rd5, %rd3, 32768;
	selp.b32 	%r28, 28, -81, %p1;
	sub.s32 	%r7, %r28, %r6;
	setp.gt.s32 	%p13, %r7, 0;
	@%p13 bra 	$L__BB12_7;
	bra.uni 	$L__BB12_6;
$L__BB12_7:
	setp.gt.u32 	%p14, %r7, 63;
	mov.b64 	%rd32, 0;
	@%p14 bra 	$L__BB12_9;
	shr.u64 	%rd22, %rd4, %r7;
	mov.b64 	%rd23, -1;
	shl.b64 	%rd24, %rd23, %r7;
	not.b64 	%rd25, %rd24;
	and.b64 	%rd26, %rd4, %rd25;
	add.s32 	%r29, %r7, -1;
	mov.b64 	%rd27, 1;
	shl.b64 	%rd28, %rd27, %r29;
	setp.gt.u64 	%p15, %rd26, %rd28;
	setp.eq.b64 	%p16, %rd26, %rd28;
	and.b64 	%rd29, %rd22, 1;
	setp.ne.b64 	%p17, %rd29, 0;
	and.pred 	%p18, %p16, %p17;
	or.pred 	%p19, %p15, %p18;
	selp.b64 	%rd30, 1, 0, %p19;
	add.s64 	%rd32, %rd22, %rd30;
	bra.uni 	$L__BB12_9;
$L__BB12_10:
	selp.b32 	%r4, 15, 127, %p1;
	sub.s32 	%r19, 53, %r3;
	shr.u64 	%rd9, %rd4, %r19;
	mov.b64 	%rd10, -1;
	shl.b64 	%rd11, %rd10, %r19;
	not.b64 	%rd12, %rd11;
	and.b64 	%rd13, %rd12, %rd1;
	sub.s32 	%r20, 52, %r3;
	mov.b64 	%rd14, 1;
	shl.b64 	%rd15, %rd14, %r20;
	setp.gt.u64 	%p6, %rd13, %rd15;
	setp.eq.b64 	%p7, %rd13, %rd15;
	and.b64 	%rd16, %rd9, 1;
	setp.ne.b64 	%p8, %rd16, 0;
	and.pred 	%p9, %p7, %p8;
	or.pred 	%p10, %p6, %p9;
	selp.b64 	%rd17, 1, 0, %p10;
	add.s64 	%rd6, %rd9, %rd17;
	shl.b64 	%rd7, %rd14, %r3;
	setp.eq.b64 	%p11, %rd6, %rd7;
	add.s32 	%r21, %r2, -1022;
	selp.b32 	%r8, %r21, %r6, %p11;
	setp.le.s32 	%p12, %r8, %r4;
	@%p12 bra 	$L__BB12_12;
	or.b32 	%r32, %r1, %r5;
	bra.uni 	$L__BB12_13;
$L__BB12_12:
	selp.b32 	%r22, 1, 0, %p11;
	shr.u64 	%rd18, %rd6, %r22;
	add.s32 	%r23, %r4, %r8;
	add.s32 	%r24, %r3, -1;
	shl.b32 	%r25, %r23, %r24;
	shl.b64 	%rd19, %rd10, %r24;
	not.b64 	%rd20, %rd19;
	and.b64 	%rd21, %rd18, %rd20;
	cvt.u32.u64 	%r26, %rd21;
	or.b32 	%r27, %r25, %r26;
	or.b32 	%r32, %r27, %r1;
$L__BB12_13:
	cvt.u16.u32 	%rs1, %r32;
	bra.uni 	$L__BB12_14;
$L__BB12_6:
	neg.s32 	%r30, %r7;
	shl.b64 	%rd32, %rd4, %r30;
$L__BB12_9:
	or.b64 	%rd31, %rd32, %rd5;
	cvt.u16.u64 	%rs1, %rd31;
$L__BB12_14:
	cvt.u32.u16 	%r31, %rs1;
	st.param.b32 	[func_retval0], %r31;
	ret;
}
.visible .func  (.param .b32 func_retval0) _Z14q_integer_halfybi(
	.param .b64 _Z14q_integer_halfybi_param_0,
	.param .b32 _Z14q_integer_halfybi_param_1,
	.param .b32 _Z14q_integer_halfybi_param_2
)
{
	.reg .pred 	%p<13>;
	.reg .b16 	%rs<3>;
	.reg .b32 	%r<20>;
	.reg .b64 	%rd<19>;
	ld.param.b8 	%rs1, [_Z14q_integer_halfybi_param_1];
	and.b16 	%rs2, %rs1, 1;
	setp.ne.b16 	%p1, %rs2, 0;
	ld.param.b64 	%rd2, [_Z14q_integer_halfybi_param_0];
	selp.b32 	%r19, 32768, 0, %p1;
	setp.eq.b64 	%p2, %rd2, 0;
	@%p2 bra 	$L__BB13_7;
	ld.param.b32 	%r6, [_Z14q_integer_halfybi_param_2];
	clz.b64 	%r7, %rd2;
	sub.s32 	%r1, 64, %r7;
	setp.eq.b32 	%p3, %r6, 12;
	selp.b32 	%r2, 11, 8, %p3;
	sub.s32 	%r3, %r1, %r2;
	setp.gt.s32 	%p4, %r3, 0;
	@%p4 bra 	$L__BB13_3;
	bra.uni 	$L__BB13_2;
$L__BB13_3:
	shr.u64 	%rd3, %rd2, %r3;
	mov.b64 	%rd4, -1;
	shl.b64 	%rd5, %rd4, %r3;
	not.b64 	%rd6, %rd5;
	and.b64 	%rd7, %rd2, %rd6;
	add.s32 	%r8, %r3, -1;
	mov.b64 	%rd8, 1;
	shl.b64 	%rd9, %rd8, %r8;
	setp.gt.u64 	%p5, %rd7, %rd9;
	setp.eq.b64 	%p6, %rd7, %rd9;
	and.b64 	%rd10, %rd3, 1;
	setp.ne.b64 	%p7, %rd10, 0;
	and.pred 	%p8, %p6, %p7;
	or.pred 	%p9, %p5, %p8;
	selp.b64 	%rd11, 1, 0, %p9;
	add.s64 	%rd18, %rd3, %rd11;
	bra.uni 	$L__BB13_4;
$L__BB13_2:
	neg.s32 	%r9, %r3;
	shl.b64 	%rd18, %rd2, %r9;
$L__BB13_4:
	mov.b64 	%rd12, 1;
	shl.b64 	%rd1, %rd12, %r2;
	setp.ne.b64 	%p10, %rd18, %rd1;
	selp.b32 	%r10, -1, 0, %p10;
	add.s32 	%r4, %r1, %r10;
	selp.b32 	%r5, 15, 127, %p3;
	setp.le.u32 	%p11, %r4, %r5;
	@%p11 bra 	$L__BB13_6;
	selp.b32 	%r17, 31744, 32640, %p3;
	or.b32 	%r19, %r17, %r19;
	bra.uni 	$L__BB13_7;
$L__BB13_6:
	setp.eq.b64 	%p12, %rd18, %rd1;
	selp.b32 	%r11, 1, 0, %p12;
	shr.u64 	%rd13, %rd18, %r11;
	add.s32 	%r12, %r4, %r5;
	add.s32 	%r13, %r2, -1;
	shl.b32 	%r14, %r12, %r13;
	mov.b64 	%rd14, -1;
	shl.b64 	%rd15, %rd14, %r13;
	not.b64 	%rd16, %rd15;
	and.b64 	%rd17, %rd13, %rd16;
	cvt.u32.u64 	%r15, %rd17;
	or.b32 	%r16, %r14, %r15;
	or.b32 	%r19, %r16, %r19;
$L__BB13_7:
	and.b32 	%r18, %r19, 65535;
	st.param.b32 	[func_retval0], %r18;
	ret;
}
.visible .func  (.param .b64 func_retval0) _Z9q_integerPKvyi(
	.param .b64 _Z9q_integerPKvyi_param_0,
	.param .b64 _Z9q_integerPKvyi_param_1,
	.param .b32 _Z9q_integerPKvyi_param_2
)
{
	.reg .pred 	%p<10>;
	.reg .b32 	%r<2>;
	.reg .b64 	%rd<18>;
	ld.param.b32 	%r1, [_Z9q_integerPKvyi_param_2];
	ld.param.b64 	%rd2, [_Z9q_integerPKvyi_param_1];
	ld.param.b64 	%rd1, [_Z9q_integerPKvyi_param_0];
	setp.gt.s32 	%p1, %r1, 3;
	@%p1 bra 	$L__BB14_5;
	bra.uni 	$L__BB14_1;
$L__BB14_5:
	setp.gt.s32 	%p2, %r1, 5;
	@%p2 bra 	$L__BB14_9;
	setp.eq.b32 	%p5, %r1, 4;
	@%p5 bra 	$L__BB14_14;
	setp.eq.b32 	%p6, %r1, 5;
	@%p6 bra 	$L__BB14_8;
	bra.uni 	$L__BB14_16;
$L__BB14_8:
	add.s64 	%rd7, %rd1, %rd2;
	ld.b8 	%rd17, [%rd7];
	bra.uni 	$L__BB14_17;
$L__BB14_1:
	setp.eq.b32 	%p7, %r1, 1;
	@%p7 bra 	$L__BB14_12;
	setp.eq.b32 	%p8, %r1, 2;
	@%p8 bra 	$L__BB14_13;
	setp.eq.b32 	%p9, %r1, 3;
	@%p9 bra 	$L__BB14_4;
	bra.uni 	$L__BB14_16;
$L__BB14_4:
	shl.b64 	%rd10, %rd2, 1;
	add.s64 	%rd11, %rd1, %rd10;
	ld.s16 	%rd17, [%rd11];
	bra.uni 	$L__BB14_17;
$L__BB14_9:
	setp.eq.b32 	%p3, %r1, 6;
	@%p3 bra 	$L__BB14_15;
	setp.eq.b32 	%p4, %r1, 7;
	@%p4 bra 	$L__BB14_11;
	bra.uni 	$L__BB14_16;
$L__BB14_11:
	shl.b64 	%rd3, %rd2, 2;
	add.s64 	%rd4, %rd1, %rd3;
	ld.b32 	%rd17, [%rd4];
	bra.uni 	$L__BB14_17;
$L__BB14_12:
	shl.b64 	%rd13, %rd2, 3;
	add.s64 	%rd14, %rd1, %rd13;
	ld.b64 	%rd17, [%rd14];
	bra.uni 	$L__BB14_17;
$L__BB14_16:
	shl.b64 	%rd15, %rd2, 3;
	add.s64 	%rd16, %rd1, %rd15;
	ld.b64 	%rd17, [%rd16];
	bra.uni 	$L__BB14_17;
$L__BB14_14:
	shl.b64 	%rd8, %rd2, 2;
	add.s64 	%rd9, %rd1, %rd8;
	ld.s32 	%rd17, [%rd9];
	bra.uni 	$L__BB14_17;
$L__BB14_15:
	shl.b64 	%rd5, %rd2, 1;
	add.s64 	%rd6, %rd1, %rd5;
	ld.b16 	%rd17, [%rd6];
	bra.uni 	$L__BB14_17;
$L__BB14_13:
	add.s64 	%rd12, %rd1, %rd2;
	ld.s8 	%rd17, [%rd12];
$L__BB14_17:
	st.param.b64 	[func_retval0], %rd17;
	ret;
}
.visible .func  (.param .b64 func_retval0) _Z11q_read_partPKvyi(
	.param .b64 _Z11q_read_partPKvyi_param_0,
	.param .b64 _Z11q_read_partPKvyi_param_1,
	.param .b32 _Z11q_read_partPKvyi_param_2
)
{
	.reg .pred 	%p<19>;
	.reg .b16 	%rs<2>;
	.reg .b32 	%r<24>;
	.reg .b64 	%rd<27>;
	ld.param.b32 	%r4, [_Z11q_read_partPKvyi_param_2];
	ld.param.b64 	%rd2, [_Z11q_read_partPKvyi_param_1];
	ld.param.b64 	%rd1, [_Z11q_read_partPKvyi_param_0];
	and.b32 	%r5, %r4, -2;
	setp.ne.b32 	%p1, %r5, 12;
	@%p1 bra 	$L__BB15_10;
	shl.b64 	%rd23, %rd2, 1;
	add.s64 	%rd24, %rd1, %rd23;
	ld.b16 	%rs1, [%rd24];
	setp.ne.b32 	%p15, %r4, 13;
	cvt.u32.u16 	%r1, %rs1;
	@%p15 bra 	$L__BB15_3;
	shl.b32 	%r23, %r1, 16;
	bra.uni 	$L__BB15_9;
$L__BB15_10:
	setp.gt.s32 	%p2, %r4, 4;
	@%p2 bra 	$L__BB15_18;
	bra.uni 	$L__BB15_11;
$L__BB15_18:
	setp.gt.s32 	%p3, %r4, 6;
	@%p3 bra 	$L__BB15_22;
	bra.uni 	$L__BB15_19;
$L__BB15_22:
	setp.eq.b32 	%p4, %r4, 7;
	@%p4 bra 	$L__BB15_30;
	setp.eq.b32 	%p5, %r4, 9;
	@%p5 bra 	$L__BB15_26;
	setp.ne.b32 	%p6, %r4, 10;
	@%p6 bra 	$L__BB15_31;
	shl.b64 	%rd17, %rd2, 2;
	add.s64 	%rd18, %rd1, %rd17;
	ld.b32 	%r6, [%rd18];
	cvt.f64.f32 	%rd26, %r6;
	bra.uni 	$L__BB15_33;
$L__BB15_3:
	cvt.s32.s16 	%r7, %rs1;
	and.b32 	%r23, %r7, -2147483648;
	bfe.u32 	%r2, %r1, 10, 5;
	setp.eq.b32 	%p16, %r2, 31;
	@%p16 bra 	$L__BB15_7;
	and.b32 	%r3, %r1, 1023;
	setp.ne.b32 	%p17, %r2, 0;
	@%p17 bra 	$L__BB15_8;
	setp.eq.b32 	%p18, %r3, 0;
	@%p18 bra 	$L__BB15_9;
	clz.b32 	%r10, %r3;
	xor.b32 	%r11, %r10, 31;
	sub.s32 	%r12, 9, %r11;
	shl.b32 	%r13, %r1, %r12;
	shl.b32 	%r14, %r11, 23;
	shl.b32 	%r15, %r13, 14;
	and.b32 	%r16, %r15, 8372224;
	add.s32 	%r17, %r14, %r23;
	add.s32 	%r18, %r17, %r16;
	add.s32 	%r23, %r18, 864026624;
	bra.uni 	$L__BB15_9;
$L__BB15_11:
	setp.gt.s32 	%p9, %r4, 2;
	@%p9 bra 	$L__BB15_15;
	setp.eq.b32 	%p12, %r4, 1;
	@%p12 bra 	$L__BB15_27;
	setp.eq.b32 	%p13, %r4, 2;
	@%p13 bra 	$L__BB15_14;
	bra.uni 	$L__BB15_31;
$L__BB15_14:
	add.s64 	%rd12, %rd1, %rd2;
	ld.s8 	%rd25, [%rd12];
	bra.uni 	$L__BB15_32;
$L__BB15_15:
	setp.eq.b32 	%p10, %r4, 3;
	@%p10 bra 	$L__BB15_28;
	setp.eq.b32 	%p11, %r4, 4;
	@%p11 bra 	$L__BB15_17;
	bra.uni 	$L__BB15_31;
$L__BB15_17:
	shl.b64 	%rd8, %rd2, 2;
	add.s64 	%rd9, %rd1, %rd8;
	ld.s32 	%rd25, [%rd9];
	bra.uni 	$L__BB15_32;
$L__BB15_19:
	setp.eq.b32 	%p7, %r4, 5;
	@%p7 bra 	$L__BB15_29;
	setp.eq.b32 	%p8, %r4, 6;
	@%p8 bra 	$L__BB15_21;
	bra.uni 	$L__BB15_31;
$L__BB15_21:
	shl.b64 	%rd5, %rd2, 1;
	add.s64 	%rd6, %rd1, %rd5;
	ld.b16 	%rd25, [%rd6];
	bra.uni 	$L__BB15_32;
$L__BB15_7:
	shl.b32 	%r8, %r1, 13;
	or.b32 	%r9, %r23, %r8;
	or.b32 	%r23, %r9, 2139095040;
	bra.uni 	$L__BB15_9;
$L__BB15_8:
	shl.b32 	%r19, %r2, 23;
	shl.b32 	%r20, %r3, 13;
	or.b32 	%r21, %r19, %r20;
	add.s32 	%r22, %r21, %r23;
	add.s32 	%r23, %r22, 939524096;
$L__BB15_9:
	cvt.f64.f32 	%rd26, %r23;
	bra.uni 	$L__BB15_33;
$L__BB15_27:
	shl.b64 	%rd13, %rd2, 3;
	add.s64 	%rd14, %rd1, %rd13;
	ld.b64 	%rd25, [%rd14];
	bra.uni 	$L__BB15_32;
$L__BB15_28:
	shl.b64 	%rd10, %rd2, 1;
	add.s64 	%rd11, %rd1, %rd10;
	ld.s16 	%rd25, [%rd11];
	bra.uni 	$L__BB15_32;
$L__BB15_30:
	shl.b64 	%rd3, %rd2, 2;
	add.s64 	%rd4, %rd1, %rd3;
	ld.b32 	%rd25, [%rd4];
	bra.uni 	$L__BB15_32;
$L__BB15_29:
	add.s64 	%rd7, %rd1, %rd2;
	ld.b8 	%rd25, [%rd7];
	bra.uni 	$L__BB15_32;
$L__BB15_26:
	shl.b64 	%rd15, %rd2, 3;
	add.s64 	%rd16, %rd1, %rd15;
	ld.b64 	%rd26, [%rd16];
	bra.uni 	$L__BB15_33;
$L__BB15_31:
	shl.b64 	%rd19, %rd2, 3;
	add.s64 	%rd20, %rd1, %rd19;
	ld.b64 	%rd25, [%rd20];
$L__BB15_32:
	setp.lt.s32 	%p14, %r4, 5;
	cvt.rn.f64.s64 	%rd21, %rd25;
	cvt.rn.f64.u64 	%rd22, %rd25;
	selp.f64 	%rd26, %rd21, %rd22, %p14;
$L__BB15_33:
	st.param.b64 	[func_retval0], %rd26;
	ret;
}
.visible .func _Z12q_store_partPvydi(
	.param .b64 _Z12q_store_partPvydi_param_0,
	.param .b64 _Z12q_store_partPvydi_param_1,
	.param .b64 _Z12q_store_partPvydi_param_2,
	.param .b32 _Z12q_store_partPvydi_param_3
)
{
	.reg .pred 	%p<22>;
	.reg .b16 	%rs<2>;
	.reg .b32 	%r<34>;
	.reg .b64 	%rd<41>;
	ld.param.b32 	%r9, [_Z12q_store_partPvydi_param_3];
	ld.param.b64 	%rd9, [_Z12q_store_partPvydi_param_2];
	ld.param.b64 	%rd8, [_Z12q_store_partPvydi_param_1];
	ld.param.b64 	%rd7, [_Z12q_store_partPvydi_param_0];
	and.b32 	%r10, %r9, -2;
	setp.ne.b32 	%p1, %r10, 12;
	@%p1 bra 	$L__BB16_16;
	shr.u64 	%rd2, %rd9, 48;
	cvt.u32.u64 	%r12, %rd2;
	and.b32 	%r1, %r12, 32768;
	shr.u64 	%rd14, %rd9, 52;
	cvt.u32.u64 	%r13, %rd14;
	and.b32 	%r2, %r13, 2047;
	setp.eq.b32 	%p4, %r2, 0;
	@%p4 bra 	$L__BB16_4;
	and.b64 	%rd1, %rd9, 4503599627370495;
	setp.eq.b32 	%p3, %r9, 12;
	selp.b32 	%r3, 11, 8, %p3;
	selp.b32 	%r5, 31744, 32640, %p3;
	setp.ne.b32 	%p5, %r2, 2047;
	@%p5 bra 	$L__BB16_5;
	setp.eq.b64 	%p6, %rd1, 0;
	add.s32 	%r14, %r3, -2;
	mov.b32 	%r15, 1;
	shl.b32 	%r16, %r15, %r14;
	selp.b32 	%r17, 0, %r16, %p6;
	or.b32 	%r18, %r5, %r17;
	or.b32 	%r19, %r18, %r1;
	cvt.u16.u32 	%rs1, %r19;
	bra.uni 	$L__BB16_15;
$L__BB16_16:
	setp.ne.b32 	%p2, %r9, 10;
	@%p2 bra 	$L__BB16_18;
	cvt.rn.f32.f64 	%r11, %rd9;
	shl.b64 	%rd12, %rd8, 2;
	add.s64 	%rd13, %rd7, %rd12;
	st.b32 	[%rd13], %r11;
	bra.uni 	$L__BB16_19;
$L__BB16_18:
	shl.b64 	%rd10, %rd8, 3;
	add.s64 	%rd11, %rd7, %rd10;
	st.b64 	[%rd11], %rd9;
	bra.uni 	$L__BB16_19;
$L__BB16_4:
	cvt.u16.u32 	%rs1, %r1;
	bra.uni 	$L__BB16_15;
$L__BB16_5:
	selp.b32 	%r20, -14, -126, %p3;
	add.s32 	%r6, %r2, -1023;
	or.b64 	%rd3, %rd1, 4503599627370496;
	setp.ge.s32 	%p7, %r6, %r20;
	@%p7 bra 	$L__BB16_11;
	and.b64 	%rd4, %rd2, 32768;
	selp.b32 	%r30, 28, -81, %p3;
	sub.s32 	%r7, %r30, %r6;
	setp.gt.s32 	%p15, %r7, 0;
	@%p15 bra 	$L__BB16_8;
	bra.uni 	$L__BB16_7;
$L__BB16_8:
	setp.gt.u32 	%p16, %r7, 63;
	mov.b64 	%rd40, 0;
	@%p16 bra 	$L__BB16_10;
	shr.u64 	%rd28, %rd3, %r7;
	mov.b64 	%rd29, -1;
	shl.b64 	%rd30, %rd29, %r7;
	not.b64 	%rd31, %rd30;
	and.b64 	%rd32, %rd3, %rd31;
	add.s32 	%r31, %r7, -1;
	mov.b64 	%rd33, 1;
	shl.b64 	%rd34, %rd33, %r31;
	setp.gt.u64 	%p17, %rd32, %rd34;
	setp.eq.b64 	%p18, %rd32, %rd34;
	and.b64 	%rd35, %rd28, 1;
	setp.ne.b64 	%p19, %rd35, 0;
	and.pred 	%p20, %p18, %p19;
	or.pred 	%p21, %p17, %p20;
	selp.b64 	%rd36, 1, 0, %p21;
	add.s64 	%rd40, %rd28, %rd36;
	bra.uni 	$L__BB16_10;
$L__BB16_11:
	selp.b32 	%r4, 15, 127, %p3;
	sub.s32 	%r21, 53, %r3;
	shr.u64 	%rd15, %rd3, %r21;
	mov.b64 	%rd16, -1;
	shl.b64 	%rd17, %rd16, %r21;
	not.b64 	%rd18, %rd17;
	and.b64 	%rd19, %rd18, %rd9;
	sub.s32 	%r22, 52, %r3;
	mov.b64 	%rd20, 1;
	shl.b64 	%rd21, %rd20, %r22;
	setp.gt.u64 	%p8, %rd19, %rd21;
	setp.eq.b64 	%p9, %rd19, %rd21;
	and.b64 	%rd22, %rd15, 1;
	setp.ne.b64 	%p10, %rd22, 0;
	and.pred 	%p11, %p9, %p10;
	or.pred 	%p12, %p8, %p11;
	selp.b64 	%rd23, 1, 0, %p12;
	add.s64 	%rd5, %rd15, %rd23;
	shl.b64 	%rd6, %rd20, %r3;
	setp.eq.b64 	%p13, %rd5, %rd6;
	add.s32 	%r23, %r2, -1022;
	selp.b32 	%r8, %r23, %r6, %p13;
	setp.le.s32 	%p14, %r8, %r4;
	@%p14 bra 	$L__BB16_13;
	or.b32 	%r33, %r1, %r5;
	bra.uni 	$L__BB16_14;
$L__BB16_13:
	selp.b32 	%r24, 1, 0, %p13;
	shr.u64 	%rd24, %rd5, %r24;
	add.s32 	%r25, %r8, %r4;
	add.s32 	%r26, %r3, -1;
	shl.b32 	%r27, %r25, %r26;
	shl.b64 	%rd25, %rd16, %r26;
	not.b64 	%rd26, %rd25;
	and.b64 	%rd27, %rd24, %rd26;
	cvt.u32.u64 	%r28, %rd27;
	or.b32 	%r29, %r27, %r28;
	or.b32 	%r33, %r29, %r1;
$L__BB16_14:
	cvt.u16.u32 	%rs1, %r33;
	bra.uni 	$L__BB16_15;
$L__BB16_7:
	neg.s32 	%r32, %r7;
	shl.b64 	%rd40, %rd3, %r32;
$L__BB16_10:
	or.b64 	%rd37, %rd40, %rd4;
	cvt.u16.u64 	%rs1, %rd37;
$L__BB16_15:
	shl.b64 	%rd38, %rd8, 1;
	add.s64 	%rd39, %rd7, %rd38;
	st.b16 	[%rd39], %rs1;
$L__BB16_19:
	ret;
}
.visible .entry q_kernel(
	.param .u64 .ptr .align 1 q_kernel_param_0,
	.param .u64 .ptr .align 1 q_kernel_param_1,
	.param .u64 .ptr .align 1 q_kernel_param_2,
	.param .u64 .ptr .align 1 q_kernel_param_3,
	.param .u64 .ptr .align 1 q_kernel_param_4,
	.param .u64 .ptr .align 1 q_kernel_param_5,
	.param .u64 .ptr .align 1 q_kernel_param_6,
	.param .u64 q_kernel_param_7,
	.param .u64 q_kernel_param_8,
	.param .u64 q_kernel_param_9,
	.param .u32 q_kernel_param_10,
	.param .u32 q_kernel_param_11,
	.param .u32 q_kernel_param_12,
	.param .u32 q_kernel_param_13,
	.param .u32 q_kernel_param_14,
	.param .u32 q_kernel_param_15,
	.param .u64 .ptr .align 1 q_kernel_param_16
)
{
	.reg .pred 	%p<244>;
	.reg .b16 	%rs<14>;
	.reg .b32 	%r<288>;
	.reg .b64 	%rd<318>;
	ld.param.b64 	%rd36, [q_kernel_param_6];
	ld.param.b64 	%rd32, [q_kernel_param_2];
	ld.param.b64 	%rd30, [q_kernel_param_0];
	cvta.to.global.u64 	%rd1, %rd32;
	cvta.to.global.u64 	%rd2, %rd30;
	cvta.to.global.u64 	%rd3, %rd36;
	mov.u32 %r56, %ctaid.x;
	mov.u32 %r57, %ntid.x;
	mov.u32 %r58, %tid.x;
	mul.wide.u32 	%rd40, %r57, %r56;
	ld.param.b64 	%rd41, [q_kernel_param_9];
	cvt.u64.u32 	%rd42, %r58;
	add.s64 	%rd4, %rd40, %rd42;
	setp.ge.u64 	%p1, %rd4, %rd41;
	@%p1 bra 	$L__BB17_367;
	ld.param.b64 	%rd39, [q_kernel_param_16];
	ld.param.b32 	%r53, [q_kernel_param_13];
	ld.param.b32 	%r50, [q_kernel_param_10];
	setp.gt.s32 	%p2, %r53, 7;
	@%p2 bra 	$L__BB17_6;
	setp.eq.b32 	%p5, %r53, 2;
	@%p5 bra 	$L__BB17_13;
	setp.eq.b32 	%p6, %r53, 7;
	@%p6 bra 	$L__BB17_4;
	bra.uni 	$L__BB17_363;
$L__BB17_4:
	setp.gt.s32 	%p31, %r50, 15;
	@%p31 bra 	$L__BB17_258;
	mov.b32 	%r281, 12;
	setp.eq.b32 	%p34, %r50, 14;
	@%p34 bra 	$L__BB17_262;
	setp.eq.b32 	%p35, %r50, 15;
	mov.b32 	%r281, %r50;
	@%p35 bra 	$L__BB17_257;
	bra.uni 	$L__BB17_262;
$L__BB17_257:
	mov.b32 	%r281, 13;
	bra.uni 	$L__BB17_262;
$L__BB17_6:
	setp.eq.b32 	%p3, %r53, 8;
	@%p3 bra 	$L__BB17_331;
	setp.eq.b32 	%p4, %r53, 9;
	@%p4 bra 	$L__BB17_8;
	bra.uni 	$L__BB17_363;
$L__BB17_8:
	mov.b32 	%r59, 8;
	mov.pred 	%p7, 0;
	setp.gt.u32 	%p8, %r50, 11;
	@%p8 bra 	$L__BB17_350;
	mov.b32 	%r60, 1;
	shl.b32 	%r61, %r60, %r50;
	and.b32 	%r62, %r61, 770;
	setp.ne.b32 	%p9, %r62, 0;
	mov.pred 	%p243, %p7;
	mov.b32 	%r285, %r59;
	@%p9 bra 	$L__BB17_357;
	and.b32 	%r63, %r61, 2084;
	setp.ne.b32 	%p10, %r63, 0;
	@%p10 bra 	$L__BB17_356;
	bra.uni 	$L__BB17_11;
$L__BB17_356:
	mov.b32 	%r285, 1;
	mov.pred 	%p243, -1;
	bra.uni 	$L__BB17_357;
$L__BB17_363:
	ld.param.b32 	%r52, [q_kernel_param_12];
	ld.param.b32 	%r51, [q_kernel_param_11];
	ld.param.b64 	%rd38, [q_kernel_param_8];
	ld.param.b64 	%rd37, [q_kernel_param_7];
	ld.param.b64 	%rd35, [q_kernel_param_5];
	ld.param.b64 	%rd34, [q_kernel_param_4];
	ld.param.b64 	%rd33, [q_kernel_param_3];
	ld.param.b64 	%rd31, [q_kernel_param_1];
	setp.eq.b32 	%p239, %r50, 17;
	@%p239 bra 	$L__BB17_365;
	setp.ne.b32 	%p240, %r50, 9;
	@%p240 bra 	$L__BB17_366;
$L__BB17_365:
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .b64 	param2;
	.param .b64 	param3;
	.param .b64 	param4;
	.param .b64 	param5;
	.param .b64 	param6;
	.param .b64 	param7;
	.param .b64 	param8;
	.param .b64 	param9;
	.param .b32 	param10;
	.param .b32 	param11;
	.param .b32 	param12;
	.param .b32 	param13;
	.param .b64 	param14;
	st.param.b64 	[param14], %rd39;
	st.param.b32 	[param13], %r53;
	st.param.b32 	[param12], %r52;
	st.param.b32 	[param11], %r51;
	st.param.b32 	[param10], %r50;
	st.param.b64 	[param9], %rd4;
	st.param.b64 	[param8], %rd38;
	st.param.b64 	[param7], %rd37;
	st.param.b64 	[param6], %rd36;
	st.param.b64 	[param5], %rd35;
	st.param.b64 	[param4], %rd34;
	st.param.b64 	[param3], %rd33;
	st.param.b64 	[param2], %rd32;
	st.param.b64 	[param1], %rd31;
	st.param.b64 	[param0], %rd30;
	call.uni _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj, (param0, param1, param2, param3, param4, param5, param6, param7, param8, param9, param10, param11, param12, param13, param14);
	}
	bra.uni 	$L__BB17_367;
$L__BB17_13:
	ld.param.b32 	%r54, [q_kernel_param_14];
	setp.gt.s32 	%p76, %r54, 15;
	@%p76 bra 	$L__BB17_17;
	mov.b32 	%r269, 12;
	setp.eq.b32 	%p79, %r54, 14;
	@%p79 bra 	$L__BB17_21;
	setp.eq.b32 	%p80, %r54, 15;
	mov.b32 	%r269, %r54;
	@%p80 bra 	$L__BB17_16;
	bra.uni 	$L__BB17_21;
$L__BB17_16:
	mov.b32 	%r269, 13;
	bra.uni 	$L__BB17_21;
$L__BB17_331:
	setp.gt.s32 	%p19, %r50, 15;
	@%p19 bra 	$L__BB17_335;
	mov.b32 	%r284, 12;
	setp.eq.b32 	%p22, %r50, 14;
	@%p22 bra 	$L__BB17_339;
	setp.eq.b32 	%p23, %r50, 15;
	mov.b32 	%r284, %r50;
	@%p23 bra 	$L__BB17_334;
	bra.uni 	$L__BB17_339;
$L__BB17_334:
	mov.b32 	%r284, 13;
	bra.uni 	$L__BB17_339;
$L__BB17_258:
	setp.eq.b32 	%p32, %r50, 16;
	@%p32 bra 	$L__BB17_261;
	setp.ne.b32 	%p33, %r50, 17;
	mov.b32 	%r281, %r50;
	@%p33 bra 	$L__BB17_262;
	mov.b32 	%r281, 9;
	bra.uni 	$L__BB17_262;
$L__BB17_17:
	setp.eq.b32 	%p77, %r54, 16;
	@%p77 bra 	$L__BB17_20;
	setp.ne.b32 	%p78, %r54, 17;
	mov.b32 	%r269, %r54;
	@%p78 bra 	$L__BB17_21;
	mov.b32 	%r269, 9;
	bra.uni 	$L__BB17_21;
$L__BB17_335:
	setp.eq.b32 	%p20, %r50, 16;
	@%p20 bra 	$L__BB17_338;
	setp.ne.b32 	%p21, %r50, 17;
	mov.b32 	%r284, %r50;
	@%p21 bra 	$L__BB17_339;
	mov.b32 	%r284, 9;
	bra.uni 	$L__BB17_339;
$L__BB17_366:
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .b64 	param2;
	.param .b64 	param3;
)QPTX";
        result += R"QPTX(
	.param .b64 	param4;
	.param .b64 	param5;
	.param .b64 	param6;
	.param .b64 	param7;
	.param .b64 	param8;
	.param .b64 	param9;
	.param .b32 	param10;
	.param .b32 	param11;
	.param .b32 	param12;
	.param .b32 	param13;
	.param .b64 	param14;
	st.param.b64 	[param14], %rd39;
	st.param.b32 	[param13], %r53;
	st.param.b32 	[param12], %r52;
	st.param.b32 	[param11], %r51;
	st.param.b32 	[param10], %r50;
	st.param.b64 	[param9], %rd4;
	st.param.b64 	[param8], %rd38;
	st.param.b64 	[param7], %rd37;
	st.param.b64 	[param6], %rd36;
	st.param.b64 	[param5], %rd35;
	st.param.b64 	[param4], %rd34;
	st.param.b64 	[param3], %rd33;
	st.param.b64 	[param2], %rd32;
	st.param.b64 	[param1], %rd31;
	st.param.b64 	[param0], %rd30;
	call.uni _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj, (param0, param1, param2, param3, param4, param5, param6, param7, param8, param9, param10, param11, param12, param13, param14);
	}
	bra.uni 	$L__BB17_367;
$L__BB17_11:
	mov.b32 	%r64, 1;
	shl.b32 	%r65, %r64, %r50;
	and.b32 	%r66, %r65, 72;
	setp.ne.b32 	%p11, %r66, 0;
	@%p11 bra 	$L__BB17_12;
	bra.uni 	$L__BB17_350;
$L__BB17_12:
	mov.b32 	%r285, 2;
	mov.pred 	%p243, -1;
$L__BB17_357:
	cvt.u64.u32 	%rd24, %r285;
	mul.lo.s64 	%rd25, %rd4, %rd24;
	shl.b64 	%rd43, %rd4, 3;
	add.s64 	%rd44, %rd3, %rd43;
	ld.global.b64 	%rd45, [%rd44];
	mul.lo.s64 	%rd26, %rd45, %rd24;
	and.b32 	%r287, %r285, 3;
	mov.b32 	%r286, 0;
	@%p243 bra 	$L__BB17_361;
	add.s64 	%rd27, %rd1, %rd26;
	and.b64 	%rd28, %rd24, 28;
	add.s64 	%rd46, %rd25, %rd2;
	add.s64 	%rd29, %rd46, 1;
	mov.b64 	%rd315, 0;
	cvt.u32.u64 	%r71, %rd28;
$L__BB17_359:
	add.s64 	%rd47, %rd27, %rd315;
	ld.global.b8 	%rs7, [%rd47];
	add.s64 	%rd48, %rd29, %rd315;
	st.global.b8 	[%rd48+-1], %rs7;
	ld.global.b8 	%rs8, [%rd47+1];
	st.global.b8 	[%rd48], %rs8;
	ld.global.b8 	%rs9, [%rd47+2];
	st.global.b8 	[%rd48+1], %rs9;
	ld.global.b8 	%rs10, [%rd47+3];
	st.global.b8 	[%rd48+2], %rs10;
	add.s64 	%rd315, %rd315, 4;
	cvt.u32.u64 	%r286, %rd315;
	setp.eq.b32 	%p16, %r71, %r286;
	@%p16 bra 	$L__BB17_360;
	bra.uni 	$L__BB17_359;
$L__BB17_360:
	setp.eq.b32 	%p17, %r287, 0;
	@%p17 bra 	$L__BB17_367;
$L__BB17_361:
	cvt.u64.u32 	%rd49, %r286;
	add.s64 	%rd50, %rd26, %rd49;
	add.s64 	%rd317, %rd1, %rd50;
	add.s64 	%rd51, %rd25, %rd49;
	add.s64 	%rd316, %rd2, %rd51;
$L__BB17_362:
	.pragma "nounroll";
	ld.global.b8 	%rs11, [%rd317];
	st.global.b8 	[%rd316], %rs11;
	add.s64 	%rd317, %rd317, 1;
	add.s64 	%rd316, %rd316, 1;
	add.s32 	%r287, %r287, -1;
	setp.ne.b32 	%p18, %r287, 0;
	@%p18 bra 	$L__BB17_362;
	bra.uni 	$L__BB17_367;
$L__BB17_261:
	mov.b32 	%r281, 10;
$L__BB17_262:
	add.s32 	%r40, %r50, -14;
	setp.lt.u32 	%p36, %r40, 4;
	selp.b32 	%r82, 1, 0, %p36;
	shl.b64 	%rd22, %rd4, %r82;
	and.b32 	%r41, %r281, -2;
	setp.ne.b32 	%p37, %r41, 12;
	@%p37 bra 	$L__BB17_272;
	shl.b64 	%rd93, %rd22, 1;
	add.s64 	%rd94, %rd1, %rd93;
	ld.global.b16 	%rs5, [%rd94];
	setp.ne.b32 	%p51, %r281, 13;
	cvt.u32.u16 	%r42, %rs5;
	@%p51 bra 	$L__BB17_265;
	shl.b32 	%r282, %r42, 16;
	bra.uni 	$L__BB17_271;
$L__BB17_272:
	setp.gt.s32 	%p38, %r281, 4;
	@%p38 bra 	$L__BB17_280;
	bra.uni 	$L__BB17_273;
$L__BB17_280:
	setp.gt.s32 	%p39, %r281, 6;
	@%p39 bra 	$L__BB17_284;
	bra.uni 	$L__BB17_281;
$L__BB17_284:
	setp.eq.b32 	%p40, %r281, 7;
	@%p40 bra 	$L__BB17_292;
	setp.eq.b32 	%p41, %r281, 9;
	@%p41 bra 	$L__BB17_288;
	setp.ne.b32 	%p42, %r281, 10;
	@%p42 bra 	$L__BB17_293;
	shl.b64 	%rd87, %rd22, 2;
	add.s64 	%rd88, %rd1, %rd87;
	ld.global.b32 	%r83, [%rd88];
	cvt.f64.f32 	%rd312, %r83;
	bra.uni 	$L__BB17_295;
$L__BB17_265:
	cvt.s32.s16 	%r84, %rs5;
	and.b32 	%r282, %r84, -2147483648;
	bfe.u32 	%r43, %r42, 10, 5;
	setp.eq.b32 	%p52, %r43, 31;
	@%p52 bra 	$L__BB17_269;
	and.b32 	%r44, %r42, 1023;
	setp.ne.b32 	%p53, %r43, 0;
	@%p53 bra 	$L__BB17_270;
	setp.eq.b32 	%p54, %r44, 0;
	@%p54 bra 	$L__BB17_271;
	clz.b32 	%r87, %r44;
	xor.b32 	%r88, %r87, 31;
	sub.s32 	%r89, 9, %r88;
	shl.b32 	%r90, %r42, %r89;
	shl.b32 	%r91, %r88, 23;
	shl.b32 	%r92, %r90, 14;
	and.b32 	%r93, %r92, 8372224;
	add.s32 	%r94, %r91, %r282;
	add.s32 	%r95, %r94, %r93;
	add.s32 	%r282, %r95, 864026624;
	bra.uni 	$L__BB17_271;
$L__BB17_273:
	setp.gt.s32 	%p45, %r281, 2;
	@%p45 bra 	$L__BB17_277;
	setp.eq.b32 	%p48, %r281, 1;
	@%p48 bra 	$L__BB17_289;
	setp.eq.b32 	%p49, %r281, 2;
	@%p49 bra 	$L__BB17_276;
	bra.uni 	$L__BB17_293;
$L__BB17_276:
	add.s64 	%rd82, %rd1, %rd22;
	ld.global.s8 	%rd311, [%rd82];
	bra.uni 	$L__BB17_294;
$L__BB17_20:
	mov.b32 	%r269, 10;
$L__BB17_21:
	add.s32 	%r1, %r54, -14;
	setp.lt.u32 	%p81, %r1, 4;
	selp.b32 	%r119, 1, 0, %p81;
	shl.b64 	%rd5, %rd4, %r119;
	and.b32 	%r2, %r269, -2;
	setp.ne.b32 	%p82, %r2, 12;
	@%p82 bra 	$L__BB17_31;
	shl.b64 	%rd139, %rd5, 1;
	add.s64 	%rd140, %rd1, %rd139;
	ld.global.b16 	%rs1, [%rd140];
	setp.ne.b32 	%p96, %r269, 13;
	cvt.u32.u16 	%r3, %rs1;
	@%p96 bra 	$L__BB17_24;
	shl.b32 	%r270, %r3, 16;
	bra.uni 	$L__BB17_30;
$L__BB17_31:
	setp.gt.s32 	%p83, %r269, 4;
	@%p83 bra 	$L__BB17_39;
	bra.uni 	$L__BB17_32;
$L__BB17_39:
	setp.gt.s32 	%p84, %r269, 6;
	@%p84 bra 	$L__BB17_43;
	bra.uni 	$L__BB17_40;
$L__BB17_43:
	setp.eq.b32 	%p85, %r269, 7;
	@%p85 bra 	$L__BB17_51;
	setp.eq.b32 	%p86, %r269, 9;
	@%p86 bra 	$L__BB17_47;
	setp.ne.b32 	%p87, %r269, 10;
	@%p87 bra 	$L__BB17_52;
	shl.b64 	%rd133, %rd5, 2;
	add.s64 	%rd134, %rd1, %rd133;
	ld.global.b32 	%r120, [%rd134];
	cvt.f64.f32 	%rd304, %r120;
	bra.uni 	$L__BB17_54;
$L__BB17_24:
	cvt.s32.s16 	%r121, %rs1;
	and.b32 	%r270, %r121, -2147483648;
	bfe.u32 	%r4, %r3, 10, 5;
	setp.eq.b32 	%p97, %r4, 31;
	@%p97 bra 	$L__BB17_28;
	and.b32 	%r5, %r3, 1023;
	setp.ne.b32 	%p98, %r4, 0;
	@%p98 bra 	$L__BB17_29;
	setp.eq.b32 	%p99, %r5, 0;
	@%p99 bra 	$L__BB17_30;
	clz.b32 	%r124, %r5;
	xor.b32 	%r125, %r124, 31;
	sub.s32 	%r126, 9, %r125;
	shl.b32 	%r127, %r3, %r126;
	shl.b32 	%r128, %r125, 23;
	shl.b32 	%r129, %r127, 14;
	and.b32 	%r130, %r129, 8372224;
	add.s32 	%r131, %r128, %r270;
	add.s32 	%r132, %r131, %r130;
	add.s32 	%r270, %r132, 864026624;
	bra.uni 	$L__BB17_30;
$L__BB17_32:
	setp.gt.s32 	%p90, %r269, 2;
	@%p90 bra 	$L__BB17_36;
	setp.eq.b32 	%p93, %r269, 1;
	@%p93 bra 	$L__BB17_48;
	setp.eq.b32 	%p94, %r269, 2;
	@%p94 bra 	$L__BB17_35;
	bra.uni 	$L__BB17_52;
$L__BB17_35:
	add.s64 	%rd128, %rd1, %rd5;
	ld.global.s8 	%rd300, [%rd128];
	bra.uni 	$L__BB17_53;
$L__BB17_338:
	mov.b32 	%r284, 10;
$L__BB17_339:
	add.s32 	%r48, %r50, -14;
	setp.lt.u32 	%p24, %r48, 4;
	selp.b32 	%r72, 1, 0, %p24;
	shl.b64 	%rd23, %rd4, %r72;
	and.b32 	%r49, %r284, -2;
	setp.ne.b32 	%p25, %r49, 12;
	@%p25 bra 	$L__BB17_341;
	setp.eq.b32 	%p27, %r284, 12;
	selp.b32 	%r73, 11, 8, %p27;
	selp.b32 	%r74, 15, 127, %p27;
	sub.s32 	%r75, 53, %r73;
	mov.b64 	%rd56, 4503599627370496;
	shr.u64 	%rd57, %rd56, %r75;
	mov.b64 	%rd58, 1;
	shl.b64 	%rd59, %rd58, %r73;
	setp.eq.b64 	%p28, %rd57, %rd59;
	selp.b32 	%r76, 1, 0, %p28;
	shr.u64 	%rd60, %rd57, %r76;
	add.s32 	%r77, %r74, %r76;
	add.s32 	%r78, %r73, -1;
	shl.b32 	%r79, %r77, %r78;
	mov.b64 	%rd61, -1;
	shl.b64 	%rd62, %rd61, %r78;
	not.b64 	%rd63, %rd62;
	and.b64 	%rd64, %rd60, %rd63;
	cvt.u32.u64 	%r80, %rd64;
	or.b32 	%r81, %r79, %r80;
	shl.b64 	%rd65, %rd23, 1;
	add.s64 	%rd66, %rd2, %rd65;
	st.global.b16 	[%rd66], %r81;
	bra.uni 	$L__BB17_344;
$L__BB17_341:
	setp.ne.b32 	%p26, %r284, 10;
	@%p26 bra 	$L__BB17_343;
	shl.b64 	%rd54, %rd23, 2;
	add.s64 	%rd55, %rd2, %rd54;
	st.global.b32 	[%rd55], 1065353216;
	bra.uni 	$L__BB17_344;
$L__BB17_343:
	shl.b64 	%rd52, %rd23, 3;
	add.s64 	%rd53, %rd2, %rd52;
	st.global.b64 	[%rd53], 4607182418800017408;
$L__BB17_344:
	setp.gt.u32 	%p29, %r48, 3;
	@%p29 bra 	$L__BB17_367;
	@%p25 bra 	$L__BB17_347;
	shl.b64 	%rd71, %rd23, 1;
	add.s64 	%rd72, %rd2, %rd71;
	st.global.b16 	[%rd72+2], 0;
	bra.uni 	$L__BB17_367;
$L__BB17_347:
	setp.ne.b32 	%p30, %r284, 10;
	@%p30 bra 	$L__BB17_349;
	shl.b64 	%rd69, %rd23, 2;
	add.s64 	%rd70, %rd2, %rd69;
	st.global.b32 	[%rd70+4], 0;
	bra.uni 	$L__BB17_367;
$L__BB17_349:
	shl.b64 	%rd67, %rd23, 3;
	add.s64 	%rd68, %rd2, %rd67;
	st.global.b64 	[%rd68+8], 0;
	bra.uni 	$L__BB17_367;
$L__BB17_277:
	setp.eq.b32 	%p46, %r281, 3;
	@%p46 bra 	$L__BB17_290;
	setp.eq.b32 	%p47, %r281, 4;
	@%p47 bra 	$L__BB17_279;
	bra.uni 	$L__BB17_293;
$L__BB17_279:
	shl.b64 	%rd78, %rd22, 2;
	add.s64 	%rd79, %rd1, %rd78;
	ld.global.s32 	%rd311, [%rd79];
	bra.uni 	$L__BB17_294;
$L__BB17_36:
	setp.eq.b32 	%p91, %r269, 3;
	@%p91 bra 	$L__BB17_49;
	setp.eq.b32 	%p92, %r269, 4;
	@%p92 bra 	$L__BB17_38;
	bra.uni 	$L__BB17_52;
$L__BB17_38:
	shl.b64 	%rd124, %rd5, 2;
	add.s64 	%rd125, %rd1, %rd124;
	ld.global.s32 	%rd300, [%rd125];
	bra.uni 	$L__BB17_53;
$L__BB17_281:
	setp.eq.b32 	%p43, %r281, 5;
	@%p43 bra 	$L__BB17_291;
	setp.eq.b32 	%p44, %r281, 6;
	@%p44 bra 	$L__BB17_283;
	bra.uni 	$L__BB17_293;
$L__BB17_283:
	shl.b64 	%rd75, %rd22, 1;
	add.s64 	%rd76, %rd1, %rd75;
	ld.global.b16 	%rd311, [%rd76];
	bra.uni 	$L__BB17_294;
$L__BB17_40:
	setp.eq.b32 	%p88, %r269, 5;
	@%p88 bra 	$L__BB17_50;
	setp.eq.b32 	%p89, %r269, 6;
	@%p89 bra 	$L__BB17_42;
	bra.uni 	$L__BB17_52;
$L__BB17_42:
	shl.b64 	%rd121, %rd5, 1;
	add.s64 	%rd122, %rd1, %rd121;
	ld.global.b16 	%rd300, [%rd122];
	bra.uni 	$L__BB17_53;
$L__BB17_350:
	and.b32 	%r67, %r50, -2;
	setp.eq.b32 	%p12, %r67, 12;
	mov.b32 	%r285, 2;
	mov.pred 	%p243, -1;
	@%p12 bra 	$L__BB17_357;
	setp.gt.u32 	%p13, %r50, 16;
	@%p13 bra 	$L__BB17_355;
	mov.b32 	%r285, 4;
	mov.b32 	%r68, 1;
	shl.b32 	%r69, %r68, %r50;
	and.b32 	%r70, %r69, 50320;
	setp.ne.b32 	%p14, %r70, 0;
	mov.pred 	%p243, %p7;
	@%p14 bra 	$L__BB17_357;
	setp.eq.b32 	%p15, %r50, 16;
	@%p15 bra 	$L__BB17_354;
	bra.uni 	$L__BB17_355;
$L__BB17_354:
	mov.pred 	%p243, %p7;
	mov.b32 	%r285, %r59;
	bra.uni 	$L__BB17_357;
$L__BB17_269:
	shl.b32 	%r85, %r42, 13;
	or.b32 	%r86, %r282, %r85;
	or.b32 	%r282, %r86, 2139095040;
	bra.uni 	$L__BB17_271;
$L__BB17_28:
	shl.b32 	%r122, %r3, 13;
	or.b32 	%r123, %r270, %r122;
	or.b32 	%r270, %r123, 2139095040;
	bra.uni 	$L__BB17_30;
$L__BB17_270:
	shl.b32 	%r96, %r43, 23;
	shl.b32 	%r97, %r44, 13;
	or.b32 	%r98, %r96, %r97;
	add.s32 	%r99, %r98, %r282;
	add.s32 	%r282, %r99, 939524096;
$L__BB17_271:
	cvt.f64.f32 	%rd312, %r282;
	bra.uni 	$L__BB17_295;
$L__BB17_29:
	shl.b32 	%r133, %r4, 23;
	shl.b32 	%r134, %r5, 13;
	or.b32 	%r135, %r133, %r134;
	add.s32 	%r136, %r135, %r270;
	add.s32 	%r270, %r136, 939524096;
$L__BB17_30:
	cvt.f64.f32 	%rd304, %r270;
	bra.uni 	$L__BB17_54;
$L__BB17_289:
	shl.b64 	%rd83, %rd22, 3;
	add.s64 	%rd84, %rd1, %rd83;
	ld.global.b64 	%rd311, [%rd84];
	bra.uni 	$L__BB17_294;
$L__BB17_290:
	shl.b64 	%rd80, %rd22, 1;
	add.s64 	%rd81, %rd1, %rd80;
	ld.global.s16 	%rd311, [%rd81];
	bra.uni 	$L__BB17_294;
$L__BB17_292:
	shl.b64 	%rd73, %rd22, 2;
	add.s64 	%rd74, %rd1, %rd73;
	ld.global.b32 	%rd311, [%rd74];
	bra.uni 	$L__BB17_294;
$L__BB17_48:
	shl.b64 	%rd129, %rd5, 3;
	add.s64 	%rd130, %rd1, %rd129;
	ld.global.b64 	%rd300, [%rd130];
	bra.uni 	$L__BB17_53;
$L__BB17_49:
	shl.b64 	%rd126, %rd5, 1;
	add.s64 	%rd127, %rd1, %rd126;
	ld.global.s16 	%rd300, [%rd127];
	bra.uni 	$L__BB17_53;
$L__BB17_51:
	shl.b64 	%rd119, %rd5, 2;
	add.s64 	%rd120, %rd1, %rd119;
	ld.global.b32 	%rd300, [%rd120];
	bra.uni 	$L__BB17_53;
$L__BB17_291:
	add.s64 	%rd77, %rd1, %rd22;
	ld.global.b8 	%rd311, [%rd77];
	bra.uni 	$L__BB17_294;
$L__BB17_50:
	add.s64 	%rd123, %rd1, %rd5;
	ld.global.b8 	%rd300, [%rd123];
	bra.uni 	$L__BB17_53;
$L__BB17_288:
	shl.b64 	%rd85, %rd22, 3;
	add.s64 	%rd86, %rd1, %rd85;
	ld.global.b64 	%rd312, [%rd86];
	bra.uni 	$L__BB17_295;
$L__BB17_47:
	shl.b64 	%rd131, %rd5, 3;
	add.s64 	%rd132, %rd1, %rd131;
	ld.global.b64 	%rd304, [%rd132];
	bra.uni 	$L__BB17_54;
$L__BB17_293:
	shl.b64 	%rd89, %rd22, 3;
	add.s64 	%rd90, %rd1, %rd89;
	ld.global.b64 	%rd311, [%rd90];
$L__BB17_294:
	setp.lt.s32 	%p50, %r281, 5;
	cvt.rn.f64.s64 	%rd91, %rd311;
	cvt.rn.f64.u64 	%rd92, %rd311;
	selp.f64 	%rd312, %rd91, %rd92, %p50;
$L__BB17_295:
	setp.gt.u32 	%p55, %r40, 3;
	mov.b64 	%rd314, 0d0000000000000000;
	@%p55 bra 	$L__BB17_329;
	@%p37 bra 	$L__BB17_306;
	shl.b64 	%rd115, %rd22, 1;
	add.s64 	%rd116, %rd1, %rd115;
	ld.global.b16 	%rs6, [%rd116+2];
	setp.ne.b32 	%p69, %r281, 13;
	cvt.u32.u16 	%r45, %rs6;
	@%p69 bra 	$L__BB17_299;
	shl.b32 	%r283, %r45, 16;
	bra.uni 	$L__BB17_305;
$L__BB17_306:
	setp.gt.s32 	%p56, %r281, 4;
	@%p56 bra 	$L__BB17_314;
	bra.uni 	$L__BB17_307;
$L__BB17_314:
	setp.gt.s32 	%p57, %r281, 6;
	@%p57 bra 	$L__BB17_318;
	bra.uni 	$L__BB17_315;
$L__BB17_318:
	setp.eq.b32 	%p58, %r281, 7;
	@%p58 bra 	$L__BB17_326;
	setp.eq.b32 	%p59, %r281, 9;
	@%p59 bra 	$L__BB17_322;
	setp.ne.b32 	%p60, %r281, 10;
	@%p60 bra 	$L__BB17_327;
	shl.b64 	%rd109, %rd22, 2;
	add.s64 	%rd110, %rd1, %rd109;
	ld.global.b32 	%r100, [%rd110+4];
	cvt.f64.f32 	%rd314, %r100;
	bra.uni 	$L__BB17_329;
$L__BB17_299:
	cvt.s32.s16 	%r101, %rs6;
	and.b32 	%r283, %r101, -2147483648;
	bfe.u32 	%r46, %r45, 10, 5;
	setp.eq.b32 	%p70, %r46, 31;
	@%p70 bra 	$L__BB17_303;
	and.b32 	%r47, %r45, 1023;
	setp.ne.b32 	%p71, %r46, 0;
	@%p71 bra 	$L__BB17_304;
	setp.eq.b32 	%p72, %r47, 0;
	@%p72 bra 	$L__BB17_305;
	clz.b32 	%r104, %r47;
	xor.b32 	%r105, %r104, 31;
	sub.s32 	%r106, 9, %r105;
	shl.b32 	%r107, %r45, %r106;
	shl.b32 	%r108, %r105, 23;
	shl.b32 	%r109, %r107, 14;
	and.b32 	%r110, %r109, 8372224;
	add.s32 	%r111, %r108, %r283;
	add.s32 	%r112, %r111, %r110;
	add.s32 	%r283, %r112, 864026624;
	bra.uni 	$L__BB17_305;
$L__BB17_307:
	setp.gt.s32 	%p63, %r281, 2;
	@%p63 bra 	$L__BB17_311;
	setp.eq.b32 	%p66, %r281, 1;
	@%p66 bra 	$L__BB17_323;
	setp.eq.b32 	%p67, %r281, 2;
	@%p67 bra 	$L__BB17_310;
	bra.uni 	$L__BB17_327;
$L__BB17_310:
	add.s64 	%rd104, %rd1, %rd22;
	ld.global.s8 	%rd313, [%rd104+1];
	bra.uni 	$L__BB17_328;
$L__BB17_311:
	setp.eq.b32 	%p64, %r281, 3;
	@%p64 bra 	$L__BB17_324;
	setp.eq.b32 	%p65, %r281, 4;
	@%p65 bra 	$L__BB17_313;
	bra.uni 	$L__BB17_327;
$L__BB17_313:
	shl.b64 	%rd100, %rd22, 2;
	add.s64 	%rd101, %rd1, %rd100;
	ld.global.s32 	%rd313, [%rd101+4];
	bra.uni 	$L__BB17_328;
$L__BB17_315:
	setp.eq.b32 	%p61, %r281, 5;
	@%p61 bra 	$L__BB17_325;
	setp.eq.b32 	%p62, %r281, 6;
	@%p62 bra 	$L__BB17_317;
	bra.uni 	$L__BB17_327;
$L__BB17_317:
	shl.b64 	%rd97, %rd22, 1;
	add.s64 	%rd98, %rd1, %rd97;
	ld.global.b16 	%rd313, [%rd98+2];
	bra.uni 	$L__BB17_328;
$L__BB17_52:
	shl.b64 	%rd135, %rd5, 3;
	add.s64 	%rd136, %rd1, %rd135;
	ld.global.b64 	%rd300, [%rd136];
$L__BB17_53:
	setp.lt.s32 	%p95, %r269, 5;
	cvt.rn.f64.s64 	%rd137, %rd300;
	cvt.rn.f64.u64 	%rd138, %rd300;
	selp.f64 	%rd304, %rd137, %rd138, %p95;
$L__BB17_54:
	ld.param.b32 	%r55, [q_kernel_param_15];
	setp.gt.u32 	%p100, %r1, 3;
	mov.b64 	%rd6, 0d0000000000000000;
	@%p100 bra 	$L__BB17_88;
	@%p82 bra 	$L__BB17_65;
	shl.b64 	%rd161, %rd5, 1;
	add.s64 	%rd162, %rd1, %rd161;
	ld.global.b16 	%rs2, [%rd162+2];
	setp.ne.b32 	%p114, %r269, 13;
	cvt.u32.u16 	%r6, %rs2;
	@%p114 bra 	$L__BB17_58;
	shl.b32 	%r271, %r6, 16;
	bra.uni 	$L__BB17_64;
$L__BB17_65:
	setp.gt.s32 	%p101, %r269, 4;
	@%p101 bra 	$L__BB17_73;
	bra.uni 	$L__BB17_66;
$L__BB17_73:
	setp.gt.s32 	%p102, %r269, 6;
	@%p102 bra 	$L__BB17_77;
	bra.uni 	$L__BB17_74;
$L__BB17_77:
	setp.eq.b32 	%p103, %r269, 7;
	@%p103 bra 	$L__BB17_85;
	setp.eq.b32 	%p104, %r269, 9;
	@%p104 bra 	$L__BB17_81;
	setp.ne.b32 	%p105, %r269, 10;
	@%p105 bra 	$L__BB17_86;
	shl.b64 	%rd155, %rd5, 2;
	add.s64 	%rd156, %rd1, %rd155;
	ld.global.b32 	%r137, [%rd156+4];
	cvt.f64.f32 	%rd6, %r137;
	bra.uni 	$L__BB17_88;
$L__BB17_58:
	cvt.s32.s16 	%r138, %rs2;
	and.b32 	%r271, %r138, -2147483648;
	bfe.u32 	%r7, %r6, 10, 5;
	setp.eq.b32 	%p115, %r7, 31;
	@%p115 bra 	$L__BB17_62;
	and.b32 	%r8, %r6, 1023;
	setp.ne.b32 	%p116, %r7, 0;
	@%p116 bra 	$L__BB17_63;
	setp.eq.b32 	%p117, %r8, 0;
	@%p117 bra 	$L__BB17_64;
	clz.b32 	%r141, %r8;
	xor.b32 	%r142, %r141, 31;
	sub.s32 	%r143, 9, %r142;
	shl.b32 	%r144, %r6, %r143;
	shl.b32 	%r145, %r142, 23;
	shl.b32 	%r146, %r144, 14;
	and.b32 	%r147, %r146, 8372224;
	add.s32 	%r148, %r145, %r271;
	add.s32 	%r149, %r148, %r147;
	add.s32 	%r271, %r149, 864026624;
	bra.uni 	$L__BB17_64;
$L__BB17_66:
	setp.gt.s32 	%p108, %r269, 2;
	@%p108 bra 	$L__BB17_70;
	setp.eq.b32 	%p111, %r269, 1;
	@%p111 bra 	$L__BB17_82;
	setp.eq.b32 	%p112, %r269, 2;
	@%p112 bra 	$L__BB17_69;
	bra.uni 	$L__BB17_86;
$L__BB17_69:
	add.s64 	%rd150, %rd1, %rd5;
	ld.global.s8 	%rd301, [%rd150+1];
	bra.uni 	$L__BB17_87;
$L__BB17_70:
	setp.eq.b32 	%p109, %r269, 3;
	@%p109 bra 	$L__BB17_83;
	setp.eq.b32 	%p110, %r269, 4;
	@%p110 bra 	$L__BB17_72;
	bra.uni 	$L__BB17_86;
$L__BB17_72:
	shl.b64 	%rd146, %rd5, 2;
	add.s64 	%rd147, %rd1, %rd146;
	ld.global.s32 	%rd301, [%rd147+4];
	bra.uni 	$L__BB17_87;
$L__BB17_74:
	setp.eq.b32 	%p106, %r269, 5;
	@%p106 bra 	$L__BB17_84;
	setp.eq.b32 	%p107, %r269, 6;
	@%p107 bra 	$L__BB17_76;
	bra.uni 	$L__BB17_86;
$L__BB17_76:
	shl.b64 	%rd143, %rd5, 1;
	add.s64 	%rd144, %rd1, %rd143;
	ld.global.b16 	%rd301, [%rd144+2];
	bra.uni 	$L__BB17_87;
$L__BB17_303:
	shl.b32 	%r102, %r45, 13;
	or.b32 	%r103, %r283, %r102;
	or.b32 	%r283, %r103, 2139095040;
	bra.uni 	$L__BB17_305;
$L__BB17_62:
	shl.b32 	%r139, %r6, 13;
	or.b32 	%r140, %r271, %r139;
	or.b32 	%r271, %r140, 2139095040;
	bra.uni 	$L__BB17_64;
$L__BB17_304:
	shl.b32 	%r113, %r46, 23;
	shl.b32 	%r114, %r47, 13;
	or.b32 	%r115, %r113, %r114;
	add.s32 	%r116, %r115, %r283;
	add.s32 	%r283, %r116, 939524096;
$L__BB17_305:
	cvt.f64.f32 	%rd314, %r283;
	bra.uni 	$L__BB17_329;
$L__BB17_63:
	shl.b32 	%r150, %r7, 23;
	shl.b32 	%r151, %r8, 13;
	or.b32 	%r152, %r150, %r151;
	add.s32 	%r153, %r152, %r271;
	add.s32 	%r271, %r153, 939524096;
$L__BB17_64:
	cvt.f64.f32 	%rd6, %r271;
	bra.uni 	$L__BB17_88;
$L__BB17_323:
	shl.b64 	%rd105, %rd22, 3;
	add.s64 	%rd106, %rd1, %rd105;
	ld.global.b64 	%rd313, [%rd106+8];
	bra.uni 	$L__BB17_328;
$L__BB17_324:
	shl.b64 	%rd102, %rd22, 1;
	add.s64 	%rd103, %rd1, %rd102;
	ld.global.s16 	%rd313, [%rd103+2];
	bra.uni 	$L__BB17_328;
$L__BB17_326:
	shl.b64 	%rd95, %rd22, 2;
	add.s64 	%rd96, %rd1, %rd95;
	ld.global.b32 	%rd313, [%rd96+4];
	bra.uni 	$L__BB17_328;
$L__BB17_82:
	shl.b64 	%rd151, %rd5, 3;
	add.s64 	%rd152, %rd1, %rd151;
	ld.global.b64 	%rd301, [%rd152+8];
	bra.uni 	$L__BB17_87;
$L__BB17_83:
	shl.b64 	%rd148, %rd5, 1;
	add.s64 	%rd149, %rd1, %rd148;
	ld.global.s16 	%rd301, [%rd149+2];
	bra.uni 	$L__BB17_87;
$L__BB17_85:
	shl.b64 	%rd141, %rd5, 2;
	add.s64 	%rd142, %rd1, %rd141;
	ld.global.b32 	%rd301, [%rd142+4];
	bra.uni 	$L__BB17_87;
$L__BB17_325:
	add.s64 	%rd99, %rd1, %rd22;
	ld.global.b8 	%rd313, [%rd99+1];
	bra.uni 	$L__BB17_328;
$L__BB17_84:
	add.s64 	%rd145, %rd1, %rd5;
	ld.global.b8 	%rd301, [%rd145+1];
	bra.uni 	$L__BB17_87;
$L__BB17_322:
	shl.b64 	%rd107, %rd22, 3;
	add.s64 	%rd108, %rd1, %rd107;
	ld.global.b64 	%rd314, [%rd108+8];
	bra.uni 	$L__BB17_329;
$L__BB17_81:
	shl.b64 	%rd153, %rd5, 3;
	add.s64 	%rd154, %rd1, %rd153;
	ld.global.b64 	%rd6, [%rd154+8];
	bra.uni 	$L__BB17_88;
$L__BB17_327:
	shl.b64 	%rd111, %rd22, 3;
	add.s64 	%rd112, %rd1, %rd111;
	ld.global.b64 	%rd313, [%rd112+8];
$L__BB17_328:
	setp.lt.s32 	%p68, %r281, 5;
	cvt.rn.f64.s64 	%rd113, %rd313;
	cvt.rn.f64.u64 	%rd114, %rd313;
	selp.f64 	%rd314, %rd113, %rd114, %p68;
$L__BB17_329:
	abs.f64 	%rd117, %rd312;
	setp.ne.f64 	%p73, %rd117, 0d7FF0000000000000;
	abs.f64 	%rd118, %rd314;
	setp.ne.f64 	%p74, %rd118, 0d7FF0000000000000;
	and.pred 	%p75, %p73, %p74;
	@%p75 bra 	$L__BB17_367;
	mov.b32 	%r118, 1;
	atom.global.or.b32 %r117, [%rd39], %r118;
	bra.uni 	$L__BB17_367;
$L__BB17_86:
	shl.b64 	%rd157, %rd5, 3;
	add.s64 	%rd158, %rd1, %rd157;
	ld.global.b64 	%rd301, [%rd158+8];
$L__BB17_87:
	setp.lt.s32 	%p113, %r269, 5;
	cvt.rn.f64.s64 	%rd159, %rd301;
	cvt.rn.f64.u64 	%rd160, %rd301;
	selp.f64 	%rd6, %rd159, %rd160, %p113;
$L__BB17_88:
	setp.gt.s32 	%p118, %r55, 15;
	setp.eq.b32 	%p242, %r55, 14;
	@%p118 bra 	$L__BB17_92;
	mov.b32 	%r272, 12;
	@%p242 bra 	$L__BB17_96;
	setp.eq.b32 	%p121, %r55, 15;
	mov.b32 	%r272, %r55;
	@%p121 bra 	$L__BB17_91;
	bra.uni 	$L__BB17_96;
$L__BB17_91:
	mov.b32 	%r272, 13;
	bra.uni 	$L__BB17_96;
$L__BB17_92:
	setp.eq.b32 	%p119, %r55, 16;
	@%p119 bra 	$L__BB17_95;
	setp.ne.b32 	%p120, %r55, 17;
	mov.b32 	%r272, %r55;
	@%p120 bra 	$L__BB17_96;
	mov.b32 	%r272, 9;
	bra.uni 	$L__BB17_96;
$L__BB17_95:
	mov.b32 	%r272, 10;
$L__BB17_96:
	add.s32 	%r154, %r54, -1;
	setp.gt.u32 	%p122, %r154, 7;
	@%p122 bra 	$L__BB17_132;
	setp.gt.s32 	%p123, %r54, 3;
	@%p123 bra 	$L__BB17_102;
	bra.uni 	$L__BB17_98;
$L__BB17_102:
	setp.gt.s32 	%p124, %r54, 5;
	@%p124 bra 	$L__BB17_106;
	setp.eq.b32 	%p127, %r54, 4;
	@%p127 bra 	$L__BB17_111;
	setp.eq.b32 	%p128, %r54, 5;
	@%p128 bra 	$L__BB17_105;
	bra.uni 	$L__BB17_113;
$L__BB17_105:
	add.s64 	%rd167, %rd1, %rd4;
	ld.global.b8 	%rd302, [%rd167];
	bra.uni 	$L__BB17_114;
$L__BB17_98:
	setp.eq.b32 	%p129, %r54, 1;
	@%p129 bra 	$L__BB17_109;
	setp.eq.b32 	%p130, %r54, 2;
	@%p130 bra 	$L__BB17_110;
	setp.eq.b32 	%p131, %r54, 3;
	@%p131 bra 	$L__BB17_101;
	bra.uni 	$L__BB17_113;
$L__BB17_101:
	shl.b64 	%rd170, %rd4, 1;
	add.s64 	%rd171, %rd1, %rd170;
	ld.global.s16 	%rd302, [%rd171];
	bra.uni 	$L__BB17_114;
$L__BB17_106:
	setp.eq.b32 	%p125, %r54, 6;
	@%p125 bra 	$L__BB17_112;
	setp.eq.b32 	%p126, %r54, 7;
	@%p126 bra 	$L__BB17_108;
	bra.uni 	$L__BB17_113;
$L__BB17_108:
	shl.b64 	%rd163, %rd4, 2;
	add.s64 	%rd164, %rd1, %rd163;
	ld.global.b32 	%rd302, [%rd164];
	bra.uni 	$L__BB17_114;
$L__BB17_109:
	shl.b64 	%rd173, %rd4, 3;
	add.s64 	%rd174, %rd1, %rd173;
	ld.global.b64 	%rd302, [%rd174];
	bra.uni 	$L__BB17_114;
$L__BB17_113:
	shl.b64 	%rd175, %rd4, 3;
	add.s64 	%rd176, %rd1, %rd175;
	ld.global.b64 	%rd302, [%rd176];
	bra.uni 	$L__BB17_114;
$L__BB17_111:
	shl.b64 	%rd168, %rd4, 2;
	add.s64 	%rd169, %rd1, %rd168;
	ld.global.s32 	%rd302, [%rd169];
	bra.uni 	$L__BB17_114;
$L__BB17_112:
	shl.b64 	%rd165, %rd4, 1;
	add.s64 	%rd166, %rd1, %rd165;
	ld.global.b16 	%rd302, [%rd166];
	bra.uni 	$L__BB17_114;
$L__BB17_110:
	add.s64 	%rd172, %rd1, %rd4;
	ld.global.s8 	%rd302, [%rd172];
$L__BB17_114:
	and.b32 	%r155, %r272, -2;
	setp.ne.b32 	%p132, %r155, 12;
	setp.lt.u32 	%p241, %r54, 5;
	@%p132 bra 	$L__BB17_131;
	setp.lt.s64 	%p134, %rd302, 0;
	and.pred 	%p135, %p241, %p134;
	neg.s64 	%rd178, %rd302;
	selp.b64 	%rd7, %rd178, %rd302, %p135;
	selp.b32 	%r273, 32768, 0, %p135;
	setp.eq.b64 	%p136, %rd7, 0;
	@%p136 bra 	$L__BB17_122;
	clz.b64 	%r159, %rd7;
	sub.s32 	%r9, 64, %r159;
	setp.eq.b32 	%p137, %r272, 12;
	selp.b32 	%r10, 11, 8, %p137;
	sub.s32 	%r11, %r9, %r10;
	setp.gt.s32 	%p138, %r11, 0;
	@%p138 bra 	$L__BB17_118;
	bra.uni 	$L__BB17_117;
$L__BB17_118:
	shr.u64 	%rd179, %rd7, %r11;
	mov.b64 	%rd180, -1;
	shl.b64 	%rd181, %rd180, %r11;
	not.b64 	%rd182, %rd181;
	and.b64 	%rd183, %rd7, %rd182;
	add.s32 	%r160, %r11, -1;
	mov.b64 	%rd184, 1;
	shl.b64 	%rd185, %rd184, %r160;
	setp.gt.u64 	%p139, %rd183, %rd185;
	setp.eq.b64 	%p140, %rd183, %rd185;
	and.b64 	%rd186, %rd179, 1;
	setp.ne.b64 	%p141, %rd186, 0;
	and.pred 	%p142, %p140, %p141;
	or.pred 	%p143, %p139, %p142;
	selp.b64 	%rd187, 1, 0, %p143;
	add.s64 	%rd303, %rd179, %rd187;
	bra.uni 	$L__BB17_119;
$L__BB17_131:
	setp.eq.b32 	%p133, %r272, 10;
	cvt.rn.f32.s64 	%r156, %rd302;
	cvt.rn.f32.u64 	%r157, %rd302;
	selp.f32 	%r158, %r156, %r157, %p241;
	cvt.f64.f32 	%rd177, %r158;
	selp.f64 	%rd304, %rd177, %rd304, %p133;
	bra.uni 	$L__BB17_132;
$L__BB17_117:
	neg.s32 	%r161, %r11;
	shl.b64 	%rd303, %rd7, %r161;
$L__BB17_119:
	mov.b64 	%rd188, 1;
	shl.b64 	%rd8, %rd188, %r10;
	setp.ne.b64 	%p144, %rd303, %rd8;
	selp.b32 	%r162, -1, 0, %p144;
	add.s32 	%r12, %r9, %r162;
	selp.b32 	%r13, 15, 127, %p137;
	setp.le.u32 	%p145, %r12, %r13;
	@%p145 bra 	$L__BB17_121;
	selp.b32 	%r169, 31744, 32640, %p137;
	or.b32 	%r273, %r273, %r169;
	bra.uni 	$L__BB17_122;
$L__BB17_121:
	setp.eq.b64 	%p146, %rd303, %rd8;
	selp.b32 	%r163, 1, 0, %p146;
	shr.u64 	%rd189, %rd303, %r163;
	add.s32 	%r164, %r12, %r13;
	add.s32 	%r165, %r10, -1;
	shl.b32 	%r166, %r164, %r165;
	mov.b64 	%rd190, -1;
	shl.b64 	%rd191, %rd190, %r165;
	not.b64 	%rd192, %rd191;
	and.b64 	%rd193, %rd189, %rd192;
	cvt.u32.u64 	%r167, %rd193;
	or.b32 	%r168, %r166, %r167;
	or.b32 	%r273, %r168, %r273;
$L__BB17_122:
	setp.ne.b32 	%p147, %r272, 13;
	and.b32 	%r14, %r273, 65535;
	@%p147 bra 	$L__BB17_124;
	shl.b32 	%r274, %r14, 16;
	bra.uni 	$L__BB17_130;
$L__BB17_124:
	shl.b32 	%r170, %r273, 16;
	and.b32 	%r274, %r170, -2147483648;
	bfe.u32 	%r15, %r273, 10, 5;
	setp.eq.b32 	%p148, %r15, 31;
	@%p148 bra 	$L__BB17_128;
	and.b32 	%r16, %r273, 1023;
	setp.ne.b32 	%p149, %r15, 0;
	@%p149 bra 	$L__BB17_129;
	setp.eq.b32 	%p150, %r16, 0;
	@%p150 bra 	$L__BB17_130;
	clz.b32 	%r173, %r16;
	xor.b32 	%r174, %r173, 31;
	sub.s32 	%r175, 9, %r174;
	shl.b32 	%r176, %r273, %r175;
	shl.b32 	%r177, %r174, 23;
	shl.b32 	%r178, %r176, 14;
	and.b32 	%r179, %r178, 8372224;
	add.s32 	%r180, %r177, %r274;
	add.s32 	%r181, %r180, %r179;
	add.s32 	%r274, %r181, 864026624;
	bra.uni 	$L__BB17_130;
$L__BB17_128:
	shl.b32 	%r171, %r14, 13;
	or.b32 	%r172, %r274, %r171;
	or.b32 	%r274, %r172, 2139095040;
	bra.uni 	$L__BB17_130;
$L__BB17_129:
	shl.b32 	%r182, %r15, 23;
	shl.b32 	%r183, %r16, 13;
	or.b32 	%r184, %r182, %r183;
	add.s32 	%r185, %r184, %r274;
	add.s32 	%r274, %r185, 939524096;
$L__BB17_130:
	cvt.f64.f32 	%rd304, %r274;
$L__BB17_132:
	add.s32 	%r17, %r55, -14;
	setp.lt.u32 	%p151, %r17, 4;
	or.pred 	%p152, %p151, %p100;
	@%p152 bra 	$L__BB17_134;
	bra.uni 	$L__BB17_133;
$L__BB17_134:
	@%p118 bra 	$L__BB17_138;
	mov.b32 	%r275, 12;
	@%p242 bra 	$L__BB17_142;
	setp.eq.b32 	%p155, %r55, 15;
	mov.b32 	%r275, %r55;
	@%p155 bra 	$L__BB17_137;
	bra.uni 	$L__BB17_142;
$L__BB17_137:
	mov.b32 	%r275, 13;
	bra.uni 	$L__BB17_142;
$L__BB17_133:
	mov.b32 	%r187, 1;
	atom.global.or.b32 %r186, [%rd39], %r187;
	bra.uni 	$L__BB17_367;
$L__BB17_138:
	setp.eq.b32 	%p153, %r55, 16;
	@%p153 bra 	$L__BB17_141;
	setp.ne.b32 	%p154, %r55, 17;
	mov.b32 	%r275, %r55;
	@%p154 bra 	$L__BB17_142;
	mov.b32 	%r275, 9;
	bra.uni 	$L__BB17_142;
$L__BB17_141:
	mov.b32 	%r275, 10;
$L__BB17_142:
	selp.b32 	%r188, 1, 0, %p151;
	shl.b64 	%rd9, %rd4, %r188;
	and.b32 	%r18, %r275, -2;
	setp.ne.b32 	%p156, %r18, 12;
	@%p156 bra 	$L__BB17_157;
	shr.u64 	%rd11, %rd304, 48;
	cvt.u32.u64 	%r190, %rd11;
	and.b32 	%r19, %r190, 32768;
	shr.u64 	%rd198, %rd304, 52;
	cvt.u32.u64 	%r191, %rd198;
	and.b32 	%r20, %r191, 2047;
	setp.eq.b32 	%p159, %r20, 0;
	@%p159 bra 	$L__BB17_146;
	and.b64 	%rd10, %rd304, 4503599627370495;
	setp.eq.b32 	%p158, %r275, 12;
	selp.b32 	%r21, 11, 8, %p158;
	selp.b32 	%r276, 31744, 32640, %p158;
	setp.ne.b32 	%p160, %r20, 2047;
	@%p160 bra 	$L__BB17_147;
	setp.eq.b64 	%p161, %rd10, 0;
	add.s32 	%r192, %r21, -2;
	mov.b32 	%r193, 1;
	shl.b32 	%r194, %r193, %r192;
	selp.b32 	%r195, 0, %r194, %p161;
	or.b32 	%r196, %r19, %r195;
	or.b32 	%r197, %r196, %r276;
	cvt.u16.u32 	%rs12, %r197;
	bra.uni 	$L__BB17_156;
$L__BB17_157:
	setp.ne.b32 	%p157, %r275, 10;
	@%p157 bra 	$L__BB17_159;
	cvt.rn.f32.f64 	%r189, %rd304;
	shl.b64 	%rd196, %rd9, 2;
	add.s64 	%rd197, %rd2, %rd196;
	st.global.b32 	[%rd197], %r189;
	bra.uni 	$L__BB17_160;
$L__BB17_159:
	shl.b64 	%rd194, %rd9, 3;
	add.s64 	%rd195, %rd2, %rd194;
	st.global.b64 	[%rd195], %rd304;
	bra.uni 	$L__BB17_160;
$L__BB17_146:
	cvt.u16.u32 	%rs12, %r19;
	bra.uni 	$L__BB17_156;
$L__BB17_147:
	selp.b32 	%r198, -14, -126, %p158;
	add.s32 	%r23, %r20, -1023;
	or.b64 	%rd12, %rd10, 4503599627370496;
	setp.ge.s32 	%p162, %r23, %r198;
	@%p162 bra 	$L__BB17_153;
	and.b64 	%rd13, %rd11, 32768;
	selp.b32 	%r208, 28, -81, %p158;
	sub.s32 	%r24, %r208, %r23;
	setp.gt.s32 	%p170, %r24, 0;
	@%p170 bra 	$L__BB17_150;
	bra.uni 	$L__BB17_149;
$L__BB17_150:
	setp.gt.u32 	%p171, %r24, 63;
	mov.b64 	%rd305, 0;
	@%p171 bra 	$L__BB17_152;
	shr.u64 	%rd212, %rd12, %r24;
	mov.b64 	%rd213, -1;
	shl.b64 	%rd214, %rd213, %r24;
	not.b64 	%rd215, %rd214;
	and.b64 	%rd216, %rd12, %rd215;
	add.s32 	%r209, %r24, -1;
	mov.b64 	%rd217, 1;
	shl.b64 	%rd218, %rd217, %r209;
	setp.gt.u64 	%p172, %rd216, %rd218;
	setp.eq.b64 	%p173, %rd216, %rd218;
	and.b64 	%rd219, %rd212, 1;
	setp.ne.b64 	%p174, %rd219, 0;
	and.pred 	%p175, %p173, %p174;
	or.pred 	%p176, %p172, %p175;
	selp.b64 	%rd220, 1, 0, %p176;
	add.s64 	%rd305, %rd212, %rd220;
	bra.uni 	$L__BB17_152;
$L__BB17_153:
	selp.b32 	%r22, 15, 127, %p158;
	sub.s32 	%r199, 53, %r21;
	shr.u64 	%rd199, %rd12, %r199;
	mov.b64 	%rd200, -1;
	shl.b64 	%rd201, %rd200, %r199;
	not.b64 	%rd202, %rd201;
	and.b64 	%rd203, %rd202, %rd304;
	sub.s32 	%r200, 52, %r21;
	mov.b64 	%rd204, 1;
	shl.b64 	%rd205, %rd204, %r200;
	setp.gt.u64 	%p163, %rd203, %rd205;
	setp.eq.b64 	%p164, %rd203, %rd205;
	and.b64 	%rd206, %rd199, 1;
	setp.ne.b64 	%p165, %rd206, 0;
	and.pred 	%p166, %p164, %p165;
	or.pred 	%p167, %p163, %p166;
	selp.b64 	%rd207, 1, 0, %p167;
	add.s64 	%rd14, %rd199, %rd207;
	shl.b64 	%rd15, %rd204, %r21;
	setp.eq.b64 	%p168, %rd14, %rd15;
	add.s32 	%r201, %r20, -1022;
	selp.b32 	%r25, %r201, %r23, %p168;
	setp.gt.s32 	%p169, %r25, %r22;
	@%p169 bra 	$L__BB17_155;
	selp.b32 	%r202, 1, 0, %p168;
	shr.u64 	%rd208, %rd14, %r202;
	add.s32 	%r203, %r25, %r22;
	add.s32 	%r204, %r21, -1;
	shl.b32 	%r205, %r203, %r204;
	shl.b64 	%rd209, %rd200, %r204;
	not.b64 	%rd210, %rd209;
	and.b64 	%rd211, %rd208, %rd210;
	cvt.u32.u64 	%r206, %rd211;
	or.b32 	%r276, %r205, %r206;
$L__BB17_155:
	or.b32 	%r207, %r276, %r19;
	cvt.u16.u32 	%rs12, %r207;
	bra.uni 	$L__BB17_156;
$L__BB17_149:
	neg.s32 	%r210, %r24;
	shl.b64 	%rd305, %rd12, %r210;
$L__BB17_152:
	or.b64 	%rd221, %rd305, %rd13;
	cvt.u16.u64 	%rs12, %rd221;
$L__BB17_156:
	shl.b64 	%rd222, %rd9, 1;
	add.s64 	%rd223, %rd2, %rd222;
	st.global.b16 	[%rd223], %rs12;
$L__BB17_160:
	setp.gt.u32 	%p177, %r17, 3;
	@%p177 bra 	$L__BB17_179;
	@%p156 bra 	$L__BB17_176;
	shr.u64 	%rd17, %rd6, 48;
	cvt.u32.u64 	%r212, %rd17;
	and.b32 	%r26, %r212, 32768;
	shr.u64 	%rd228, %rd6, 52;
	cvt.u32.u64 	%r213, %rd228;
	and.b32 	%r27, %r213, 2047;
	setp.eq.b32 	%p180, %r27, 0;
	@%p180 bra 	$L__BB17_165;
	and.b64 	%rd16, %rd6, 4503599627370495;
	setp.eq.b32 	%p179, %r275, 12;
)QPTX";
        result += R"QPTX(
	selp.b32 	%r28, 11, 8, %p179;
	selp.b32 	%r277, 31744, 32640, %p179;
	setp.ne.b32 	%p181, %r27, 2047;
	@%p181 bra 	$L__BB17_166;
	setp.eq.b64 	%p182, %rd16, 0;
	add.s32 	%r214, %r28, -2;
	mov.b32 	%r215, 1;
	shl.b32 	%r216, %r215, %r214;
	selp.b32 	%r217, 0, %r216, %p182;
	or.b32 	%r218, %r26, %r217;
	or.b32 	%r219, %r218, %r277;
	cvt.u16.u32 	%rs13, %r219;
	bra.uni 	$L__BB17_175;
$L__BB17_176:
	setp.ne.b32 	%p178, %r275, 10;
	@%p178 bra 	$L__BB17_178;
	cvt.rn.f32.f64 	%r211, %rd6;
	shl.b64 	%rd226, %rd9, 2;
	add.s64 	%rd227, %rd2, %rd226;
	st.global.b32 	[%rd227+4], %r211;
	bra.uni 	$L__BB17_179;
$L__BB17_178:
	shl.b64 	%rd224, %rd9, 3;
	add.s64 	%rd225, %rd2, %rd224;
	st.global.b64 	[%rd225+8], %rd6;
	bra.uni 	$L__BB17_179;
$L__BB17_165:
	cvt.u16.u32 	%rs13, %r26;
	bra.uni 	$L__BB17_175;
$L__BB17_166:
	selp.b32 	%r220, -14, -126, %p179;
	add.s32 	%r30, %r27, -1023;
	or.b64 	%rd18, %rd16, 4503599627370496;
	setp.ge.s32 	%p183, %r30, %r220;
	@%p183 bra 	$L__BB17_172;
	and.b64 	%rd19, %rd17, 32768;
	selp.b32 	%r230, 28, -81, %p179;
	sub.s32 	%r31, %r230, %r30;
	setp.gt.s32 	%p191, %r31, 0;
	@%p191 bra 	$L__BB17_169;
	bra.uni 	$L__BB17_168;
$L__BB17_169:
	setp.gt.u32 	%p192, %r31, 63;
	mov.b64 	%rd306, 0;
	@%p192 bra 	$L__BB17_171;
	shr.u64 	%rd242, %rd18, %r31;
	mov.b64 	%rd243, -1;
	shl.b64 	%rd244, %rd243, %r31;
	not.b64 	%rd245, %rd244;
	and.b64 	%rd246, %rd18, %rd245;
	add.s32 	%r231, %r31, -1;
	mov.b64 	%rd247, 1;
	shl.b64 	%rd248, %rd247, %r231;
	setp.gt.u64 	%p193, %rd246, %rd248;
	setp.eq.b64 	%p194, %rd246, %rd248;
	and.b64 	%rd249, %rd242, 1;
	setp.ne.b64 	%p195, %rd249, 0;
	and.pred 	%p196, %p194, %p195;
	or.pred 	%p197, %p193, %p196;
	selp.b64 	%rd250, 1, 0, %p197;
	add.s64 	%rd306, %rd242, %rd250;
	bra.uni 	$L__BB17_171;
$L__BB17_172:
	selp.b32 	%r29, 15, 127, %p179;
	sub.s32 	%r221, 53, %r28;
	shr.u64 	%rd229, %rd18, %r221;
	mov.b64 	%rd230, -1;
	shl.b64 	%rd231, %rd230, %r221;
	not.b64 	%rd232, %rd231;
	and.b64 	%rd233, %rd232, %rd6;
	sub.s32 	%r222, 52, %r28;
	mov.b64 	%rd234, 1;
	shl.b64 	%rd235, %rd234, %r222;
	setp.gt.u64 	%p184, %rd233, %rd235;
	setp.eq.b64 	%p185, %rd233, %rd235;
	and.b64 	%rd236, %rd229, 1;
	setp.ne.b64 	%p186, %rd236, 0;
	and.pred 	%p187, %p185, %p186;
	or.pred 	%p188, %p184, %p187;
	selp.b64 	%rd237, 1, 0, %p188;
	add.s64 	%rd20, %rd229, %rd237;
	shl.b64 	%rd21, %rd234, %r28;
	setp.eq.b64 	%p189, %rd20, %rd21;
	add.s32 	%r223, %r27, -1022;
	selp.b32 	%r32, %r223, %r30, %p189;
	setp.gt.s32 	%p190, %r32, %r29;
	@%p190 bra 	$L__BB17_174;
	selp.b32 	%r224, 1, 0, %p189;
	shr.u64 	%rd238, %rd20, %r224;
	add.s32 	%r225, %r32, %r29;
	add.s32 	%r226, %r28, -1;
	shl.b32 	%r227, %r225, %r226;
	shl.b64 	%rd239, %rd230, %r226;
	not.b64 	%rd240, %rd239;
	and.b64 	%rd241, %rd238, %rd240;
	cvt.u32.u64 	%r228, %rd241;
	or.b32 	%r277, %r227, %r228;
$L__BB17_174:
	or.b32 	%r229, %r277, %r26;
	cvt.u16.u32 	%rs13, %r229;
	bra.uni 	$L__BB17_175;
$L__BB17_355:
	mov.b32 	%r285, 16;
	mov.pred 	%p243, %p7;
	bra.uni 	$L__BB17_357;
$L__BB17_168:
	neg.s32 	%r232, %r31;
	shl.b64 	%rd306, %rd18, %r232;
$L__BB17_171:
	or.b64 	%rd251, %rd306, %rd19;
	cvt.u16.u64 	%rs13, %rd251;
$L__BB17_175:
	shl.b64 	%rd252, %rd9, 1;
	add.s64 	%rd253, %rd2, %rd252;
	st.global.b16 	[%rd253+2], %rs13;
$L__BB17_179:
	@%p118 bra 	$L__BB17_183;
	mov.b32 	%r278, 12;
	@%p242 bra 	$L__BB17_187;
	setp.eq.b32 	%p200, %r55, 15;
	mov.b32 	%r278, %r55;
	@%p200 bra 	$L__BB17_182;
	bra.uni 	$L__BB17_187;
$L__BB17_182:
	mov.b32 	%r278, 13;
	bra.uni 	$L__BB17_187;
$L__BB17_183:
	setp.eq.b32 	%p198, %r55, 16;
	@%p198 bra 	$L__BB17_186;
	setp.ne.b32 	%p199, %r55, 17;
	mov.b32 	%r278, %r55;
	@%p199 bra 	$L__BB17_187;
	mov.b32 	%r278, 9;
	bra.uni 	$L__BB17_187;
$L__BB17_186:
	mov.b32 	%r278, 10;
$L__BB17_187:
	and.b32 	%r33, %r278, -2;
	setp.ne.b32 	%p201, %r33, 12;
	@%p201 bra 	$L__BB17_197;
	shl.b64 	%rd274, %rd9, 1;
	add.s64 	%rd275, %rd2, %rd274;
	ld.global.b16 	%rs3, [%rd275];
	setp.ne.b32 	%p215, %r278, 13;
	cvt.u32.u16 	%r34, %rs3;
	@%p215 bra 	$L__BB17_190;
	shl.b32 	%r279, %r34, 16;
	bra.uni 	$L__BB17_196;
$L__BB17_197:
	setp.gt.s32 	%p202, %r278, 4;
	@%p202 bra 	$L__BB17_205;
	bra.uni 	$L__BB17_198;
$L__BB17_205:
	setp.gt.s32 	%p203, %r278, 6;
	@%p203 bra 	$L__BB17_209;
	bra.uni 	$L__BB17_206;
$L__BB17_209:
	setp.eq.b32 	%p204, %r278, 7;
	@%p204 bra 	$L__BB17_217;
	setp.eq.b32 	%p205, %r278, 9;
	@%p205 bra 	$L__BB17_213;
	setp.ne.b32 	%p206, %r278, 10;
	@%p206 bra 	$L__BB17_218;
	shl.b64 	%rd268, %rd9, 2;
	add.s64 	%rd269, %rd2, %rd268;
	ld.global.b32 	%r233, [%rd269];
	cvt.f64.f32 	%rd308, %r233;
	bra.uni 	$L__BB17_220;
$L__BB17_190:
	cvt.s32.s16 	%r234, %rs3;
	and.b32 	%r279, %r234, -2147483648;
	bfe.u32 	%r35, %r34, 10, 5;
	setp.eq.b32 	%p216, %r35, 31;
	@%p216 bra 	$L__BB17_194;
	and.b32 	%r36, %r34, 1023;
	setp.ne.b32 	%p217, %r35, 0;
	@%p217 bra 	$L__BB17_195;
	setp.eq.b32 	%p218, %r36, 0;
	@%p218 bra 	$L__BB17_196;
	clz.b32 	%r237, %r36;
	xor.b32 	%r238, %r237, 31;
	sub.s32 	%r239, 9, %r238;
	shl.b32 	%r240, %r34, %r239;
	shl.b32 	%r241, %r238, 23;
	shl.b32 	%r242, %r240, 14;
	and.b32 	%r243, %r242, 8372224;
	add.s32 	%r244, %r241, %r279;
	add.s32 	%r245, %r244, %r243;
	add.s32 	%r279, %r245, 864026624;
	bra.uni 	$L__BB17_196;
$L__BB17_198:
	setp.gt.s32 	%p209, %r278, 2;
	@%p209 bra 	$L__BB17_202;
	setp.eq.b32 	%p212, %r278, 1;
	@%p212 bra 	$L__BB17_214;
	setp.eq.b32 	%p213, %r278, 2;
	@%p213 bra 	$L__BB17_201;
	bra.uni 	$L__BB17_218;
$L__BB17_201:
	add.s64 	%rd263, %rd2, %rd9;
	ld.global.s8 	%rd307, [%rd263];
	bra.uni 	$L__BB17_219;
$L__BB17_202:
	setp.eq.b32 	%p210, %r278, 3;
	@%p210 bra 	$L__BB17_215;
	setp.eq.b32 	%p211, %r278, 4;
	@%p211 bra 	$L__BB17_204;
	bra.uni 	$L__BB17_218;
$L__BB17_204:
	shl.b64 	%rd259, %rd9, 2;
	add.s64 	%rd260, %rd2, %rd259;
	ld.global.s32 	%rd307, [%rd260];
	bra.uni 	$L__BB17_219;
$L__BB17_206:
	setp.eq.b32 	%p207, %r278, 5;
	@%p207 bra 	$L__BB17_216;
	setp.eq.b32 	%p208, %r278, 6;
	@%p208 bra 	$L__BB17_208;
	bra.uni 	$L__BB17_218;
$L__BB17_208:
	shl.b64 	%rd256, %rd9, 1;
	add.s64 	%rd257, %rd2, %rd256;
	ld.global.b16 	%rd307, [%rd257];
	bra.uni 	$L__BB17_219;
$L__BB17_194:
	shl.b32 	%r235, %r34, 13;
	or.b32 	%r236, %r279, %r235;
	or.b32 	%r279, %r236, 2139095040;
	bra.uni 	$L__BB17_196;
$L__BB17_195:
	shl.b32 	%r246, %r35, 23;
	shl.b32 	%r247, %r36, 13;
	or.b32 	%r248, %r246, %r247;
	add.s32 	%r249, %r248, %r279;
	add.s32 	%r279, %r249, 939524096;
$L__BB17_196:
	cvt.f64.f32 	%rd308, %r279;
	bra.uni 	$L__BB17_220;
$L__BB17_214:
	shl.b64 	%rd264, %rd9, 3;
	add.s64 	%rd265, %rd2, %rd264;
	ld.global.b64 	%rd307, [%rd265];
	bra.uni 	$L__BB17_219;
$L__BB17_215:
	shl.b64 	%rd261, %rd9, 1;
	add.s64 	%rd262, %rd2, %rd261;
	ld.global.s16 	%rd307, [%rd262];
	bra.uni 	$L__BB17_219;
$L__BB17_217:
	shl.b64 	%rd254, %rd9, 2;
	add.s64 	%rd255, %rd2, %rd254;
	ld.global.b32 	%rd307, [%rd255];
	bra.uni 	$L__BB17_219;
$L__BB17_216:
	add.s64 	%rd258, %rd2, %rd9;
	ld.global.b8 	%rd307, [%rd258];
	bra.uni 	$L__BB17_219;
$L__BB17_213:
	shl.b64 	%rd266, %rd9, 3;
	add.s64 	%rd267, %rd2, %rd266;
	ld.global.b64 	%rd308, [%rd267];
	bra.uni 	$L__BB17_220;
$L__BB17_218:
	shl.b64 	%rd270, %rd9, 3;
	add.s64 	%rd271, %rd2, %rd270;
	ld.global.b64 	%rd307, [%rd271];
$L__BB17_219:
	setp.lt.s32 	%p214, %r278, 5;
	cvt.rn.f64.s64 	%rd272, %rd307;
	cvt.rn.f64.u64 	%rd273, %rd307;
	selp.f64 	%rd308, %rd272, %rd273, %p214;
$L__BB17_220:
	mov.b64 	%rd310, 0d0000000000000000;
	@%p177 bra 	$L__BB17_254;
	@%p201 bra 	$L__BB17_231;
	shl.b64 	%rd296, %rd9, 1;
	add.s64 	%rd297, %rd2, %rd296;
	ld.global.b16 	%rs4, [%rd297+2];
	setp.ne.b32 	%p232, %r278, 13;
	cvt.u32.u16 	%r37, %rs4;
	@%p232 bra 	$L__BB17_224;
	shl.b32 	%r280, %r37, 16;
	bra.uni 	$L__BB17_230;
$L__BB17_231:
	setp.gt.s32 	%p219, %r278, 4;
	@%p219 bra 	$L__BB17_239;
	bra.uni 	$L__BB17_232;
$L__BB17_239:
	setp.gt.s32 	%p220, %r278, 6;
	@%p220 bra 	$L__BB17_243;
	bra.uni 	$L__BB17_240;
$L__BB17_243:
	setp.eq.b32 	%p221, %r278, 7;
	@%p221 bra 	$L__BB17_251;
	setp.eq.b32 	%p222, %r278, 9;
	@%p222 bra 	$L__BB17_247;
	setp.ne.b32 	%p223, %r278, 10;
	@%p223 bra 	$L__BB17_252;
	shl.b64 	%rd290, %rd9, 2;
	add.s64 	%rd291, %rd2, %rd290;
	ld.global.b32 	%r250, [%rd291+4];
	cvt.f64.f32 	%rd310, %r250;
	bra.uni 	$L__BB17_254;
$L__BB17_224:
	cvt.s32.s16 	%r251, %rs4;
	and.b32 	%r280, %r251, -2147483648;
	bfe.u32 	%r38, %r37, 10, 5;
	setp.eq.b32 	%p233, %r38, 31;
	@%p233 bra 	$L__BB17_228;
	and.b32 	%r39, %r37, 1023;
	setp.ne.b32 	%p234, %r38, 0;
	@%p234 bra 	$L__BB17_229;
	setp.eq.b32 	%p235, %r39, 0;
	@%p235 bra 	$L__BB17_230;
	clz.b32 	%r254, %r39;
	xor.b32 	%r255, %r254, 31;
	sub.s32 	%r256, 9, %r255;
	shl.b32 	%r257, %r37, %r256;
	shl.b32 	%r258, %r255, 23;
	shl.b32 	%r259, %r257, 14;
	and.b32 	%r260, %r259, 8372224;
	add.s32 	%r261, %r258, %r280;
	add.s32 	%r262, %r261, %r260;
	add.s32 	%r280, %r262, 864026624;
	bra.uni 	$L__BB17_230;
$L__BB17_232:
	setp.gt.s32 	%p226, %r278, 2;
	@%p226 bra 	$L__BB17_236;
	setp.eq.b32 	%p229, %r278, 1;
	@%p229 bra 	$L__BB17_248;
	setp.eq.b32 	%p230, %r278, 2;
	@%p230 bra 	$L__BB17_235;
	bra.uni 	$L__BB17_252;
$L__BB17_235:
	add.s64 	%rd285, %rd2, %rd9;
	ld.global.s8 	%rd309, [%rd285+1];
	bra.uni 	$L__BB17_253;
$L__BB17_236:
	setp.eq.b32 	%p227, %r278, 3;
	@%p227 bra 	$L__BB17_249;
	setp.eq.b32 	%p228, %r278, 4;
	@%p228 bra 	$L__BB17_238;
	bra.uni 	$L__BB17_252;
$L__BB17_238:
	shl.b64 	%rd281, %rd9, 2;
	add.s64 	%rd282, %rd2, %rd281;
	ld.global.s32 	%rd309, [%rd282+4];
	bra.uni 	$L__BB17_253;
$L__BB17_240:
	setp.eq.b32 	%p224, %r278, 5;
	@%p224 bra 	$L__BB17_250;
	setp.eq.b32 	%p225, %r278, 6;
	@%p225 bra 	$L__BB17_242;
	bra.uni 	$L__BB17_252;
$L__BB17_242:
	shl.b64 	%rd278, %rd9, 1;
	add.s64 	%rd279, %rd2, %rd278;
	ld.global.b16 	%rd309, [%rd279+2];
	bra.uni 	$L__BB17_253;
$L__BB17_228:
	shl.b32 	%r252, %r37, 13;
	or.b32 	%r253, %r280, %r252;
	or.b32 	%r280, %r253, 2139095040;
	bra.uni 	$L__BB17_230;
$L__BB17_229:
	shl.b32 	%r263, %r38, 23;
	shl.b32 	%r264, %r39, 13;
	or.b32 	%r265, %r263, %r264;
	add.s32 	%r266, %r265, %r280;
	add.s32 	%r280, %r266, 939524096;
$L__BB17_230:
	cvt.f64.f32 	%rd310, %r280;
	bra.uni 	$L__BB17_254;
$L__BB17_248:
	shl.b64 	%rd286, %rd9, 3;
	add.s64 	%rd287, %rd2, %rd286;
	ld.global.b64 	%rd309, [%rd287+8];
	bra.uni 	$L__BB17_253;
$L__BB17_249:
	shl.b64 	%rd283, %rd9, 1;
	add.s64 	%rd284, %rd2, %rd283;
	ld.global.s16 	%rd309, [%rd284+2];
	bra.uni 	$L__BB17_253;
$L__BB17_251:
	shl.b64 	%rd276, %rd9, 2;
	add.s64 	%rd277, %rd2, %rd276;
	ld.global.b32 	%rd309, [%rd277+4];
	bra.uni 	$L__BB17_253;
$L__BB17_250:
	add.s64 	%rd280, %rd2, %rd9;
	ld.global.b8 	%rd309, [%rd280+1];
	bra.uni 	$L__BB17_253;
$L__BB17_247:
	shl.b64 	%rd288, %rd9, 3;
	add.s64 	%rd289, %rd2, %rd288;
	ld.global.b64 	%rd310, [%rd289+8];
	bra.uni 	$L__BB17_254;
$L__BB17_252:
	shl.b64 	%rd292, %rd9, 3;
	add.s64 	%rd293, %rd2, %rd292;
	ld.global.b64 	%rd309, [%rd293+8];
$L__BB17_253:
	setp.lt.s32 	%p231, %r278, 5;
	cvt.rn.f64.s64 	%rd294, %rd309;
	cvt.rn.f64.u64 	%rd295, %rd309;
	selp.f64 	%rd310, %rd294, %rd295, %p231;
$L__BB17_254:
	abs.f64 	%rd298, %rd308;
	setp.ne.f64 	%p236, %rd298, 0d7FF0000000000000;
	abs.f64 	%rd299, %rd310;
	setp.ne.f64 	%p237, %rd299, 0d7FF0000000000000;
	and.pred 	%p238, %p236, %p237;
	@%p238 bra 	$L__BB17_367;
	mov.b32 	%r268, 1;
	atom.global.or.b32 %r267, [%rd39], %r268;
$L__BB17_367:
	ret;
}
.weak .func  (.param .align 8 .b8 func_retval0[16]) _Z6q_readIdE5QPairIT_EPKvyi(
	.param .b64 _Z6q_readIdE5QPairIT_EPKvyi_param_0,
	.param .b64 _Z6q_readIdE5QPairIT_EPKvyi_param_1,
	.param .b32 _Z6q_readIdE5QPairIT_EPKvyi_param_2
)
{
	.reg .pred 	%p<43>;
	.reg .b16 	%rs<3>;
	.reg .b32 	%r<48>;
	.reg .b64 	%rd<52>;
	ld.param.b32 	%r9, [_Z6q_readIdE5QPairIT_EPKvyi_param_2];
	ld.param.b64 	%rd3, [_Z6q_readIdE5QPairIT_EPKvyi_param_1];
	setp.gt.s32 	%p1, %r9, 15;
	@%p1 bra 	$L__BB18_4;
	mov.b32 	%r45, 12;
	setp.eq.b32 	%p4, %r9, 14;
	@%p4 bra 	$L__BB18_8;
	setp.eq.b32 	%p5, %r9, 15;
	mov.b32 	%r45, %r9;
	@%p5 bra 	$L__BB18_3;
	bra.uni 	$L__BB18_8;
$L__BB18_3:
	mov.b32 	%r45, 13;
	bra.uni 	$L__BB18_8;
$L__BB18_4:
	setp.eq.b32 	%p2, %r9, 16;
	@%p2 bra 	$L__BB18_7;
	setp.ne.b32 	%p3, %r9, 17;
	mov.b32 	%r45, %r9;
	@%p3 bra 	$L__BB18_8;
	mov.b32 	%r45, 9;
	bra.uni 	$L__BB18_8;
$L__BB18_7:
	mov.b32 	%r45, 10;
$L__BB18_8:
	ld.param.b64 	%rd2, [_Z6q_readIdE5QPairIT_EPKvyi_param_0];
	add.s32 	%r1, %r9, -14;
	setp.lt.u32 	%p6, %r1, 4;
	selp.b32 	%r10, 1, 0, %p6;
	shl.b64 	%rd1, %rd3, %r10;
	and.b32 	%r2, %r45, -2;
	setp.ne.b32 	%p7, %r2, 12;
	@%p7 bra 	$L__BB18_18;
	shl.b64 	%rd24, %rd1, 1;
	add.s64 	%rd25, %rd2, %rd24;
	ld.b16 	%rs1, [%rd25];
	setp.ne.b32 	%p21, %r45, 13;
	cvt.u32.u16 	%r3, %rs1;
	@%p21 bra 	$L__BB18_11;
	shl.b32 	%r46, %r3, 16;
	bra.uni 	$L__BB18_17;
$L__BB18_18:
	setp.gt.s32 	%p8, %r45, 4;
	@%p8 bra 	$L__BB18_26;
	bra.uni 	$L__BB18_19;
$L__BB18_26:
	setp.gt.s32 	%p9, %r45, 6;
	@%p9 bra 	$L__BB18_30;
	bra.uni 	$L__BB18_27;
$L__BB18_30:
	setp.eq.b32 	%p10, %r45, 7;
	@%p10 bra 	$L__BB18_38;
	setp.eq.b32 	%p11, %r45, 9;
	@%p11 bra 	$L__BB18_34;
	setp.ne.b32 	%p12, %r45, 10;
	@%p12 bra 	$L__BB18_39;
	shl.b64 	%rd18, %rd1, 2;
	add.s64 	%rd19, %rd2, %rd18;
	ld.b32 	%r11, [%rd19];
	cvt.f64.f32 	%rd49, %r11;
	bra.uni 	$L__BB18_41;
$L__BB18_11:
	cvt.s32.s16 	%r12, %rs1;
	and.b32 	%r46, %r12, -2147483648;
	bfe.u32 	%r4, %r3, 10, 5;
	setp.eq.b32 	%p22, %r4, 31;
	@%p22 bra 	$L__BB18_15;
	and.b32 	%r5, %r3, 1023;
	setp.ne.b32 	%p23, %r4, 0;
	@%p23 bra 	$L__BB18_16;
	setp.eq.b32 	%p24, %r5, 0;
	@%p24 bra 	$L__BB18_17;
	clz.b32 	%r15, %r5;
	xor.b32 	%r16, %r15, 31;
	sub.s32 	%r17, 9, %r16;
	shl.b32 	%r18, %r3, %r17;
	shl.b32 	%r19, %r16, 23;
	shl.b32 	%r20, %r18, 14;
	and.b32 	%r21, %r20, 8372224;
	add.s32 	%r22, %r19, %r46;
	add.s32 	%r23, %r22, %r21;
	add.s32 	%r46, %r23, 864026624;
	bra.uni 	$L__BB18_17;
$L__BB18_19:
	setp.gt.s32 	%p15, %r45, 2;
	@%p15 bra 	$L__BB18_23;
	setp.eq.b32 	%p18, %r45, 1;
	@%p18 bra 	$L__BB18_35;
	setp.eq.b32 	%p19, %r45, 2;
	@%p19 bra 	$L__BB18_22;
	bra.uni 	$L__BB18_39;
$L__BB18_22:
	add.s64 	%rd13, %rd2, %rd1;
	ld.s8 	%rd48, [%rd13];
	bra.uni 	$L__BB18_40;
$L__BB18_23:
	setp.eq.b32 	%p16, %r45, 3;
	@%p16 bra 	$L__BB18_36;
	setp.eq.b32 	%p17, %r45, 4;
	@%p17 bra 	$L__BB18_25;
	bra.uni 	$L__BB18_39;
$L__BB18_25:
	shl.b64 	%rd9, %rd1, 2;
	add.s64 	%rd10, %rd2, %rd9;
	ld.s32 	%rd48, [%rd10];
	bra.uni 	$L__BB18_40;
$L__BB18_27:
	setp.eq.b32 	%p13, %r45, 5;
	@%p13 bra 	$L__BB18_37;
	setp.eq.b32 	%p14, %r45, 6;
	@%p14 bra 	$L__BB18_29;
	bra.uni 	$L__BB18_39;
$L__BB18_29:
	shl.b64 	%rd6, %rd1, 1;
	add.s64 	%rd7, %rd2, %rd6;
	ld.b16 	%rd48, [%rd7];
	bra.uni 	$L__BB18_40;
$L__BB18_15:
	shl.b32 	%r13, %r3, 13;
	or.b32 	%r14, %r46, %r13;
	or.b32 	%r46, %r14, 2139095040;
	bra.uni 	$L__BB18_17;
$L__BB18_16:
	shl.b32 	%r24, %r4, 23;
	shl.b32 	%r25, %r5, 13;
	or.b32 	%r26, %r24, %r25;
	add.s32 	%r27, %r26, %r46;
	add.s32 	%r46, %r27, 939524096;
$L__BB18_17:
	cvt.f64.f32 	%rd49, %r46;
	bra.uni 	$L__BB18_41;
$L__BB18_35:
	shl.b64 	%rd14, %rd1, 3;
	add.s64 	%rd15, %rd2, %rd14;
	ld.b64 	%rd48, [%rd15];
	bra.uni 	$L__BB18_40;
$L__BB18_36:
	shl.b64 	%rd11, %rd1, 1;
	add.s64 	%rd12, %rd2, %rd11;
	ld.s16 	%rd48, [%rd12];
	bra.uni 	$L__BB18_40;
$L__BB18_38:
	shl.b64 	%rd4, %rd1, 2;
	add.s64 	%rd5, %rd2, %rd4;
	ld.b32 	%rd48, [%rd5];
	bra.uni 	$L__BB18_40;
$L__BB18_37:
	add.s64 	%rd8, %rd2, %rd1;
	ld.b8 	%rd48, [%rd8];
	bra.uni 	$L__BB18_40;
$L__BB18_34:
	shl.b64 	%rd16, %rd1, 3;
	add.s64 	%rd17, %rd2, %rd16;
	ld.b64 	%rd49, [%rd17];
	bra.uni 	$L__BB18_41;
$L__BB18_39:
	shl.b64 	%rd20, %rd1, 3;
	add.s64 	%rd21, %rd2, %rd20;
	ld.b64 	%rd48, [%rd21];
$L__BB18_40:
	setp.lt.s32 	%p20, %r45, 5;
	cvt.rn.f64.s64 	%rd22, %rd48;
	cvt.rn.f64.u64 	%rd23, %rd48;
	selp.f64 	%rd49, %rd22, %rd23, %p20;
$L__BB18_41:
	setp.gt.u32 	%p25, %r1, 3;
	mov.b64 	%rd51, 0d0000000000000000;
	@%p25 bra 	$L__BB18_75;
	@%p7 bra 	$L__BB18_52;
	shl.b64 	%rd46, %rd1, 1;
	add.s64 	%rd47, %rd2, %rd46;
	ld.b16 	%rs2, [%rd47+2];
	setp.ne.b32 	%p39, %r45, 13;
	cvt.u32.u16 	%r6, %rs2;
	@%p39 bra 	$L__BB18_45;
	shl.b32 	%r47, %r6, 16;
	bra.uni 	$L__BB18_51;
$L__BB18_52:
	setp.gt.s32 	%p26, %r45, 4;
	@%p26 bra 	$L__BB18_60;
	bra.uni 	$L__BB18_53;
$L__BB18_60:
	setp.gt.s32 	%p27, %r45, 6;
	@%p27 bra 	$L__BB18_64;
	bra.uni 	$L__BB18_61;
$L__BB18_64:
	setp.eq.b32 	%p28, %r45, 7;
	@%p28 bra 	$L__BB18_72;
	setp.eq.b32 	%p29, %r45, 9;
	@%p29 bra 	$L__BB18_68;
	setp.ne.b32 	%p30, %r45, 10;
	@%p30 bra 	$L__BB18_73;
	shl.b64 	%rd40, %rd1, 2;
	add.s64 	%rd41, %rd2, %rd40;
	ld.b32 	%r28, [%rd41+4];
	cvt.f64.f32 	%rd51, %r28;
	bra.uni 	$L__BB18_75;
$L__BB18_45:
	cvt.s32.s16 	%r29, %rs2;
	and.b32 	%r47, %r29, -2147483648;
	bfe.u32 	%r7, %r6, 10, 5;
	setp.eq.b32 	%p40, %r7, 31;
	@%p40 bra 	$L__BB18_49;
	and.b32 	%r8, %r6, 1023;
	setp.ne.b32 	%p41, %r7, 0;
	@%p41 bra 	$L__BB18_50;
	setp.eq.b32 	%p42, %r8, 0;
	@%p42 bra 	$L__BB18_51;
	clz.b32 	%r32, %r8;
	xor.b32 	%r33, %r32, 31;
	sub.s32 	%r34, 9, %r33;
	shl.b32 	%r35, %r6, %r34;
	shl.b32 	%r36, %r33, 23;
	shl.b32 	%r37, %r35, 14;
	and.b32 	%r38, %r37, 8372224;
	add.s32 	%r39, %r36, %r47;
	add.s32 	%r40, %r39, %r38;
	add.s32 	%r47, %r40, 864026624;
	bra.uni 	$L__BB18_51;
$L__BB18_53:
	setp.gt.s32 	%p33, %r45, 2;
	@%p33 bra 	$L__BB18_57;
	setp.eq.b32 	%p36, %r45, 1;
	@%p36 bra 	$L__BB18_69;
	setp.eq.b32 	%p37, %r45, 2;
	@%p37 bra 	$L__BB18_56;
	bra.uni 	$L__BB18_73;
$L__BB18_56:
	add.s64 	%rd35, %rd2, %rd1;
	ld.s8 	%rd50, [%rd35+1];
	bra.uni 	$L__BB18_74;
$L__BB18_57:
	setp.eq.b32 	%p34, %r45, 3;
	@%p34 bra 	$L__BB18_70;
	setp.eq.b32 	%p35, %r45, 4;
	@%p35 bra 	$L__BB18_59;
	bra.uni 	$L__BB18_73;
$L__BB18_59:
	shl.b64 	%rd31, %rd1, 2;
	add.s64 	%rd32, %rd2, %rd31;
	ld.s32 	%rd50, [%rd32+4];
	bra.uni 	$L__BB18_74;
$L__BB18_61:
	setp.eq.b32 	%p31, %r45, 5;
	@%p31 bra 	$L__BB18_71;
	setp.eq.b32 	%p32, %r45, 6;
	@%p32 bra 	$L__BB18_63;
	bra.uni 	$L__BB18_73;
$L__BB18_63:
	shl.b64 	%rd28, %rd1, 1;
	add.s64 	%rd29, %rd2, %rd28;
	ld.b16 	%rd50, [%rd29+2];
	bra.uni 	$L__BB18_74;
$L__BB18_49:
	shl.b32 	%r30, %r6, 13;
	or.b32 	%r31, %r47, %r30;
	or.b32 	%r47, %r31, 2139095040;
	bra.uni 	$L__BB18_51;
$L__BB18_50:
	shl.b32 	%r41, %r7, 23;
	shl.b32 	%r42, %r8, 13;
	or.b32 	%r43, %r41, %r42;
	add.s32 	%r44, %r43, %r47;
	add.s32 	%r47, %r44, 939524096;
$L__BB18_51:
	cvt.f64.f32 	%rd51, %r47;
	bra.uni 	$L__BB18_75;
$L__BB18_69:
	shl.b64 	%rd36, %rd1, 3;
	add.s64 	%rd37, %rd2, %rd36;
	ld.b64 	%rd50, [%rd37+8];
	bra.uni 	$L__BB18_74;
$L__BB18_70:
	shl.b64 	%rd33, %rd1, 1;
	add.s64 	%rd34, %rd2, %rd33;
	ld.s16 	%rd50, [%rd34+2];
	bra.uni 	$L__BB18_74;
$L__BB18_72:
	shl.b64 	%rd26, %rd1, 2;
	add.s64 	%rd27, %rd2, %rd26;
	ld.b32 	%rd50, [%rd27+4];
	bra.uni 	$L__BB18_74;
$L__BB18_71:
	add.s64 	%rd30, %rd2, %rd1;
	ld.b8 	%rd50, [%rd30+1];
	bra.uni 	$L__BB18_74;
$L__BB18_68:
	shl.b64 	%rd38, %rd1, 3;
	add.s64 	%rd39, %rd2, %rd38;
	ld.b64 	%rd51, [%rd39+8];
	bra.uni 	$L__BB18_75;
$L__BB18_73:
	shl.b64 	%rd42, %rd1, 3;
	add.s64 	%rd43, %rd2, %rd42;
	ld.b64 	%rd50, [%rd43+8];
$L__BB18_74:
	setp.lt.s32 	%p38, %r45, 5;
	cvt.rn.f64.s64 	%rd44, %rd50;
	cvt.rn.f64.u64 	%rd45, %rd50;
	selp.f64 	%rd51, %rd44, %rd45, %p38;
$L__BB18_75:
	st.param.b64 	[func_retval0+8], %rd51;
	st.param.b64 	[func_retval0], %rd49;
	ret;
}
.weak .func _Z7q_storeIdEvPvy5QPairIT_Ei(
	.param .b64 _Z7q_storeIdEvPvy5QPairIT_Ei_param_0,
	.param .b64 _Z7q_storeIdEvPvy5QPairIT_Ei_param_1,
	.param .align 8 .b8 _Z7q_storeIdEvPvy5QPairIT_Ei_param_2[16],
	.param .b32 _Z7q_storeIdEvPvy5QPairIT_Ei_param_3
)
{
	.reg .pred 	%p<49>;
	.reg .b16 	%rs<3>;
	.reg .b32 	%r<68>;
	.reg .b64 	%rd<80>;
	ld.param.b32 	%r19, [_Z7q_storeIdEvPvy5QPairIT_Ei_param_3];
	ld.param.b64 	%rd17, [_Z7q_storeIdEvPvy5QPairIT_Ei_param_1];
	setp.gt.s32 	%p1, %r19, 15;
	@%p1 bra 	$L__BB19_4;
	mov.b32 	%r65, 12;
	setp.eq.b32 	%p4, %r19, 14;
	@%p4 bra 	$L__BB19_8;
	setp.eq.b32 	%p5, %r19, 15;
	mov.b32 	%r65, %r19;
	@%p5 bra 	$L__BB19_3;
	bra.uni 	$L__BB19_8;
$L__BB19_3:
	mov.b32 	%r65, 13;
	bra.uni 	$L__BB19_8;
$L__BB19_4:
	setp.eq.b32 	%p2, %r19, 16;
	@%p2 bra 	$L__BB19_7;
	setp.ne.b32 	%p3, %r19, 17;
	mov.b32 	%r65, %r19;
	@%p3 bra 	$L__BB19_8;
	mov.b32 	%r65, 9;
	bra.uni 	$L__BB19_8;
$L__BB19_7:
	mov.b32 	%r65, 10;
$L__BB19_8:
	ld.param.b64 	%rd16, [_Z7q_storeIdEvPvy5QPairIT_Ei_param_0];
	add.s32 	%r1, %r19, -14;
	setp.lt.u32 	%p6, %r1, 4;
	selp.b32 	%r20, 1, 0, %p6;
	shl.b64 	%rd1, %rd17, %r20;
	ld.param.b64 	%rd2, [_Z7q_storeIdEvPvy5QPairIT_Ei_param_2];
	and.b32 	%r2, %r65, -2;
	setp.ne.b32 	%p7, %r2, 12;
	@%p7 bra 	$L__BB19_24;
	shr.u64 	%rd4, %rd2, 48;
	cvt.u32.u64 	%r22, %rd4;
	and.b32 	%r3, %r22, 32768;
	shr.u64 	%rd22, %rd2, 52;
	cvt.u32.u64 	%r23, %rd22;
	and.b32 	%r4, %r23, 2047;
	setp.eq.b32 	%p10, %r4, 0;
	@%p10 bra 	$L__BB19_12;
	and.b64 	%rd3, %rd2, 4503599627370495;
	setp.eq.b32 	%p9, %r65, 12;
	selp.b32 	%r5, 11, 8, %p9;
	selp.b32 	%r7, 31744, 32640, %p9;
	setp.ne.b32 	%p11, %r4, 2047;
	@%p11 bra 	$L__BB19_13;
	setp.eq.b64 	%p12, %rd3, 0;
	add.s32 	%r24, %r5, -2;
	mov.b32 	%r25, 1;
	shl.b32 	%r26, %r25, %r24;
	selp.b32 	%r27, 0, %r26, %p12;
	or.b32 	%r28, %r27, %r7;
	or.b32 	%r29, %r28, %r3;
	cvt.u16.u32 	%rs1, %r29;
	bra.uni 	$L__BB19_23;
$L__BB19_24:
	setp.ne.b32 	%p8, %r65, 10;
	@%p8 bra 	$L__BB19_26;
	cvt.rn.f32.f64 	%r21, %rd2;
	shl.b64 	%rd20, %rd1, 2;
	add.s64 	%rd21, %rd16, %rd20;
	st.b32 	[%rd21], %r21;
	bra.uni 	$L__BB19_27;
$L__BB19_26:
	shl.b64 	%rd18, %rd1, 3;
	add.s64 	%rd19, %rd16, %rd18;
	st.b64 	[%rd19], %rd2;
	bra.uni 	$L__BB19_27;
$L__BB19_12:
	cvt.u16.u32 	%rs1, %r3;
	bra.uni 	$L__BB19_23;
$L__BB19_13:
	selp.b32 	%r30, -14, -126, %p9;
	add.s32 	%r8, %r4, -1023;
	or.b64 	%rd5, %rd3, 4503599627370496;
	setp.ge.s32 	%p13, %r8, %r30;
	@%p13 bra 	$L__BB19_19;
	and.b64 	%rd6, %rd4, 32768;
	selp.b32 	%r40, 28, -81, %p9;
	sub.s32 	%r9, %r40, %r8;
	setp.gt.s32 	%p21, %r9, 0;
	@%p21 bra 	$L__BB19_16;
	bra.uni 	$L__BB19_15;
$L__BB19_16:
	setp.gt.u32 	%p22, %r9, 63;
	mov.b64 	%rd78, 0;
	@%p22 bra 	$L__BB19_18;
	shr.u64 	%rd36, %rd5, %r9;
	mov.b64 	%rd37, -1;
	shl.b64 	%rd38, %rd37, %r9;
	not.b64 	%rd39, %rd38;
	and.b64 	%rd40, %rd5, %rd39;
	add.s32 	%r41, %r9, -1;
	mov.b64 	%rd41, 1;
	shl.b64 	%rd42, %rd41, %r41;
	setp.gt.u64 	%p23, %rd40, %rd42;
	setp.eq.b64 	%p24, %rd40, %rd42;
	and.b64 	%rd43, %rd36, 1;
	setp.ne.b64 	%p25, %rd43, 0;
	and.pred 	%p26, %p24, %p25;
	or.pred 	%p27, %p23, %p26;
	selp.b64 	%rd44, 1, 0, %p27;
	add.s64 	%rd78, %rd36, %rd44;
	bra.uni 	$L__BB19_18;
$L__BB19_19:
	selp.b32 	%r6, 15, 127, %p9;
	sub.s32 	%r31, 53, %r5;
	shr.u64 	%rd23, %rd5, %r31;
	mov.b64 	%rd24, -1;
	shl.b64 	%rd25, %rd24, %r31;
	not.b64 	%rd26, %rd25;
	and.b64 	%rd27, %rd26, %rd2;
	sub.s32 	%r32, 52, %r5;
	mov.b64 	%rd28, 1;
	shl.b64 	%rd29, %rd28, %r32;
	setp.gt.u64 	%p14, %rd27, %rd29;
	setp.eq.b64 	%p15, %rd27, %rd29;
	and.b64 	%rd30, %rd23, 1;
	setp.ne.b64 	%p16, %rd30, 0;
	and.pred 	%p17, %p15, %p16;
	or.pred 	%p18, %p14, %p17;
	selp.b64 	%rd31, 1, 0, %p18;
	add.s64 	%rd7, %rd23, %rd31;
	shl.b64 	%rd8, %rd28, %r5;
	setp.eq.b64 	%p19, %rd7, %rd8;
	add.s32 	%r33, %r4, -1022;
	selp.b32 	%r10, %r33, %r8, %p19;
	setp.le.s32 	%p20, %r10, %r6;
	@%p20 bra 	$L__BB19_21;
	or.b32 	%r66, %r3, %r7;
	bra.uni 	$L__BB19_22;
$L__BB19_21:
	selp.b32 	%r34, 1, 0, %p19;
	shr.u64 	%rd32, %rd7, %r34;
	add.s32 	%r35, %r10, %r6;
	add.s32 	%r36, %r5, -1;
	shl.b32 	%r37, %r35, %r36;
	shl.b64 	%rd33, %rd24, %r36;
	not.b64 	%rd34, %rd33;
	and.b64 	%rd35, %rd32, %rd34;
	cvt.u32.u64 	%r38, %rd35;
	or.b32 	%r39, %r37, %r38;
	or.b32 	%r66, %r39, %r3;
$L__BB19_22:
	cvt.u16.u32 	%rs1, %r66;
	bra.uni 	$L__BB19_23;
$L__BB19_15:
	neg.s32 	%r42, %r9;
	shl.b64 	%rd78, %rd5, %r42;
$L__BB19_18:
	or.b64 	%rd45, %rd78, %rd6;
	cvt.u16.u64 	%rs1, %rd45;
$L__BB19_23:
	shl.b64 	%rd46, %rd1, 1;
	add.s64 	%rd47, %rd16, %rd46;
	st.b16 	[%rd47], %rs1;
$L__BB19_27:
	setp.gt.u32 	%p28, %r1, 3;
	@%p28 bra 	$L__BB19_47;
	ld.param.b64 	%rd9, [_Z7q_storeIdEvPvy5QPairIT_Ei_param_2+8];
	@%p7 bra 	$L__BB19_44;
	shr.u64 	%rd11, %rd9, 48;
	cvt.u32.u64 	%r44, %rd11;
	and.b32 	%r11, %r44, 32768;
	shr.u64 	%rd52, %rd9, 52;
	cvt.u32.u64 	%r45, %rd52;
	and.b32 	%r12, %r45, 2047;
	setp.eq.b32 	%p31, %r12, 0;
	@%p31 bra 	$L__BB19_32;
	and.b64 	%rd10, %rd9, 4503599627370495;
	setp.eq.b32 	%p30, %r65, 12;
	selp.b32 	%r13, 11, 8, %p30;
	selp.b32 	%r15, 31744, 32640, %p30;
	setp.ne.b32 	%p32, %r12, 2047;
	@%p32 bra 	$L__BB19_33;
	setp.eq.b64 	%p33, %rd10, 0;
	add.s32 	%r46, %r13, -2;
	mov.b32 	%r47, 1;
	shl.b32 	%r48, %r47, %r46;
	selp.b32 	%r49, 0, %r48, %p33;
	or.b32 	%r50, %r49, %r15;
	or.b32 	%r51, %r50, %r11;
	cvt.u16.u32 	%rs2, %r51;
	bra.uni 	$L__BB19_43;
$L__BB19_44:
	setp.ne.b32 	%p29, %r65, 10;
	@%p29 bra 	$L__BB19_46;
	cvt.rn.f32.f64 	%r43, %rd9;
	shl.b64 	%rd50, %rd1, 2;
	add.s64 	%rd51, %rd16, %rd50;
	st.b32 	[%rd51+4], %r43;
	bra.uni 	$L__BB19_47;
$L__BB19_46:
	shl.b64 	%rd48, %rd1, 3;
	add.s64 	%rd49, %rd16, %rd48;
	st.b64 	[%rd49+8], %rd9;
	bra.uni 	$L__BB19_47;
$L__BB19_32:
	cvt.u16.u32 	%rs2, %r11;
	bra.uni 	$L__BB19_43;
$L__BB19_33:
	selp.b32 	%r52, -14, -126, %p30;
	add.s32 	%r16, %r12, -1023;
	or.b64 	%rd12, %rd10, 4503599627370496;
	setp.ge.s32 	%p34, %r16, %r52;
	@%p34 bra 	$L__BB19_39;
	and.b64 	%rd13, %rd11, 32768;
	selp.b32 	%r62, 28, -81, %p30;
	sub.s32 	%r17, %r62, %r16;
	setp.gt.s32 	%p42, %r17, 0;
	@%p42 bra 	$L__BB19_36;
	bra.uni 	$L__BB19_35;
$L__BB19_36:
	setp.gt.u32 	%p43, %r17, 63;
	mov.b64 	%rd79, 0;
	@%p43 bra 	$L__BB19_38;
	shr.u64 	%rd66, %rd12, %r17;
	mov.b64 	%rd67, -1;
	shl.b64 	%rd68, %rd67, %r17;
	not.b64 	%rd69, %rd68;
	and.b64 	%rd70, %rd12, %rd69;
	add.s32 	%r63, %r17, -1;
	mov.b64 	%rd71, 1;
	shl.b64 	%rd72, %rd71, %r63;
	setp.gt.u64 	%p44, %rd70, %rd72;
	setp.eq.b64 	%p45, %rd70, %rd72;
	and.b64 	%rd73, %rd66, 1;
	setp.ne.b64 	%p46, %rd73, 0;
	and.pred 	%p47, %p45, %p46;
	or.pred 	%p48, %p44, %p47;
	selp.b64 	%rd74, 1, 0, %p48;
	add.s64 	%rd79, %rd66, %rd74;
	bra.uni 	$L__BB19_38;
$L__BB19_39:
	selp.b32 	%r14, 15, 127, %p30;
	sub.s32 	%r53, 53, %r13;
	shr.u64 	%rd53, %rd12, %r53;
	mov.b64 	%rd54, -1;
	shl.b64 	%rd55, %rd54, %r53;
	not.b64 	%rd56, %rd55;
	and.b64 	%rd57, %rd9, %rd56;
	sub.s32 	%r54, 52, %r13;
	mov.b64 	%rd58, 1;
	shl.b64 	%rd59, %rd58, %r54;
	setp.gt.u64 	%p35, %rd57, %rd59;
	setp.eq.b64 	%p36, %rd57, %rd59;
	and.b64 	%rd60, %rd53, 1;
	setp.ne.b64 	%p37, %rd60, 0;
	and.pred 	%p38, %p36, %p37;
	or.pred 	%p39, %p35, %p38;
	selp.b64 	%rd61, 1, 0, %p39;
	add.s64 	%rd14, %rd53, %rd61;
	shl.b64 	%rd15, %rd58, %r13;
	setp.eq.b64 	%p40, %rd14, %rd15;
	add.s32 	%r55, %r12, -1022;
	selp.b32 	%r18, %r55, %r16, %p40;
	setp.le.s32 	%p41, %r18, %r14;
	@%p41 bra 	$L__BB19_41;
	or.b32 	%r67, %r11, %r15;
	bra.uni 	$L__BB19_42;
$L__BB19_41:
	selp.b32 	%r56, 1, 0, %p40;
	shr.u64 	%rd62, %rd14, %r56;
	add.s32 	%r57, %r18, %r14;
	add.s32 	%r58, %r13, -1;
	shl.b32 	%r59, %r57, %r58;
	shl.b64 	%rd63, %rd54, %r58;
	not.b64 	%rd64, %rd63;
	and.b64 	%rd65, %rd62, %rd64;
	cvt.u32.u64 	%r60, %rd65;
	or.b32 	%r61, %r59, %r60;
	or.b32 	%r67, %r61, %r11;
$L__BB19_42:
	cvt.u16.u32 	%rs2, %r67;
	bra.uni 	$L__BB19_43;
$L__BB19_35:
	neg.s32 	%r64, %r17;
	shl.b64 	%rd79, %rd12, %r64;
$L__BB19_38:
	or.b64 	%rd75, %rd79, %rd13;
	cvt.u16.u64 	%rs2, %rd75;
$L__BB19_43:
	shl.b64 	%rd76, %rd1, 1;
	add.s64 	%rd77, %rd16, %rd76;
	st.b16 	[%rd77+2], %rs2;
$L__BB19_47:
	ret;
}
.weak .func _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj(
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_0,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_1,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_2,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_3,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_4,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_5,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_6,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_7,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_8,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_9,
	.param .b32 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_10,
	.param .b32 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_11,
	.param .b32 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_12,
	.param .b32 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_13,
	.param .b64 _Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_14
)
{
	.local .align 8 .b8 	__local_depot20[112];
	.reg .b64 	%SP;
	.reg .b64 	%SPL;
	.reg .pred 	%p<334>;
	.reg .b16 	%rs<17>;
	.reg .b32 	%r<425>;
	.reg .b64 	%rd<477>;
	mov.b64 	%SPL, __local_depot20;
	cvta.local.u64 	%SP, %SPL;
	ld.param.b32 	%r85, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_13];
	ld.param.b32 	%r82, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_10];
	ld.param.b64 	%rd66, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_9];
	ld.param.b64 	%rd62, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_4];
	ld.param.b64 	%rd58, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_0];
	add.u64 	%rd68, %SP, 0;
	add.u64 	%rd1, %SPL, 0;
	add.u64 	%rd69, %SP, 16;
	add.u64 	%rd2, %SPL, 16;
	add.u64 	%rd70, %SP, 32;
	add.u64 	%rd3, %SPL, 32;
	add.u64 	%rd71, %SP, 48;
	add.u64 	%rd4, %SPL, 48;
	add.u64 	%rd72, %SP, 64;
	add.u64 	%rd5, %SPL, 64;
	add.u64 	%rd73, %SP, 80;
	add.u64 	%rd6, %SPL, 80;
	add.u64 	%rd74, %SP, 96;
	add.u64 	%rd7, %SPL, 96;
	setp.eq.b32 	%p1, %r85, 11;
	setp.gt.s32 	%p328, %r82, 15;
	add.s32 	%r397, %r82, -14;
	setp.eq.b32 	%p329, %r82, 16;
	setp.ne.b32 	%p330, %r82, 17;
	setp.eq.b32 	%p331, %r82, 14;
	setp.eq.b32 	%p332, %r82, 15;
	@%p1 bra 	$L__BB20_2;
	setp.ne.b32 	%p2, %r85, 4;
	@%p2 bra 	$L__BB20_110;
$L__BB20_2:
	ld.param.b64 	%rd63, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_5];
	shl.b64 	%rd75, %rd66, 3;
	add.s64 	%rd76, %rd63, %rd75;
	ld.b64 	%rd451, [%rd76];
	ld.b64 	%rd8, [%rd76+8];
	setp.ge.u64 	%p3, %rd451, %rd8;
	mov.b64 	%rd455, 0d0000000000000000;
	@%p3 bra 	$L__BB20_6;
	ld.param.b64 	%rd64, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_6];
	setp.lt.u32 	%p4, %r397, 4;
	selp.b64 	%rd9, 1, 0, %p4;
	shl.b64 	%rd77, %rd451, 3;
	add.s64 	%rd450, %rd64, %rd77;
	mov.b64 	%rd455, 0d0000000000000000;
	cvt.u32.u64 	%r86, %rd9;
	setp.ne.b32 	%p23, %r85, 11;
	bra.uni 	$L__BB20_4;
)QPTX";
        result += R"QPTX(
$L__BB20_101:
	shl.b32 	%r404, %r19, 16;
$L__BB20_108:
	cvt.f64.f32 	%rd455, %r404;
$L__BB20_109:
	add.s64 	%rd451, %rd451, 1;
	add.s64 	%rd450, %rd450, 8;
	setp.lt.u64 	%p48, %rd451, %rd8;
	@%p48 bra 	$L__BB20_4;
	bra.uni 	$L__BB20_6;
$L__BB20_4:
	@%p328 bra 	$L__BB20_40;
	mov.b32 	%r400, 12;
	@%p331 bra 	$L__BB20_44;
	mov.b32 	%r400, %r82;
	@%p332 bra 	$L__BB20_39;
	bra.uni 	$L__BB20_44;
$L__BB20_39:
	mov.b32 	%r400, 13;
	bra.uni 	$L__BB20_44;
$L__BB20_40:
	@%p329 bra 	$L__BB20_43;
	mov.b32 	%r400, %r82;
	@%p330 bra 	$L__BB20_44;
	mov.b32 	%r400, 9;
	bra.uni 	$L__BB20_44;
$L__BB20_43:
	mov.b32 	%r400, 10;
$L__BB20_44:
	ld.b64 	%rd17, [%rd450];
	shl.b64 	%rd18, %rd17, %r86;
	and.b32 	%r87, %r400, -2;
	setp.ne.b32 	%p5, %r87, 12;
	@%p5 bra 	$L__BB20_54;
	shl.b64 	%rd98, %rd18, 1;
	add.s64 	%rd99, %rd62, %rd98;
	ld.b16 	%rs1, [%rd99];
	setp.ne.b32 	%p19, %r400, 13;
	cvt.u32.u16 	%r9, %rs1;
	@%p19 bra 	$L__BB20_47;
	shl.b32 	%r401, %r9, 16;
	bra.uni 	$L__BB20_53;
$L__BB20_54:
	setp.gt.s32 	%p6, %r400, 4;
	@%p6 bra 	$L__BB20_62;
	bra.uni 	$L__BB20_55;
$L__BB20_62:
	setp.gt.s32 	%p7, %r400, 6;
	@%p7 bra 	$L__BB20_66;
	bra.uni 	$L__BB20_63;
$L__BB20_66:
	setp.eq.b32 	%p8, %r400, 7;
	@%p8 bra 	$L__BB20_74;
	setp.eq.b32 	%p9, %r400, 9;
	@%p9 bra 	$L__BB20_70;
	setp.ne.b32 	%p10, %r400, 10;
	@%p10 bra 	$L__BB20_75;
	shl.b64 	%rd92, %rd18, 2;
	add.s64 	%rd93, %rd62, %rd92;
	ld.b32 	%r88, [%rd93];
	cvt.f64.f32 	%rd453, %r88;
	bra.uni 	$L__BB20_77;
$L__BB20_47:
	cvt.s32.s16 	%r89, %rs1;
	and.b32 	%r401, %r89, -2147483648;
	bfe.u32 	%r10, %r9, 10, 5;
	setp.eq.b32 	%p20, %r10, 31;
	@%p20 bra 	$L__BB20_51;
	and.b32 	%r11, %r9, 1023;
	setp.ne.b32 	%p21, %r10, 0;
	@%p21 bra 	$L__BB20_52;
	setp.eq.b32 	%p22, %r11, 0;
	@%p22 bra 	$L__BB20_53;
	clz.b32 	%r92, %r11;
	xor.b32 	%r93, %r92, 31;
	sub.s32 	%r94, 9, %r93;
	shl.b32 	%r95, %r9, %r94;
	shl.b32 	%r96, %r93, 23;
	shl.b32 	%r97, %r95, 14;
	and.b32 	%r98, %r97, 8372224;
	add.s32 	%r99, %r96, %r401;
	add.s32 	%r100, %r99, %r98;
	add.s32 	%r401, %r100, 864026624;
	bra.uni 	$L__BB20_53;
$L__BB20_55:
	setp.gt.s32 	%p13, %r400, 2;
	@%p13 bra 	$L__BB20_59;
	setp.eq.b32 	%p16, %r400, 1;
	@%p16 bra 	$L__BB20_71;
	setp.eq.b32 	%p17, %r400, 2;
	@%p17 bra 	$L__BB20_58;
	bra.uni 	$L__BB20_75;
$L__BB20_58:
	add.s64 	%rd87, %rd62, %rd18;
	ld.s8 	%rd452, [%rd87];
	bra.uni 	$L__BB20_76;
$L__BB20_59:
	setp.eq.b32 	%p14, %r400, 3;
	@%p14 bra 	$L__BB20_72;
	setp.eq.b32 	%p15, %r400, 4;
	@%p15 bra 	$L__BB20_61;
	bra.uni 	$L__BB20_75;
$L__BB20_61:
	shl.b64 	%rd83, %rd18, 2;
	add.s64 	%rd84, %rd62, %rd83;
	ld.s32 	%rd452, [%rd84];
	bra.uni 	$L__BB20_76;
$L__BB20_63:
	setp.eq.b32 	%p11, %r400, 5;
	@%p11 bra 	$L__BB20_73;
	setp.eq.b32 	%p12, %r400, 6;
	@%p12 bra 	$L__BB20_65;
	bra.uni 	$L__BB20_75;
$L__BB20_65:
	shl.b64 	%rd80, %rd18, 1;
	add.s64 	%rd81, %rd62, %rd80;
	ld.b16 	%rd452, [%rd81];
	bra.uni 	$L__BB20_76;
$L__BB20_51:
	shl.b32 	%r90, %r9, 13;
	or.b32 	%r91, %r401, %r90;
	or.b32 	%r401, %r91, 2139095040;
	bra.uni 	$L__BB20_53;
$L__BB20_52:
	shl.b32 	%r101, %r10, 23;
	shl.b32 	%r102, %r11, 13;
	or.b32 	%r103, %r101, %r102;
	add.s32 	%r104, %r103, %r401;
	add.s32 	%r401, %r104, 939524096;
$L__BB20_53:
	cvt.f64.f32 	%rd453, %r401;
	bra.uni 	$L__BB20_77;
$L__BB20_71:
	shl.b64 	%rd88, %rd18, 3;
	add.s64 	%rd89, %rd62, %rd88;
	ld.b64 	%rd452, [%rd89];
	bra.uni 	$L__BB20_76;
$L__BB20_72:
	shl.b64 	%rd85, %rd18, 1;
	add.s64 	%rd86, %rd62, %rd85;
	ld.s16 	%rd452, [%rd86];
	bra.uni 	$L__BB20_76;
$L__BB20_74:
	shl.b64 	%rd78, %rd18, 2;
	add.s64 	%rd79, %rd62, %rd78;
	ld.b32 	%rd452, [%rd79];
	bra.uni 	$L__BB20_76;
$L__BB20_73:
	add.s64 	%rd82, %rd62, %rd18;
	ld.b8 	%rd452, [%rd82];
	bra.uni 	$L__BB20_76;
$L__BB20_70:
	shl.b64 	%rd90, %rd18, 3;
	add.s64 	%rd91, %rd62, %rd90;
	ld.b64 	%rd453, [%rd91];
	bra.uni 	$L__BB20_77;
$L__BB20_75:
	shl.b64 	%rd94, %rd18, 3;
	add.s64 	%rd95, %rd62, %rd94;
	ld.b64 	%rd452, [%rd95];
$L__BB20_76:
	setp.lt.s32 	%p18, %r400, 5;
	cvt.rn.f64.s64 	%rd96, %rd452;
	cvt.rn.f64.u64 	%rd97, %rd452;
	selp.f64 	%rd453, %rd96, %rd97, %p18;
$L__BB20_77:
	add.rn.f64 	%rd455, %rd455, %rd453;
	@%p23 bra 	$L__BB20_109;
	@%p328 bra 	$L__BB20_82;
	mov.b32 	%r402, 12;
	@%p331 bra 	$L__BB20_86;
	mov.b32 	%r402, %r82;
	@%p332 bra 	$L__BB20_81;
	bra.uni 	$L__BB20_86;
$L__BB20_81:
	mov.b32 	%r402, 13;
	bra.uni 	$L__BB20_86;
$L__BB20_82:
	@%p329 bra 	$L__BB20_85;
	mov.b32 	%r402, %r82;
	@%p330 bra 	$L__BB20_86;
	mov.b32 	%r402, 9;
	bra.uni 	$L__BB20_86;
$L__BB20_85:
	mov.b32 	%r402, 10;
$L__BB20_86:
	and.b32 	%r105, %r402, -2;
	setp.ne.b32 	%p24, %r105, 12;
	@%p24 bra 	$L__BB20_109;
	shr.u64 	%rd20, %rd455, 48;
	cvt.u32.u64 	%r106, %rd20;
	and.b32 	%r12, %r106, 32768;
	shr.u64 	%rd100, %rd455, 52;
	cvt.u32.u64 	%r107, %rd100;
	and.b32 	%r13, %r107, 2047;
	setp.eq.b32 	%p26, %r13, 0;
	@%p26 bra 	$L__BB20_90;
	and.b64 	%rd19, %rd455, 4503599627370495;
	setp.eq.b32 	%p25, %r402, 12;
	selp.b32 	%r14, 11, 8, %p25;
	selp.b32 	%r403, 31744, 32640, %p25;
	setp.ne.b32 	%p27, %r13, 2047;
	@%p27 bra 	$L__BB20_91;
	setp.eq.b64 	%p28, %rd19, 0;
	add.s32 	%r108, %r14, -2;
	mov.b32 	%r109, 1;
	shl.b32 	%r110, %r109, %r108;
	selp.b32 	%r111, 0, %r110, %p28;
	or.b32 	%r112, %r12, %r111;
	or.b32 	%r113, %r112, %r403;
	cvt.u16.u32 	%rs12, %r113;
	bra.uni 	$L__BB20_100;
$L__BB20_90:
	cvt.u16.u32 	%rs12, %r12;
	bra.uni 	$L__BB20_100;
$L__BB20_91:
	selp.b32 	%r114, -14, -126, %p25;
	add.s32 	%r16, %r13, -1023;
	or.b64 	%rd21, %rd19, 4503599627370496;
	setp.ge.s32 	%p29, %r16, %r114;
	@%p29 bra 	$L__BB20_97;
	and.b64 	%rd22, %rd20, 32768;
	selp.b32 	%r124, 28, -81, %p25;
	sub.s32 	%r17, %r124, %r16;
	setp.gt.s32 	%p37, %r17, 0;
	@%p37 bra 	$L__BB20_94;
	bra.uni 	$L__BB20_93;
$L__BB20_94:
	setp.gt.u32 	%p38, %r17, 63;
	mov.b64 	%rd454, 0;
	@%p38 bra 	$L__BB20_96;
	shr.u64 	%rd114, %rd21, %r17;
	mov.b64 	%rd115, -1;
	shl.b64 	%rd116, %rd115, %r17;
	not.b64 	%rd117, %rd116;
	and.b64 	%rd118, %rd21, %rd117;
	add.s32 	%r125, %r17, -1;
	mov.b64 	%rd119, 1;
	shl.b64 	%rd120, %rd119, %r125;
	setp.gt.u64 	%p39, %rd118, %rd120;
	setp.eq.b64 	%p40, %rd118, %rd120;
	and.b64 	%rd121, %rd114, 1;
	setp.ne.b64 	%p41, %rd121, 0;
	and.pred 	%p42, %p40, %p41;
	or.pred 	%p43, %p39, %p42;
	selp.b64 	%rd122, 1, 0, %p43;
	add.s64 	%rd454, %rd114, %rd122;
	bra.uni 	$L__BB20_96;
$L__BB20_97:
	selp.b32 	%r15, 15, 127, %p25;
	sub.s32 	%r115, 53, %r14;
	shr.u64 	%rd101, %rd21, %r115;
	mov.b64 	%rd102, -1;
	shl.b64 	%rd103, %rd102, %r115;
	not.b64 	%rd104, %rd103;
	and.b64 	%rd105, %rd104, %rd455;
	sub.s32 	%r116, 52, %r14;
	mov.b64 	%rd106, 1;
	shl.b64 	%rd107, %rd106, %r116;
	setp.gt.u64 	%p30, %rd105, %rd107;
	setp.eq.b64 	%p31, %rd105, %rd107;
	and.b64 	%rd108, %rd101, 1;
	setp.ne.b64 	%p32, %rd108, 0;
	and.pred 	%p33, %p31, %p32;
	or.pred 	%p34, %p30, %p33;
	selp.b64 	%rd109, 1, 0, %p34;
	add.s64 	%rd23, %rd101, %rd109;
	shl.b64 	%rd24, %rd106, %r14;
	setp.eq.b64 	%p35, %rd23, %rd24;
	add.s32 	%r117, %r13, -1022;
	selp.b32 	%r18, %r117, %r16, %p35;
	setp.gt.s32 	%p36, %r18, %r15;
	@%p36 bra 	$L__BB20_99;
	selp.b32 	%r118, 1, 0, %p35;
	shr.u64 	%rd110, %rd23, %r118;
	add.s32 	%r119, %r18, %r15;
	add.s32 	%r120, %r14, -1;
	shl.b32 	%r121, %r119, %r120;
	shl.b64 	%rd111, %rd102, %r120;
	not.b64 	%rd112, %rd111;
	and.b64 	%rd113, %rd110, %rd112;
	cvt.u32.u64 	%r122, %rd113;
	or.b32 	%r403, %r121, %r122;
$L__BB20_99:
	or.b32 	%r123, %r403, %r12;
	cvt.u16.u32 	%rs12, %r123;
	bra.uni 	$L__BB20_100;
$L__BB20_93:
	neg.s32 	%r126, %r17;
	shl.b64 	%rd454, %rd21, %r126;
$L__BB20_96:
	or.b64 	%rd123, %rd454, %rd22;
	cvt.u16.u64 	%rs12, %rd123;
$L__BB20_100:
	setp.ne.b32 	%p44, %r402, 13;
	cvt.u32.u16 	%r19, %rs12;
	@%p44 bra 	$L__BB20_102;
	bra.uni 	$L__BB20_101;
$L__BB20_102:
	cvt.s32.s16 	%r127, %rs12;
	and.b32 	%r404, %r127, -2147483648;
	bfe.u32 	%r20, %r19, 10, 5;
	setp.eq.b32 	%p45, %r20, 31;
	@%p45 bra 	$L__BB20_106;
	and.b32 	%r21, %r19, 1023;
	setp.ne.b32 	%p46, %r20, 0;
	@%p46 bra 	$L__BB20_107;
	setp.eq.b32 	%p47, %r21, 0;
	@%p47 bra 	$L__BB20_108;
	clz.b32 	%r130, %r21;
	xor.b32 	%r131, %r130, 31;
	sub.s32 	%r132, 9, %r131;
	shl.b32 	%r133, %r19, %r132;
	shl.b32 	%r134, %r131, 23;
	shl.b32 	%r135, %r133, 14;
	and.b32 	%r136, %r135, 8372224;
	add.s32 	%r137, %r134, %r404;
	add.s32 	%r138, %r137, %r136;
	add.s32 	%r404, %r138, 864026624;
	bra.uni 	$L__BB20_108;
$L__BB20_106:
	shl.b32 	%r128, %r19, 13;
	or.b32 	%r129, %r404, %r128;
	or.b32 	%r404, %r129, 2139095040;
	bra.uni 	$L__BB20_108;
$L__BB20_107:
	shl.b32 	%r139, %r20, 23;
	shl.b32 	%r140, %r21, 13;
	or.b32 	%r141, %r139, %r140;
	add.s32 	%r142, %r141, %r404;
	add.s32 	%r404, %r142, 939524096;
	bra.uni 	$L__BB20_108;
$L__BB20_6:
	@%p328 bra 	$L__BB20_10;
	mov.b32 	%r398, 12;
	@%p331 bra 	$L__BB20_14;
	mov.b32 	%r398, %r82;
	@%p332 bra 	$L__BB20_9;
	bra.uni 	$L__BB20_14;
$L__BB20_9:
	mov.b32 	%r398, 13;
	bra.uni 	$L__BB20_14;
$L__BB20_10:
	@%p329 bra 	$L__BB20_13;
	mov.b32 	%r398, %r82;
	@%p330 bra 	$L__BB20_14;
	mov.b32 	%r398, 9;
	bra.uni 	$L__BB20_14;
$L__BB20_110:
	ld.param.b64 	%rd461, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_8];
	ld.param.b64 	%rd65, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_7];
	st.local.b64 	[%rd1], %rd65;
	st.local.b64 	[%rd1+8], %rd461;
	@%p328 bra 	$L__BB20_114;
	mov.b32 	%r405, 12;
	@%p331 bra 	$L__BB20_118;
	mov.b32 	%r405, %r82;
	@%p332 bra 	$L__BB20_113;
	bra.uni 	$L__BB20_118;
$L__BB20_113:
	mov.b32 	%r405, 13;
	bra.uni 	$L__BB20_118;
$L__BB20_114:
	@%p329 bra 	$L__BB20_117;
	mov.b32 	%r405, %r82;
	@%p330 bra 	$L__BB20_118;
	mov.b32 	%r405, 9;
	bra.uni 	$L__BB20_118;
$L__BB20_13:
	mov.b32 	%r398, 10;
$L__BB20_14:
	setp.lt.u32 	%p49, %r397, 4;
	selp.b32 	%r143, 1, 0, %p49;
	shl.b64 	%rd10, %rd66, %r143;
	and.b32 	%r1, %r398, -2;
	setp.ne.b32 	%p50, %r1, 12;
	@%p50 bra 	$L__BB20_29;
	shr.u64 	%rd12, %rd455, 48;
	cvt.u32.u64 	%r145, %rd12;
	and.b32 	%r2, %r145, 32768;
	shr.u64 	%rd128, %rd455, 52;
	cvt.u32.u64 	%r146, %rd128;
	and.b32 	%r3, %r146, 2047;
	setp.eq.b32 	%p53, %r3, 0;
	@%p53 bra 	$L__BB20_18;
	and.b64 	%rd11, %rd455, 4503599627370495;
	setp.eq.b32 	%p52, %r398, 12;
	selp.b32 	%r4, 11, 8, %p52;
	selp.b32 	%r399, 31744, 32640, %p52;
	setp.ne.b32 	%p54, %r3, 2047;
	@%p54 bra 	$L__BB20_19;
	setp.eq.b64 	%p55, %rd11, 0;
	add.s32 	%r147, %r4, -2;
	mov.b32 	%r148, 1;
	shl.b32 	%r149, %r148, %r147;
	selp.b32 	%r150, 0, %r149, %p55;
	or.b32 	%r151, %r2, %r150;
	or.b32 	%r152, %r151, %r399;
	cvt.u16.u32 	%rs11, %r152;
	bra.uni 	$L__BB20_28;
$L__BB20_29:
	setp.ne.b32 	%p51, %r398, 10;
	@%p51 bra 	$L__BB20_31;
	cvt.rn.f32.f64 	%r144, %rd455;
	shl.b64 	%rd126, %rd10, 2;
	add.s64 	%rd127, %rd58, %rd126;
	st.b32 	[%rd127], %r144;
	bra.uni 	$L__BB20_32;
$L__BB20_31:
	shl.b64 	%rd124, %rd10, 3;
	add.s64 	%rd125, %rd58, %rd124;
	st.b64 	[%rd125], %rd455;
	bra.uni 	$L__BB20_32;
$L__BB20_18:
	cvt.u16.u32 	%rs11, %r2;
	bra.uni 	$L__BB20_28;
$L__BB20_19:
	selp.b32 	%r153, -14, -126, %p52;
	add.s32 	%r6, %r3, -1023;
	or.b64 	%rd13, %rd11, 4503599627370496;
	setp.ge.s32 	%p56, %r6, %r153;
	@%p56 bra 	$L__BB20_25;
	and.b64 	%rd14, %rd12, 32768;
	selp.b32 	%r163, 28, -81, %p52;
	sub.s32 	%r7, %r163, %r6;
	setp.gt.s32 	%p64, %r7, 0;
	@%p64 bra 	$L__BB20_22;
	bra.uni 	$L__BB20_21;
$L__BB20_22:
	setp.gt.u32 	%p65, %r7, 63;
	mov.b64 	%rd449, 0;
	@%p65 bra 	$L__BB20_24;
	shr.u64 	%rd142, %rd13, %r7;
	mov.b64 	%rd143, -1;
	shl.b64 	%rd144, %rd143, %r7;
	not.b64 	%rd145, %rd144;
	and.b64 	%rd146, %rd13, %rd145;
	add.s32 	%r164, %r7, -1;
	mov.b64 	%rd147, 1;
	shl.b64 	%rd148, %rd147, %r164;
	setp.gt.u64 	%p66, %rd146, %rd148;
	setp.eq.b64 	%p67, %rd146, %rd148;
	and.b64 	%rd149, %rd142, 1;
	setp.ne.b64 	%p68, %rd149, 0;
	and.pred 	%p69, %p67, %p68;
	or.pred 	%p70, %p66, %p69;
	selp.b64 	%rd150, 1, 0, %p70;
	add.s64 	%rd449, %rd142, %rd150;
	bra.uni 	$L__BB20_24;
$L__BB20_117:
	mov.b32 	%r405, 10;
$L__BB20_118:
	ld.param.b64 	%rd60, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_2];
	setp.lt.u32 	%p73, %r397, 4;
	selp.b32 	%r166, 1, 0, %p73;
	shl.b64 	%rd27, %rd66, %r166;
	and.b32 	%r24, %r405, -2;
	setp.ne.b32 	%p74, %r24, 12;
	@%p74 bra 	$L__BB20_128;
	shl.b64 	%rd180, %rd27, 1;
	add.s64 	%rd181, %rd60, %rd180;
	ld.b16 	%rs4, [%rd181];
	setp.ne.b32 	%p88, %r405, 13;
	cvt.u32.u16 	%r25, %rs4;
	@%p88 bra 	$L__BB20_121;
	shl.b32 	%r406, %r25, 16;
	bra.uni 	$L__BB20_127;
$L__BB20_128:
	setp.gt.s32 	%p75, %r405, 4;
	@%p75 bra 	$L__BB20_136;
	bra.uni 	$L__BB20_129;
$L__BB20_136:
	setp.gt.s32 	%p76, %r405, 6;
	@%p76 bra 	$L__BB20_140;
	bra.uni 	$L__BB20_137;
$L__BB20_140:
	setp.eq.b32 	%p77, %r405, 7;
	@%p77 bra 	$L__BB20_148;
	setp.eq.b32 	%p78, %r405, 9;
	@%p78 bra 	$L__BB20_144;
	setp.ne.b32 	%p79, %r405, 10;
	@%p79 bra 	$L__BB20_149;
	shl.b64 	%rd174, %rd27, 2;
	add.s64 	%rd175, %rd60, %rd174;
	ld.b32 	%r167, [%rd175];
	cvt.f64.f32 	%rd457, %r167;
	bra.uni 	$L__BB20_151;
$L__BB20_121:
	cvt.s32.s16 	%r168, %rs4;
	and.b32 	%r406, %r168, -2147483648;
	bfe.u32 	%r26, %r25, 10, 5;
	setp.eq.b32 	%p89, %r26, 31;
	@%p89 bra 	$L__BB20_125;
	and.b32 	%r27, %r25, 1023;
	setp.ne.b32 	%p90, %r26, 0;
	@%p90 bra 	$L__BB20_126;
	setp.eq.b32 	%p91, %r27, 0;
	@%p91 bra 	$L__BB20_127;
	clz.b32 	%r171, %r27;
	xor.b32 	%r172, %r171, 31;
	sub.s32 	%r173, 9, %r172;
	shl.b32 	%r174, %r25, %r173;
	shl.b32 	%r175, %r172, 23;
	shl.b32 	%r176, %r174, 14;
	and.b32 	%r177, %r176, 8372224;
	add.s32 	%r178, %r175, %r406;
	add.s32 	%r179, %r178, %r177;
	add.s32 	%r406, %r179, 864026624;
	bra.uni 	$L__BB20_127;
$L__BB20_129:
	setp.gt.s32 	%p82, %r405, 2;
	@%p82 bra 	$L__BB20_133;
	setp.eq.b32 	%p85, %r405, 1;
	@%p85 bra 	$L__BB20_145;
	setp.eq.b32 	%p86, %r405, 2;
	@%p86 bra 	$L__BB20_132;
	bra.uni 	$L__BB20_149;
$L__BB20_132:
	add.s64 	%rd169, %rd60, %rd27;
	ld.s8 	%rd456, [%rd169];
	bra.uni 	$L__BB20_150;
$L__BB20_25:
	selp.b32 	%r5, 15, 127, %p52;
	sub.s32 	%r154, 53, %r4;
	shr.u64 	%rd129, %rd13, %r154;
	mov.b64 	%rd130, -1;
	shl.b64 	%rd131, %rd130, %r154;
	not.b64 	%rd132, %rd131;
	and.b64 	%rd133, %rd132, %rd455;
	sub.s32 	%r155, 52, %r4;
	mov.b64 	%rd134, 1;
	shl.b64 	%rd135, %rd134, %r155;
	setp.gt.u64 	%p57, %rd133, %rd135;
	setp.eq.b64 	%p58, %rd133, %rd135;
	and.b64 	%rd136, %rd129, 1;
	setp.ne.b64 	%p59, %rd136, 0;
	and.pred 	%p60, %p58, %p59;
	or.pred 	%p61, %p57, %p60;
	selp.b64 	%rd137, 1, 0, %p61;
	add.s64 	%rd15, %rd129, %rd137;
	shl.b64 	%rd16, %rd134, %r4;
	setp.eq.b64 	%p62, %rd15, %rd16;
	add.s32 	%r156, %r3, -1022;
	selp.b32 	%r8, %r156, %r6, %p62;
	setp.gt.s32 	%p63, %r8, %r5;
	@%p63 bra 	$L__BB20_27;
	selp.b32 	%r157, 1, 0, %p62;
	shr.u64 	%rd138, %rd15, %r157;
	add.s32 	%r158, %r8, %r5;
	add.s32 	%r159, %r4, -1;
	shl.b32 	%r160, %r158, %r159;
	shl.b64 	%rd139, %rd130, %r159;
	not.b64 	%rd140, %rd139;
	and.b64 	%rd141, %rd138, %rd140;
	cvt.u32.u64 	%r161, %rd141;
	or.b32 	%r399, %r160, %r161;
$L__BB20_27:
	or.b32 	%r162, %r399, %r2;
	cvt.u16.u32 	%rs11, %r162;
	bra.uni 	$L__BB20_28;
$L__BB20_133:
	setp.eq.b32 	%p83, %r405, 3;
	@%p83 bra 	$L__BB20_146;
	setp.eq.b32 	%p84, %r405, 4;
	@%p84 bra 	$L__BB20_135;
	bra.uni 	$L__BB20_149;
$L__BB20_135:
	shl.b64 	%rd165, %rd27, 2;
	add.s64 	%rd166, %rd60, %rd165;
	ld.s32 	%rd456, [%rd166];
	bra.uni 	$L__BB20_150;
$L__BB20_137:
	setp.eq.b32 	%p80, %r405, 5;
	@%p80 bra 	$L__BB20_147;
	setp.eq.b32 	%p81, %r405, 6;
	@%p81 bra 	$L__BB20_139;
	bra.uni 	$L__BB20_149;
$L__BB20_139:
	shl.b64 	%rd162, %rd27, 1;
	add.s64 	%rd163, %rd60, %rd162;
	ld.b16 	%rd456, [%rd163];
	bra.uni 	$L__BB20_150;
$L__BB20_125:
	shl.b32 	%r169, %r25, 13;
	or.b32 	%r170, %r406, %r169;
	or.b32 	%r406, %r170, 2139095040;
	bra.uni 	$L__BB20_127;
$L__BB20_126:
	shl.b32 	%r180, %r26, 23;
	shl.b32 	%r181, %r27, 13;
	or.b32 	%r182, %r180, %r181;
	add.s32 	%r183, %r182, %r406;
	add.s32 	%r406, %r183, 939524096;
$L__BB20_127:
	cvt.f64.f32 	%rd457, %r406;
	bra.uni 	$L__BB20_151;
$L__BB20_21:
	neg.s32 	%r165, %r7;
	shl.b64 	%rd449, %rd13, %r165;
$L__BB20_24:
	or.b64 	%rd151, %rd449, %rd14;
	cvt.u16.u64 	%rs11, %rd151;
$L__BB20_28:
	shl.b64 	%rd152, %rd10, 1;
	add.s64 	%rd153, %rd58, %rd152;
	st.b16 	[%rd153], %rs11;
$L__BB20_32:
	setp.gt.u32 	%p71, %r397, 3;
	@%p71 bra 	$L__BB20_552;
	@%p50 bra 	$L__BB20_35;
	shl.b64 	%rd158, %rd10, 1;
	add.s64 	%rd159, %rd58, %rd158;
	st.b16 	[%rd159+2], 0;
	bra.uni 	$L__BB20_552;
$L__BB20_35:
	setp.ne.b32 	%p72, %r398, 10;
	@%p72 bra 	$L__BB20_37;
	shl.b64 	%rd156, %rd10, 2;
	add.s64 	%rd157, %rd58, %rd156;
	st.b32 	[%rd157+4], 0;
	bra.uni 	$L__BB20_552;
$L__BB20_37:
	shl.b64 	%rd154, %rd10, 3;
	add.s64 	%rd155, %rd58, %rd154;
	st.b64 	[%rd155+8], 0;
	bra.uni 	$L__BB20_552;
$L__BB20_145:
	shl.b64 	%rd170, %rd27, 3;
	add.s64 	%rd171, %rd60, %rd170;
	ld.b64 	%rd456, [%rd171];
	bra.uni 	$L__BB20_150;
$L__BB20_146:
	shl.b64 	%rd167, %rd27, 1;
	add.s64 	%rd168, %rd60, %rd167;
	ld.s16 	%rd456, [%rd168];
	bra.uni 	$L__BB20_150;
$L__BB20_148:
	shl.b64 	%rd160, %rd27, 2;
	add.s64 	%rd161, %rd60, %rd160;
	ld.b32 	%rd456, [%rd161];
	bra.uni 	$L__BB20_150;
$L__BB20_147:
	add.s64 	%rd164, %rd60, %rd27;
	ld.b8 	%rd456, [%rd164];
	bra.uni 	$L__BB20_150;
$L__BB20_144:
	shl.b64 	%rd172, %rd27, 3;
	add.s64 	%rd173, %rd60, %rd172;
	ld.b64 	%rd457, [%rd173];
	bra.uni 	$L__BB20_151;
$L__BB20_149:
	shl.b64 	%rd176, %rd27, 3;
	add.s64 	%rd177, %rd60, %rd176;
	ld.b64 	%rd456, [%rd177];
$L__BB20_150:
	setp.lt.s32 	%p87, %r405, 5;
	cvt.rn.f64.s64 	%rd178, %rd456;
	cvt.rn.f64.u64 	%rd179, %rd456;
	selp.f64 	%rd457, %rd178, %rd179, %p87;
$L__BB20_151:
	setp.gt.u32 	%p92, %r397, 3;
	mov.b64 	%rd464, 0d0000000000000000;
	mov.b64 	%rd459, %rd464;
	@%p92 bra 	$L__BB20_185;
	@%p74 bra 	$L__BB20_162;
	shl.b64 	%rd202, %rd27, 1;
	add.s64 	%rd203, %rd60, %rd202;
	ld.b16 	%rs5, [%rd203+2];
	setp.ne.b32 	%p106, %r405, 13;
	cvt.u32.u16 	%r28, %rs5;
	@%p106 bra 	$L__BB20_155;
	shl.b32 	%r407, %r28, 16;
	bra.uni 	$L__BB20_161;
$L__BB20_162:
	setp.gt.s32 	%p93, %r405, 4;
	@%p93 bra 	$L__BB20_170;
	bra.uni 	$L__BB20_163;
$L__BB20_170:
	setp.gt.s32 	%p94, %r405, 6;
	@%p94 bra 	$L__BB20_174;
	bra.uni 	$L__BB20_171;
$L__BB20_174:
	setp.eq.b32 	%p95, %r405, 7;
	@%p95 bra 	$L__BB20_182;
	setp.eq.b32 	%p96, %r405, 9;
	@%p96 bra 	$L__BB20_178;
	setp.ne.b32 	%p97, %r405, 10;
	@%p97 bra 	$L__BB20_183;
	shl.b64 	%rd196, %rd27, 2;
	add.s64 	%rd197, %rd60, %rd196;
	ld.b32 	%r184, [%rd197+4];
	cvt.f64.f32 	%rd459, %r184;
	bra.uni 	$L__BB20_185;
$L__BB20_155:
	cvt.s32.s16 	%r185, %rs5;
	and.b32 	%r407, %r185, -2147483648;
	bfe.u32 	%r29, %r28, 10, 5;
	setp.eq.b32 	%p107, %r29, 31;
	@%p107 bra 	$L__BB20_159;
	and.b32 	%r30, %r28, 1023;
	setp.ne.b32 	%p108, %r29, 0;
	@%p108 bra 	$L__BB20_160;
	setp.eq.b32 	%p109, %r30, 0;
	@%p109 bra 	$L__BB20_161;
	clz.b32 	%r188, %r30;
	xor.b32 	%r189, %r188, 31;
	sub.s32 	%r190, 9, %r189;
	shl.b32 	%r191, %r28, %r190;
	shl.b32 	%r192, %r189, 23;
	shl.b32 	%r193, %r191, 14;
	and.b32 	%r194, %r193, 8372224;
	add.s32 	%r195, %r192, %r407;
	add.s32 	%r196, %r195, %r194;
	add.s32 	%r407, %r196, 864026624;
	bra.uni 	$L__BB20_161;
$L__BB20_163:
	setp.gt.s32 	%p100, %r405, 2;
	@%p100 bra 	$L__BB20_167;
	setp.eq.b32 	%p103, %r405, 1;
	@%p103 bra 	$L__BB20_179;
	setp.eq.b32 	%p104, %r405, 2;
	@%p104 bra 	$L__BB20_166;
	bra.uni 	$L__BB20_183;
$L__BB20_166:
	add.s64 	%rd191, %rd60, %rd27;
	ld.s8 	%rd458, [%rd191+1];
	bra.uni 	$L__BB20_184;
$L__BB20_167:
	setp.eq.b32 	%p101, %r405, 3;
	@%p101 bra 	$L__BB20_180;
	setp.eq.b32 	%p102, %r405, 4;
	@%p102 bra 	$L__BB20_169;
	bra.uni 	$L__BB20_183;
$L__BB20_169:
	shl.b64 	%rd187, %rd27, 2;
	add.s64 	%rd188, %rd60, %rd187;
	ld.s32 	%rd458, [%rd188+4];
	bra.uni 	$L__BB20_184;
$L__BB20_171:
	setp.eq.b32 	%p98, %r405, 5;
	@%p98 bra 	$L__BB20_181;
	setp.eq.b32 	%p99, %r405, 6;
	@%p99 bra 	$L__BB20_173;
	bra.uni 	$L__BB20_183;
$L__BB20_173:
	shl.b64 	%rd184, %rd27, 1;
	add.s64 	%rd185, %rd60, %rd184;
	ld.b16 	%rd458, [%rd185+2];
	bra.uni 	$L__BB20_184;
$L__BB20_159:
	shl.b32 	%r186, %r28, 13;
	or.b32 	%r187, %r407, %r186;
	or.b32 	%r407, %r187, 2139095040;
	bra.uni 	$L__BB20_161;
$L__BB20_160:
	shl.b32 	%r197, %r29, 23;
	shl.b32 	%r198, %r30, 13;
	or.b32 	%r199, %r197, %r198;
	add.s32 	%r200, %r199, %r407;
	add.s32 	%r407, %r200, 939524096;
$L__BB20_161:
	cvt.f64.f32 	%rd459, %r407;
	bra.uni 	$L__BB20_185;
$L__BB20_179:
	shl.b64 	%rd192, %rd27, 3;
	add.s64 	%rd193, %rd60, %rd192;
	ld.b64 	%rd458, [%rd193+8];
	bra.uni 	$L__BB20_184;
$L__BB20_180:
	shl.b64 	%rd189, %rd27, 1;
	add.s64 	%rd190, %rd60, %rd189;
	ld.s16 	%rd458, [%rd190+2];
	bra.uni 	$L__BB20_184;
$L__BB20_182:
	shl.b64 	%rd182, %rd27, 2;
	add.s64 	%rd183, %rd60, %rd182;
	ld.b32 	%rd458, [%rd183+4];
	bra.uni 	$L__BB20_184;
$L__BB20_181:
	add.s64 	%rd186, %rd60, %rd27;
	ld.b8 	%rd458, [%rd186+1];
	bra.uni 	$L__BB20_184;
$L__BB20_178:
	shl.b64 	%rd194, %rd27, 3;
	add.s64 	%rd195, %rd60, %rd194;
	ld.b64 	%rd459, [%rd195+8];
	bra.uni 	$L__BB20_185;
$L__BB20_183:
	shl.b64 	%rd198, %rd27, 3;
	add.s64 	%rd199, %rd60, %rd198;
	ld.b64 	%rd458, [%rd199+8];
$L__BB20_184:
	setp.lt.s32 	%p105, %r405, 5;
	cvt.rn.f64.s64 	%rd200, %rd458;
	cvt.rn.f64.u64 	%rd201, %rd458;
	selp.f64 	%rd459, %rd200, %rd201, %p105;
$L__BB20_185:
	ld.param.b32 	%r84, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_12];
	ld.param.b64 	%rd61, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_3];
	setp.gt.u32 	%p110, %r85, 10;
	mov.b64 	%rd465, %rd464;
	@%p110 bra 	$L__BB20_330;
	mov.b32 	%r201, 1;
	shl.b32 	%r202, %r201, %r85;
	and.b32 	%r203, %r202, 1033;
	setp.ne.b32 	%p111, %r203, 0;
	mov.b64 	%rd465, %rd464;
	@%p111 bra 	$L__BB20_187;
	bra.uni 	$L__BB20_330;
$L__BB20_187:
	setp.eq.b32 	%p112, %r84, 0;
	@%p112 bra 	$L__BB20_255;
	@%p328 bra 	$L__BB20_192;
	mov.b32 	%r408, 12;
	@%p331 bra 	$L__BB20_196;
	mov.b32 	%r408, %r82;
	@%p332 bra 	$L__BB20_191;
	bra.uni 	$L__BB20_196;
$L__BB20_191:
	mov.b32 	%r408, 13;
	bra.uni 	$L__BB20_196;
$L__BB20_255:
	@%p328 bra 	$L__BB20_259;
	mov.b32 	%r411, 12;
	@%p331 bra 	$L__BB20_263;
	mov.b32 	%r411, %r82;
	@%p332 bra 	$L__BB20_258;
	bra.uni 	$L__BB20_263;
$L__BB20_258:
	mov.b32 	%r411, 13;
	bra.uni 	$L__BB20_263;
$L__BB20_192:
	@%p329 bra 	$L__BB20_195;
	mov.b32 	%r408, %r82;
	@%p330 bra 	$L__BB20_196;
	mov.b32 	%r408, 9;
	bra.uni 	$L__BB20_196;
$L__BB20_259:
	@%p329 bra 	$L__BB20_262;
	mov.b32 	%r411, %r82;
	@%p330 bra 	$L__BB20_263;
	mov.b32 	%r411, 9;
	bra.uni 	$L__BB20_263;
$L__BB20_195:
	mov.b32 	%r408, 10;
$L__BB20_196:
	cvt.u32.u64 	%r22, %rd65;
	and.b32 	%r31, %r408, -2;
	setp.ne.b32 	%p113, %r31, 12;
	@%p113 bra 	$L__BB20_206;
	setp.ne.b32 	%p126, %r408, 13;
	and.b32 	%r32, %r22, 65535;
	@%p126 bra 	$L__BB20_199;
	shl.b32 	%r409, %r32, 16;
	bra.uni 	$L__BB20_205;
$L__BB20_206:
	setp.gt.s32 	%p114, %r408, 5;
	@%p114 bra 	$L__BB20_214;
	setp.gt.s32 	%p120, %r408, 3;
	@%p120 bra 	$L__BB20_211;
	setp.eq.b32 	%p123, %r408, 2;
	@%p123 bra 	$L__BB20_221;
	setp.eq.b32 	%p124, %r408, 3;
	mov.b64 	%rd460, %rd65;
	@%p124 bra 	$L__BB20_210;
	bra.uni 	$L__BB20_224;
$L__BB20_210:
	cvt.s64.s16 	%rd460, %rd65;
	bra.uni 	$L__BB20_224;
$L__BB20_199:
	cvt.u16.u64 	%rs2, %rd65;
	cvt.s32.s16 	%r204, %rs2;
	and.b32 	%r409, %r204, -2147483648;
	bfe.u32 	%r33, %r22, 10, 5;
	setp.eq.b32 	%p127, %r33, 31;
	@%p127 bra 	$L__BB20_203;
	and.b32 	%r34, %r22, 1023;
	setp.ne.b32 	%p128, %r33, 0;
	@%p128 bra 	$L__BB20_204;
	setp.eq.b32 	%p129, %r34, 0;
	@%p129 bra 	$L__BB20_205;
	clz.b32 	%r207, %r34;
	xor.b32 	%r208, %r207, 31;
	sub.s32 	%r209, 9, %r208;
	shl.b32 	%r210, %r22, %r209;
	shl.b32 	%r211, %r208, 23;
	shl.b32 	%r212, %r210, 14;
	and.b32 	%r213, %r212, 8372224;
	add.s32 	%r214, %r211, %r409;
	add.s32 	%r215, %r214, %r213;
	add.s32 	%r409, %r215, 864026624;
	bra.uni 	$L__BB20_205;
$L__BB20_214:
	setp.gt.s32 	%p115, %r408, 8;
	@%p115 bra 	$L__BB20_218;
	setp.eq.b32 	%p118, %r408, 6;
	@%p118 bra 	$L__BB20_223;
	setp.eq.b32 	%p119, %r408, 7;
	mov.b64 	%rd460, %rd65;
	@%p119 bra 	$L__BB20_217;
	bra.uni 	$L__BB20_224;
$L__BB20_217:
	and.b64 	%rd460, %rd65, 4294967295;
	bra.uni 	$L__BB20_224;
$L__BB20_211:
	setp.eq.b32 	%p121, %r408, 4;
	@%p121 bra 	$L__BB20_222;
	setp.eq.b32 	%p122, %r408, 5;
	mov.b64 	%rd460, %rd65;
	@%p122 bra 	$L__BB20_213;
	bra.uni 	$L__BB20_224;
$L__BB20_213:
	and.b64 	%rd460, %rd65, 255;
	bra.uni 	$L__BB20_224;
$L__BB20_218:
	setp.eq.b32 	%p116, %r408, 9;
	mov.b64 	%rd465, %rd65;
	@%p116 bra 	$L__BB20_225;
	setp.ne.b32 	%p117, %r408, 10;
	mov.b64 	%rd460, %rd65;
	@%p117 bra 	$L__BB20_224;
	cvt.f64.f32 	%rd465, %r22;
	bra.uni 	$L__BB20_225;
$L__BB20_262:
	mov.b32 	%r411, 10;
$L__BB20_263:
	and.b32 	%r39, %r411, -2;
	setp.ne.b32 	%p146, %r39, 12;
	@%p146 bra 	$L__BB20_273;
	shl.b64 	%rd228, %rd27, 1;
	add.s64 	%rd229, %rd61, %rd228;
	ld.b16 	%rs6, [%rd229];
	setp.ne.b32 	%p160, %r411, 13;
	cvt.u32.u16 	%r40, %rs6;
	@%p160 bra 	$L__BB20_266;
	shl.b32 	%r412, %r40, 16;
	bra.uni 	$L__BB20_272;
$L__BB20_273:
	setp.gt.s32 	%p147, %r411, 4;
	@%p147 bra 	$L__BB20_281;
	bra.uni 	$L__BB20_274;
$L__BB20_281:
	setp.gt.s32 	%p148, %r411, 6;
	@%p148 bra 	$L__BB20_285;
	bra.uni 	$L__BB20_282;
$L__BB20_285:
	setp.eq.b32 	%p149, %r411, 7;
	@%p149 bra 	$L__BB20_293;
	setp.eq.b32 	%p150, %r411, 9;
	@%p150 bra 	$L__BB20_289;
	setp.ne.b32 	%p151, %r411, 10;
	@%p151 bra 	$L__BB20_294;
	shl.b64 	%rd222, %rd27, 2;
	add.s64 	%rd223, %rd61, %rd222;
	ld.b32 	%r236, [%rd223];
	cvt.f64.f32 	%rd465, %r236;
	bra.uni 	$L__BB20_296;
$L__BB20_266:
	cvt.s32.s16 	%r237, %rs6;
	and.b32 	%r412, %r237, -2147483648;
	bfe.u32 	%r41, %r40, 10, 5;
	setp.eq.b32 	%p161, %r41, 31;
	@%p161 bra 	$L__BB20_270;
	and.b32 	%r42, %r40, 1023;
	setp.ne.b32 	%p162, %r41, 0;
	@%p162 bra 	$L__BB20_271;
	setp.eq.b32 	%p163, %r42, 0;
	@%p163 bra 	$L__BB20_272;
	clz.b32 	%r240, %r42;
	xor.b32 	%r241, %r240, 31;
	sub.s32 	%r242, 9, %r241;
	shl.b32 	%r243, %r40, %r242;
	shl.b32 	%r244, %r241, 23;
	shl.b32 	%r245, %r243, 14;
	and.b32 	%r246, %r245, 8372224;
	add.s32 	%r247, %r244, %r412;
	add.s32 	%r248, %r247, %r246;
	add.s32 	%r412, %r248, 864026624;
	bra.uni 	$L__BB20_272;
$L__BB20_274:
	setp.gt.s32 	%p154, %r411, 2;
	@%p154 bra 	$L__BB20_278;
	setp.eq.b32 	%p157, %r411, 1;
	@%p157 bra 	$L__BB20_290;
	setp.eq.b32 	%p158, %r411, 2;
	@%p158 bra 	$L__BB20_277;
	bra.uni 	$L__BB20_294;
$L__BB20_277:
	add.s64 	%rd217, %rd61, %rd27;
	ld.s8 	%rd462, [%rd217];
	bra.uni 	$L__BB20_295;
$L__BB20_203:
	shl.b32 	%r205, %r32, 13;
	or.b32 	%r206, %r409, %r205;
	or.b32 	%r409, %r206, 2139095040;
	bra.uni 	$L__BB20_205;
$L__BB20_204:
	shl.b32 	%r216, %r33, 23;
	shl.b32 	%r217, %r34, 13;
	or.b32 	%r218, %r216, %r217;
	add.s32 	%r219, %r218, %r409;
	add.s32 	%r409, %r219, 939524096;
$L__BB20_205:
	cvt.f64.f32 	%rd465, %r409;
	bra.uni 	$L__BB20_225;
$L__BB20_278:
	setp.eq.b32 	%p155, %r411, 3;
	@%p155 bra 	$L__BB20_291;
	setp.eq.b32 	%p156, %r411, 4;
	@%p156 bra 	$L__BB20_280;
	bra.uni 	$L__BB20_294;
$L__BB20_280:
	shl.b64 	%rd213, %rd27, 2;
	add.s64 	%rd214, %rd61, %rd213;
	ld.s32 	%rd462, [%rd214];
	bra.uni 	$L__BB20_295;
$L__BB20_282:
	setp.eq.b32 	%p152, %r411, 5;
	@%p152 bra 	$L__BB20_292;
	setp.eq.b32 	%p153, %r411, 6;
	@%p153 bra 	$L__BB20_284;
	bra.uni 	$L__BB20_294;
$L__BB20_284:
	shl.b64 	%rd210, %rd27, 1;
	add.s64 	%rd211, %rd61, %rd210;
	ld.b16 	%rd462, [%rd211];
	bra.uni 	$L__BB20_295;
$L__BB20_221:
	cvt.s64.s8 	%rd460, %rd65;
	bra.uni 	$L__BB20_224;
$L__BB20_223:
	and.b64 	%rd460, %rd65, 65535;
	bra.uni 	$L__BB20_224;
$L__BB20_222:
	cvt.s64.s32 	%rd460, %rd65;
$L__BB20_224:
	setp.lt.s32 	%p125, %r408, 5;
	cvt.rn.f64.s64 	%rd204, %rd460;
	cvt.rn.f64.u64 	%rd205, %rd460;
	selp.f64 	%rd465, %rd204, %rd205, %p125;
$L__BB20_225:
	@%p92 bra 	$L__BB20_330;
	shr.u64 	%rd25, %rd65, 16;
	@%p113 bra 	$L__BB20_236;
	setp.ne.b32 	%p142, %r408, 13;
	cvt.u32.u64 	%r35, %rd25;
	and.b32 	%r36, %r35, 65535;
	@%p142 bra 	$L__BB20_229;
	shl.b32 	%r410, %r36, 16;
	bra.uni 	$L__BB20_235;
$L__BB20_236:
	setp.gt.s32 	%p130, %r408, 5;
	@%p130 bra 	$L__BB20_244;
	shr.u64 	%rd26, %rd65, 8;
	setp.gt.s32 	%p136, %r408, 3;
	@%p136 bra 	$L__BB20_241;
	setp.eq.b32 	%p139, %r408, 2;
	@%p139 bra 	$L__BB20_251;
	setp.eq.b32 	%p140, %r408, 3;
	@%p140 bra 	$L__BB20_240;
	bra.uni 	$L__BB20_254;
$L__BB20_240:
	cvt.s64.s16 	%rd461, %rd25;
	bra.uni 	$L__BB20_254;
$L__BB20_229:
	cvt.u16.u64 	%rs3, %rd25;
	cvt.s32.s16 	%r220, %rs3;
	and.b32 	%r410, %r220, -2147483648;
	bfe.u32 	%r37, %r35, 10, 5;
	setp.eq.b32 	%p143, %r37, 31;
	@%p143 bra 	$L__BB20_233;
	and.b32 	%r38, %r35, 1023;
	setp.ne.b32 	%p144, %r37, 0;
	@%p144 bra 	$L__BB20_234;
	setp.eq.b32 	%p145, %r38, 0;
	@%p145 bra 	$L__BB20_235;
	clz.b32 	%r223, %r38;
	xor.b32 	%r224, %r223, 31;
	sub.s32 	%r225, 9, %r224;
	shl.b32 	%r226, %r35, %r225;
	shl.b32 	%r227, %r224, 23;
	shl.b32 	%r228, %r226, 14;
	and.b32 	%r229, %r228, 8372224;
	add.s32 	%r230, %r227, %r410;
	add.s32 	%r231, %r230, %r229;
	add.s32 	%r410, %r231, 864026624;
	bra.uni 	$L__BB20_235;
$L__BB20_244:
	setp.gt.s32 	%p131, %r408, 8;
	@%p131 bra 	$L__BB20_248;
	setp.eq.b32 	%p134, %r408, 6;
	@%p134 bra 	$L__BB20_253;
	setp.eq.b32 	%p135, %r408, 7;
	@%p135 bra 	$L__BB20_247;
	bra.uni 	$L__BB20_254;
$L__BB20_247:
	shr.u64 	%rd461, %rd65, 32;
	bra.uni 	$L__BB20_254;
$L__BB20_241:
	setp.eq.b32 	%p137, %r408, 4;
	@%p137 bra 	$L__BB20_252;
	setp.eq.b32 	%p138, %r408, 5;
	@%p138 bra 	$L__BB20_243;
	bra.uni 	$L__BB20_254;
$L__BB20_243:
	and.b64 	%rd461, %rd26, 255;
	bra.uni 	$L__BB20_254;
$L__BB20_248:
	setp.eq.b32 	%p132, %r408, 9;
	mov.b64 	%rd464, %rd461;
	@%p132 bra 	$L__BB20_330;
	setp.ne.b32 	%p133, %r408, 10;
	@%p133 bra 	$L__BB20_254;
	{ .reg .b32 tmp; mov.b64 {tmp, %r23}, %rd65; }
	cvt.f64.f32 	%rd464, %r23;
	bra.uni 	$L__BB20_330;
$L__BB20_270:
	shl.b32 	%r238, %r40, 13;
	or.b32 	%r239, %r412, %r238;
	or.b32 	%r412, %r239, 2139095040;
	bra.uni 	$L__BB20_272;
$L__BB20_271:
	shl.b32 	%r249, %r41, 23;
	shl.b32 	%r250, %r42, 13;
	or.b32 	%r251, %r249, %r250;
	add.s32 	%r252, %r251, %r412;
	add.s32 	%r412, %r252, 939524096;
$L__BB20_272:
	cvt.f64.f32 	%rd465, %r412;
	bra.uni 	$L__BB20_296;
$L__BB20_233:
	shl.b32 	%r221, %r36, 13;
	or.b32 	%r222, %r410, %r221;
	or.b32 	%r410, %r222, 2139095040;
	bra.uni 	$L__BB20_235;
$L__BB20_234:
	shl.b32 	%r232, %r37, 23;
	shl.b32 	%r233, %r38, 13;
	or.b32 	%r234, %r232, %r233;
	add.s32 	%r235, %r234, %r410;
)QPTX";
        result += R"QPTX(
	add.s32 	%r410, %r235, 939524096;
$L__BB20_235:
	cvt.f64.f32 	%rd464, %r410;
	bra.uni 	$L__BB20_330;
$L__BB20_290:
	shl.b64 	%rd218, %rd27, 3;
	add.s64 	%rd219, %rd61, %rd218;
	ld.b64 	%rd462, [%rd219];
	bra.uni 	$L__BB20_295;
$L__BB20_291:
	shl.b64 	%rd215, %rd27, 1;
	add.s64 	%rd216, %rd61, %rd215;
	ld.s16 	%rd462, [%rd216];
	bra.uni 	$L__BB20_295;
$L__BB20_293:
	shl.b64 	%rd208, %rd27, 2;
	add.s64 	%rd209, %rd61, %rd208;
	ld.b32 	%rd462, [%rd209];
	bra.uni 	$L__BB20_295;
$L__BB20_292:
	add.s64 	%rd212, %rd61, %rd27;
	ld.b8 	%rd462, [%rd212];
	bra.uni 	$L__BB20_295;
$L__BB20_289:
	shl.b64 	%rd220, %rd27, 3;
	add.s64 	%rd221, %rd61, %rd220;
	ld.b64 	%rd465, [%rd221];
	bra.uni 	$L__BB20_296;
$L__BB20_294:
	shl.b64 	%rd224, %rd27, 3;
	add.s64 	%rd225, %rd61, %rd224;
	ld.b64 	%rd462, [%rd225];
$L__BB20_295:
	setp.lt.s32 	%p159, %r411, 5;
	cvt.rn.f64.s64 	%rd226, %rd462;
	cvt.rn.f64.u64 	%rd227, %rd462;
	selp.f64 	%rd465, %rd226, %rd227, %p159;
$L__BB20_296:
	@%p92 bra 	$L__BB20_330;
	@%p146 bra 	$L__BB20_307;
	shl.b64 	%rd250, %rd27, 1;
	add.s64 	%rd251, %rd61, %rd250;
	ld.b16 	%rs7, [%rd251+2];
	setp.ne.b32 	%p177, %r411, 13;
	cvt.u32.u16 	%r43, %rs7;
	@%p177 bra 	$L__BB20_300;
	shl.b32 	%r413, %r43, 16;
	bra.uni 	$L__BB20_306;
$L__BB20_307:
	setp.gt.s32 	%p164, %r411, 4;
	@%p164 bra 	$L__BB20_315;
	bra.uni 	$L__BB20_308;
$L__BB20_315:
	setp.gt.s32 	%p165, %r411, 6;
	@%p165 bra 	$L__BB20_319;
	bra.uni 	$L__BB20_316;
$L__BB20_319:
	setp.eq.b32 	%p166, %r411, 7;
	@%p166 bra 	$L__BB20_327;
	setp.eq.b32 	%p167, %r411, 9;
	@%p167 bra 	$L__BB20_323;
	setp.ne.b32 	%p168, %r411, 10;
	@%p168 bra 	$L__BB20_328;
	shl.b64 	%rd244, %rd27, 2;
	add.s64 	%rd245, %rd61, %rd244;
	ld.b32 	%r253, [%rd245+4];
	cvt.f64.f32 	%rd464, %r253;
	bra.uni 	$L__BB20_330;
$L__BB20_300:
	cvt.s32.s16 	%r254, %rs7;
	and.b32 	%r413, %r254, -2147483648;
	bfe.u32 	%r44, %r43, 10, 5;
	setp.eq.b32 	%p178, %r44, 31;
	@%p178 bra 	$L__BB20_304;
	and.b32 	%r45, %r43, 1023;
	setp.ne.b32 	%p179, %r44, 0;
	@%p179 bra 	$L__BB20_305;
	setp.eq.b32 	%p180, %r45, 0;
	@%p180 bra 	$L__BB20_306;
	clz.b32 	%r257, %r45;
	xor.b32 	%r258, %r257, 31;
	sub.s32 	%r259, 9, %r258;
	shl.b32 	%r260, %r43, %r259;
	shl.b32 	%r261, %r258, 23;
	shl.b32 	%r262, %r260, 14;
	and.b32 	%r263, %r262, 8372224;
	add.s32 	%r264, %r261, %r413;
	add.s32 	%r265, %r264, %r263;
	add.s32 	%r413, %r265, 864026624;
	bra.uni 	$L__BB20_306;
$L__BB20_308:
	setp.gt.s32 	%p171, %r411, 2;
	@%p171 bra 	$L__BB20_312;
	setp.eq.b32 	%p174, %r411, 1;
	@%p174 bra 	$L__BB20_324;
	setp.eq.b32 	%p175, %r411, 2;
	@%p175 bra 	$L__BB20_311;
	bra.uni 	$L__BB20_328;
$L__BB20_311:
	add.s64 	%rd239, %rd61, %rd27;
	ld.s8 	%rd463, [%rd239+1];
	bra.uni 	$L__BB20_329;
$L__BB20_312:
	setp.eq.b32 	%p172, %r411, 3;
	@%p172 bra 	$L__BB20_325;
	setp.eq.b32 	%p173, %r411, 4;
	@%p173 bra 	$L__BB20_314;
	bra.uni 	$L__BB20_328;
$L__BB20_314:
	shl.b64 	%rd235, %rd27, 2;
	add.s64 	%rd236, %rd61, %rd235;
	ld.s32 	%rd463, [%rd236+4];
	bra.uni 	$L__BB20_329;
$L__BB20_316:
	setp.eq.b32 	%p169, %r411, 5;
	@%p169 bra 	$L__BB20_326;
	setp.eq.b32 	%p170, %r411, 6;
	@%p170 bra 	$L__BB20_318;
	bra.uni 	$L__BB20_328;
$L__BB20_318:
	shl.b64 	%rd232, %rd27, 1;
	add.s64 	%rd233, %rd61, %rd232;
	ld.b16 	%rd463, [%rd233+2];
	bra.uni 	$L__BB20_329;
$L__BB20_251:
	cvt.s64.s8 	%rd461, %rd26;
	bra.uni 	$L__BB20_254;
$L__BB20_253:
	and.b64 	%rd461, %rd25, 65535;
	bra.uni 	$L__BB20_254;
$L__BB20_252:
	shr.s64 	%rd461, %rd65, 32;
$L__BB20_254:
	setp.lt.s32 	%p141, %r408, 5;
	cvt.rn.f64.s64 	%rd206, %rd461;
	cvt.rn.f64.u64 	%rd207, %rd461;
	selp.f64 	%rd464, %rd206, %rd207, %p141;
	bra.uni 	$L__BB20_330;
$L__BB20_304:
	shl.b32 	%r255, %r43, 13;
	or.b32 	%r256, %r413, %r255;
	or.b32 	%r413, %r256, 2139095040;
	bra.uni 	$L__BB20_306;
$L__BB20_305:
	shl.b32 	%r266, %r44, 23;
	shl.b32 	%r267, %r45, 13;
	or.b32 	%r268, %r266, %r267;
	add.s32 	%r269, %r268, %r413;
	add.s32 	%r413, %r269, 939524096;
$L__BB20_306:
	cvt.f64.f32 	%rd464, %r413;
	bra.uni 	$L__BB20_330;
$L__BB20_324:
	shl.b64 	%rd240, %rd27, 3;
	add.s64 	%rd241, %rd61, %rd240;
	ld.b64 	%rd463, [%rd241+8];
	bra.uni 	$L__BB20_329;
$L__BB20_325:
	shl.b64 	%rd237, %rd27, 1;
	add.s64 	%rd238, %rd61, %rd237;
	ld.s16 	%rd463, [%rd238+2];
	bra.uni 	$L__BB20_329;
$L__BB20_327:
	shl.b64 	%rd230, %rd27, 2;
	add.s64 	%rd231, %rd61, %rd230;
	ld.b32 	%rd463, [%rd231+4];
	bra.uni 	$L__BB20_329;
$L__BB20_326:
	add.s64 	%rd234, %rd61, %rd27;
	ld.b8 	%rd463, [%rd234+1];
	bra.uni 	$L__BB20_329;
$L__BB20_323:
	shl.b64 	%rd242, %rd27, 3;
	add.s64 	%rd243, %rd61, %rd242;
	ld.b64 	%rd464, [%rd243+8];
	bra.uni 	$L__BB20_330;
$L__BB20_328:
	shl.b64 	%rd246, %rd27, 3;
	add.s64 	%rd247, %rd61, %rd246;
	ld.b64 	%rd463, [%rd247+8];
$L__BB20_329:
	setp.lt.s32 	%p176, %r411, 5;
	cvt.rn.f64.s64 	%rd248, %rd463;
	cvt.rn.f64.u64 	%rd249, %rd463;
	selp.f64 	%rd464, %rd248, %rd249, %p176;
$L__BB20_330:
	setp.ne.b32 	%p181, %r84, 1;
	mov.b64 	%rd466, %rd464;
	mov.b64 	%rd28, %rd465;
	mov.b64 	%rd29, %rd457;
	mov.b64 	%rd30, %rd459;
	@%p181 bra 	$L__BB20_332;
	mov.b64 	%rd466, %rd459;
	mov.b64 	%rd28, %rd457;
	mov.b64 	%rd29, %rd465;
	mov.b64 	%rd30, %rd464;
$L__BB20_332:
	ld.param.b64 	%rd67, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_14];
	ld.param.b32 	%r83, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_11];
	setp.gt.s32 	%p182, %r85, 2;
	@%p182 bra 	$L__BB20_337;
	setp.eq.b32 	%p185, %r85, 0;
	@%p185 bra 	$L__BB20_341;
	setp.eq.b32 	%p186, %r85, 1;
	@%p186 bra 	$L__BB20_335;
	bra.uni 	$L__BB20_442;
$L__BB20_335:
	@%p328 bra 	$L__BB20_388;
	mov.b32 	%r417, 12;
	@%p331 bra 	$L__BB20_392;
	mov.b32 	%r417, %r82;
	@%p332 bra 	$L__BB20_387;
	bra.uni 	$L__BB20_392;
$L__BB20_387:
	mov.b32 	%r417, 13;
	bra.uni 	$L__BB20_392;
$L__BB20_337:
	setp.eq.b32 	%p183, %r85, 3;
	@%p183 bra 	$L__BB20_339;
	setp.eq.b32 	%p184, %r85, 10;
	@%p184 bra 	$L__BB20_339;
	bra.uni 	$L__BB20_442;
$L__BB20_339:
	setp.gt.s32 	%p189, %r83, 2;
	@%p189 bra 	$L__BB20_431;
	bra.uni 	$L__BB20_340;
$L__BB20_431:
	setp.eq.b32 	%p190, %r83, 3;
	@%p190 bra 	$L__BB20_435;
	setp.eq.b32 	%p191, %r83, 4;
	@%p191 bra 	$L__BB20_436;
	setp.eq.b32 	%p192, %r83, 5;
	@%p192 bra 	$L__BB20_434;
	bra.uni 	$L__BB20_437;
$L__BB20_434:
	setp.gt.f64 	%p333, %rd29, %rd28;
	bra.uni 	$L__BB20_438;
$L__BB20_442:
	add.s32 	%r360, %r85, -5;
	setp.gt.u32 	%p278, %r360, 1;
	@%p278 bra 	$L__BB20_552;
	@%p328 bra 	$L__BB20_447;
	mov.b32 	%r420, 12;
	@%p331 bra 	$L__BB20_451;
	mov.b32 	%r420, %r82;
	@%p332 bra 	$L__BB20_446;
	bra.uni 	$L__BB20_451;
$L__BB20_446:
	mov.b32 	%r420, 13;
	bra.uni 	$L__BB20_451;
$L__BB20_341:
	st.local.b64 	[%rd2], %rd29;
	st.local.b64 	[%rd2+8], %rd30;
	st.local.b64 	[%rd3], %rd28;
	st.local.b64 	[%rd3+8], %rd466;
	{
	.param .align 8 .b8 	param0[16];
	.param .align 8 .b8 	param1[16];
	.param .b32 	param2;
	.param .b32 	param3;
	.param .b64 	param4;
	.param .align 8 .b8 	retval0[16];
	st.param.b64 	[param4], %rd67;
	st.param.b32 	[param3], %r83;
	st.param.b32 	[param2], %r82;
	cvta.to.local.u64 	%rd313, %rd70;
	ld.local.b64 	%rd314, [%rd313+8];
	st.param.b64 	[param1+8], %rd314;
	ld.local.b64 	%rd315, [%rd313];
	st.param.b64 	[param1], %rd315;
	cvta.to.local.u64 	%rd316, %rd69;
	ld.local.b64 	%rd317, [%rd316+8];
	st.param.b64 	[param0+8], %rd317;
	ld.local.b64 	%rd318, [%rd316];
	st.param.b64 	[param0], %rd318;
	call.uni (retval0), _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj, (param0, param1, param2, param3, param4);
	ld.param.b64 	%rd319, [retval0+8];
	ld.param.b64 	%rd320, [retval0];
	}
	@%p328 bra 	$L__BB20_345;
	mov.b32 	%r414, 12;
	@%p331 bra 	$L__BB20_349;
	mov.b32 	%r414, %r82;
	@%p332 bra 	$L__BB20_344;
	bra.uni 	$L__BB20_349;
$L__BB20_344:
	mov.b32 	%r414, 13;
	bra.uni 	$L__BB20_349;
$L__BB20_340:
	setp.eq.f64 	%p187, %rd465, %rd457;
	setp.eq.f64 	%p188, %rd464, %rd459;
	and.pred 	%p333, %p187, %p188;
	setp.eq.b32 	%p193, %r83, 1;
	@%p193 bra 	$L__BB20_438;
	setp.eq.b32 	%p194, %r83, 2;
	@%p194 bra 	$L__BB20_430;
	bra.uni 	$L__BB20_437;
$L__BB20_430:
	not.pred 	%p333, %p333;
	bra.uni 	$L__BB20_438;
$L__BB20_388:
	@%p329 bra 	$L__BB20_391;
	mov.b32 	%r417, %r82;
	@%p330 bra 	$L__BB20_392;
	mov.b32 	%r417, 9;
	bra.uni 	$L__BB20_392;
$L__BB20_345:
	@%p329 bra 	$L__BB20_348;
	mov.b32 	%r414, %r82;
	@%p330 bra 	$L__BB20_349;
	mov.b32 	%r414, 9;
	bra.uni 	$L__BB20_349;
$L__BB20_435:
	setp.lt.f64 	%p333, %rd29, %rd28;
	bra.uni 	$L__BB20_438;
$L__BB20_436:
	setp.le.f64 	%p333, %rd29, %rd28;
	bra.uni 	$L__BB20_438;
$L__BB20_437:
	setp.ge.f64 	%p333, %rd29, %rd28;
$L__BB20_438:
	setp.ne.b32 	%p195, %r85, 3;
	@%p195 bra 	$L__BB20_440;
	selp.b16 	%rs10, 1, 0, %p333;
	add.s64 	%rd252, %rd58, %rd66;
	st.b8 	[%rd252], %rs10;
	bra.uni 	$L__BB20_552;
$L__BB20_440:
	@%p333 bra 	$L__BB20_552;
	mov.b32 	%r271, 1;
	atom.global.or.b32 %r270, [%rd67], %r271;
	bra.uni 	$L__BB20_552;
$L__BB20_447:
	@%p329 bra 	$L__BB20_450;
	mov.b32 	%r420, %r82;
	@%p330 bra 	$L__BB20_451;
	mov.b32 	%r420, 9;
	bra.uni 	$L__BB20_451;
$L__BB20_391:
	mov.b32 	%r417, 10;
$L__BB20_392:
	neg.f64 	%rd43, %rd29;
	and.b32 	%r61, %r417, -2;
	setp.ne.b32 	%p196, %r61, 12;
	@%p196 bra 	$L__BB20_407;
	shr.u64 	%rd46, %rd43, 48;
	cvt.u32.u64 	%r273, %rd46;
	and.b32 	%r62, %r273, 32768;
	shr.u64 	%rd257, %rd43, 52;
	cvt.u32.u64 	%r274, %rd257;
	and.b32 	%r63, %r274, 2047;
	setp.eq.b32 	%p199, %r63, 0;
	@%p199 bra 	$L__BB20_396;
	and.b64 	%rd45, %rd43, 4503599627370495;
	setp.eq.b32 	%p198, %r417, 12;
	selp.b32 	%r64, 11, 8, %p198;
	selp.b32 	%r418, 31744, 32640, %p198;
	setp.ne.b32 	%p200, %r63, 2047;
	@%p200 bra 	$L__BB20_397;
	setp.eq.b64 	%p201, %rd45, 0;
	add.s32 	%r275, %r64, -2;
	mov.b32 	%r276, 1;
	shl.b32 	%r277, %r276, %r275;
	selp.b32 	%r278, 0, %r277, %p201;
	or.b32 	%r279, %r62, %r278;
	or.b32 	%r280, %r279, %r418;
	cvt.u16.u32 	%rs15, %r280;
	bra.uni 	$L__BB20_406;
$L__BB20_407:
	setp.ne.b32 	%p197, %r417, 10;
	@%p197 bra 	$L__BB20_409;
	cvt.rn.f32.f64 	%r272, %rd43;
	shl.b64 	%rd255, %rd27, 2;
	add.s64 	%rd256, %rd58, %rd255;
	st.b32 	[%rd256], %r272;
	bra.uni 	$L__BB20_410;
$L__BB20_409:
	shl.b64 	%rd253, %rd27, 3;
	add.s64 	%rd254, %rd58, %rd253;
	st.b64 	[%rd254], %rd43;
	bra.uni 	$L__BB20_410;
$L__BB20_348:
	mov.b32 	%r414, 10;
$L__BB20_349:
	and.b32 	%r46, %r414, -2;
	setp.ne.b32 	%p237, %r46, 12;
	@%p237 bra 	$L__BB20_364;
	shr.u64 	%rd32, %rd320, 48;
	cvt.u32.u64 	%r317, %rd32;
	and.b32 	%r47, %r317, 32768;
	shr.u64 	%rd325, %rd320, 52;
	cvt.u32.u64 	%r318, %rd325;
	and.b32 	%r48, %r318, 2047;
	setp.eq.b32 	%p240, %r48, 0;
	@%p240 bra 	$L__BB20_353;
	and.b64 	%rd31, %rd320, 4503599627370495;
	setp.eq.b32 	%p239, %r414, 12;
	selp.b32 	%r49, 11, 8, %p239;
	selp.b32 	%r415, 31744, 32640, %p239;
	setp.ne.b32 	%p241, %r48, 2047;
	@%p241 bra 	$L__BB20_354;
	setp.eq.b64 	%p242, %rd31, 0;
	add.s32 	%r319, %r49, -2;
	mov.b32 	%r320, 1;
	shl.b32 	%r321, %r320, %r319;
	selp.b32 	%r322, 0, %r321, %p242;
	or.b32 	%r323, %r47, %r322;
	or.b32 	%r324, %r323, %r415;
	cvt.u16.u32 	%rs13, %r324;
	bra.uni 	$L__BB20_363;
$L__BB20_364:
	setp.ne.b32 	%p238, %r414, 10;
	@%p238 bra 	$L__BB20_366;
	cvt.rn.f32.f64 	%r316, %rd320;
	shl.b64 	%rd323, %rd27, 2;
	add.s64 	%rd324, %rd58, %rd323;
	st.b32 	[%rd324], %r316;
	bra.uni 	$L__BB20_367;
$L__BB20_366:
	shl.b64 	%rd321, %rd27, 3;
	add.s64 	%rd322, %rd58, %rd321;
	st.b64 	[%rd322], %rd320;
	bra.uni 	$L__BB20_367;
$L__BB20_396:
	cvt.u16.u32 	%rs15, %r62;
	bra.uni 	$L__BB20_406;
$L__BB20_353:
	cvt.u16.u32 	%rs13, %r47;
	bra.uni 	$L__BB20_363;
$L__BB20_397:
	selp.b32 	%r281, -14, -126, %p198;
	add.s32 	%r66, %r63, -1023;
	or.b64 	%rd47, %rd45, 4503599627370496;
	setp.ge.s32 	%p202, %r66, %r281;
	@%p202 bra 	$L__BB20_403;
	and.b64 	%rd48, %rd46, 32768;
	selp.b32 	%r291, 28, -81, %p198;
	sub.s32 	%r67, %r291, %r66;
	setp.gt.s32 	%p210, %r67, 0;
	@%p210 bra 	$L__BB20_400;
	bra.uni 	$L__BB20_399;
$L__BB20_400:
	setp.gt.u32 	%p211, %r67, 63;
	mov.b64 	%rd469, 0;
	@%p211 bra 	$L__BB20_402;
	shr.u64 	%rd271, %rd47, %r67;
	mov.b64 	%rd272, -1;
	shl.b64 	%rd273, %rd272, %r67;
	not.b64 	%rd274, %rd273;
	and.b64 	%rd275, %rd47, %rd274;
	add.s32 	%r292, %r67, -1;
	mov.b64 	%rd276, 1;
	shl.b64 	%rd277, %rd276, %r292;
	setp.gt.u64 	%p212, %rd275, %rd277;
	setp.eq.b64 	%p213, %rd275, %rd277;
	and.b64 	%rd278, %rd271, 1;
	setp.ne.b64 	%p214, %rd278, 0;
	and.pred 	%p215, %p213, %p214;
	or.pred 	%p216, %p212, %p215;
	selp.b64 	%rd279, 1, 0, %p216;
	add.s64 	%rd469, %rd271, %rd279;
	bra.uni 	$L__BB20_402;
$L__BB20_354:
	selp.b32 	%r325, -14, -126, %p239;
	add.s32 	%r51, %r48, -1023;
	or.b64 	%rd33, %rd31, 4503599627370496;
	setp.ge.s32 	%p243, %r51, %r325;
	@%p243 bra 	$L__BB20_360;
	and.b64 	%rd34, %rd32, 32768;
	selp.b32 	%r335, 28, -81, %p239;
	sub.s32 	%r52, %r335, %r51;
	setp.gt.s32 	%p251, %r52, 0;
	@%p251 bra 	$L__BB20_357;
	bra.uni 	$L__BB20_356;
$L__BB20_357:
	setp.gt.u32 	%p252, %r52, 63;
	mov.b64 	%rd467, 0;
	@%p252 bra 	$L__BB20_359;
	shr.u64 	%rd339, %rd33, %r52;
	mov.b64 	%rd340, -1;
	shl.b64 	%rd341, %rd340, %r52;
	not.b64 	%rd342, %rd341;
	and.b64 	%rd343, %rd33, %rd342;
	add.s32 	%r336, %r52, -1;
	mov.b64 	%rd344, 1;
	shl.b64 	%rd345, %rd344, %r336;
	setp.gt.u64 	%p253, %rd343, %rd345;
	setp.eq.b64 	%p254, %rd343, %rd345;
	and.b64 	%rd346, %rd339, 1;
	setp.ne.b64 	%p255, %rd346, 0;
	and.pred 	%p256, %p254, %p255;
	or.pred 	%p257, %p253, %p256;
	selp.b64 	%rd347, 1, 0, %p257;
	add.s64 	%rd467, %rd339, %rd347;
	bra.uni 	$L__BB20_359;
$L__BB20_450:
	mov.b32 	%r420, 10;
$L__BB20_451:
	and.b32 	%r361, %r420, -2;
	setp.ne.b32 	%p279, %r361, 12;
	@%p279 bra 	$L__BB20_461;
	shl.b64 	%rd401, %rd27, 1;
	add.s64 	%rd402, %rd62, %rd401;
	ld.b16 	%rs8, [%rd402];
	setp.ne.b32 	%p293, %r420, 13;
	cvt.u32.u16 	%r76, %rs8;
	@%p293 bra 	$L__BB20_454;
	shl.b32 	%r421, %r76, 16;
	bra.uni 	$L__BB20_460;
$L__BB20_461:
	setp.gt.s32 	%p280, %r420, 4;
	@%p280 bra 	$L__BB20_469;
	bra.uni 	$L__BB20_462;
$L__BB20_469:
	setp.gt.s32 	%p281, %r420, 6;
	@%p281 bra 	$L__BB20_473;
	bra.uni 	$L__BB20_470;
$L__BB20_473:
	setp.eq.b32 	%p282, %r420, 7;
	@%p282 bra 	$L__BB20_481;
	setp.eq.b32 	%p283, %r420, 9;
	@%p283 bra 	$L__BB20_477;
	setp.ne.b32 	%p284, %r420, 10;
	@%p284 bra 	$L__BB20_482;
	shl.b64 	%rd395, %rd27, 2;
	add.s64 	%rd396, %rd62, %rd395;
	ld.b32 	%r362, [%rd396];
	cvt.f64.f32 	%rd472, %r362;
	bra.uni 	$L__BB20_484;
$L__BB20_454:
	cvt.s32.s16 	%r363, %rs8;
	and.b32 	%r421, %r363, -2147483648;
	bfe.u32 	%r77, %r76, 10, 5;
	setp.eq.b32 	%p294, %r77, 31;
	@%p294 bra 	$L__BB20_458;
	and.b32 	%r78, %r76, 1023;
	setp.ne.b32 	%p295, %r77, 0;
	@%p295 bra 	$L__BB20_459;
	setp.eq.b32 	%p296, %r78, 0;
	@%p296 bra 	$L__BB20_460;
	clz.b32 	%r366, %r78;
	xor.b32 	%r367, %r366, 31;
	sub.s32 	%r368, 9, %r367;
	shl.b32 	%r369, %r76, %r368;
	shl.b32 	%r370, %r367, 23;
	shl.b32 	%r371, %r369, 14;
	and.b32 	%r372, %r371, 8372224;
	add.s32 	%r373, %r370, %r421;
	add.s32 	%r374, %r373, %r372;
	add.s32 	%r421, %r374, 864026624;
	bra.uni 	$L__BB20_460;
$L__BB20_462:
	setp.gt.s32 	%p287, %r420, 2;
	@%p287 bra 	$L__BB20_466;
	setp.eq.b32 	%p290, %r420, 1;
	@%p290 bra 	$L__BB20_478;
	setp.eq.b32 	%p291, %r420, 2;
	@%p291 bra 	$L__BB20_465;
	bra.uni 	$L__BB20_482;
$L__BB20_465:
	add.s64 	%rd390, %rd62, %rd27;
	ld.s8 	%rd471, [%rd390];
	bra.uni 	$L__BB20_483;
$L__BB20_403:
	selp.b32 	%r65, 15, 127, %p198;
	sub.s32 	%r282, 53, %r64;
	shr.u64 	%rd258, %rd47, %r282;
	mov.b64 	%rd259, -1;
	shl.b64 	%rd260, %rd259, %r282;
	not.b64 	%rd261, %rd260;
	and.b64 	%rd262, %rd261, %rd43;
	sub.s32 	%r283, 52, %r64;
	mov.b64 	%rd263, 1;
	shl.b64 	%rd264, %rd263, %r283;
	setp.gt.u64 	%p203, %rd262, %rd264;
	setp.eq.b64 	%p204, %rd262, %rd264;
	and.b64 	%rd265, %rd258, 1;
	setp.ne.b64 	%p205, %rd265, 0;
	and.pred 	%p206, %p204, %p205;
	or.pred 	%p207, %p203, %p206;
	selp.b64 	%rd266, 1, 0, %p207;
	add.s64 	%rd49, %rd258, %rd266;
	shl.b64 	%rd50, %rd263, %r64;
	setp.eq.b64 	%p208, %rd49, %rd50;
	add.s32 	%r284, %r63, -1022;
	selp.b32 	%r68, %r284, %r66, %p208;
	setp.gt.s32 	%p209, %r68, %r65;
	@%p209 bra 	$L__BB20_405;
	selp.b32 	%r285, 1, 0, %p208;
	shr.u64 	%rd267, %rd49, %r285;
	add.s32 	%r286, %r68, %r65;
	add.s32 	%r287, %r64, -1;
	shl.b32 	%r288, %r286, %r287;
	shl.b64 	%rd268, %rd259, %r287;
	not.b64 	%rd269, %rd268;
	and.b64 	%rd270, %rd267, %rd269;
	cvt.u32.u64 	%r289, %rd270;
	or.b32 	%r418, %r288, %r289;
$L__BB20_405:
	or.b32 	%r290, %r418, %r62;
	cvt.u16.u32 	%rs15, %r290;
	bra.uni 	$L__BB20_406;
$L__BB20_360:
	selp.b32 	%r50, 15, 127, %p239;
	sub.s32 	%r326, 53, %r49;
	shr.u64 	%rd326, %rd33, %r326;
	mov.b64 	%rd327, -1;
	shl.b64 	%rd328, %rd327, %r326;
	not.b64 	%rd329, %rd328;
	and.b64 	%rd330, %rd329, %rd320;
	sub.s32 	%r327, 52, %r49;
	mov.b64 	%rd331, 1;
	shl.b64 	%rd332, %rd331, %r327;
	setp.gt.u64 	%p244, %rd330, %rd332;
	setp.eq.b64 	%p245, %rd330, %rd332;
	and.b64 	%rd333, %rd326, 1;
	setp.ne.b64 	%p246, %rd333, 0;
	and.pred 	%p247, %p245, %p246;
	or.pred 	%p248, %p244, %p247;
	selp.b64 	%rd334, 1, 0, %p248;
	add.s64 	%rd35, %rd326, %rd334;
	shl.b64 	%rd36, %rd331, %r49;
	setp.eq.b64 	%p249, %rd35, %rd36;
	add.s32 	%r328, %r48, -1022;
	selp.b32 	%r53, %r328, %r51, %p249;
	setp.gt.s32 	%p250, %r53, %r50;
	@%p250 bra 	$L__BB20_362;
	selp.b32 	%r329, 1, 0, %p249;
	shr.u64 	%rd335, %rd35, %r329;
	add.s32 	%r330, %r53, %r50;
	add.s32 	%r331, %r49, -1;
	shl.b32 	%r332, %r330, %r331;
	shl.b64 	%rd336, %rd327, %r331;
	not.b64 	%rd337, %rd336;
	and.b64 	%rd338, %rd335, %rd337;
	cvt.u32.u64 	%r333, %rd338;
	or.b32 	%r415, %r332, %r333;
$L__BB20_362:
	or.b32 	%r334, %r415, %r47;
	cvt.u16.u32 	%rs13, %r334;
	bra.uni 	$L__BB20_363;
$L__BB20_466:
	setp.eq.b32 	%p288, %r420, 3;
	@%p288 bra 	$L__BB20_479;
	setp.eq.b32 	%p289, %r420, 4;
	@%p289 bra 	$L__BB20_468;
	bra.uni 	$L__BB20_482;
$L__BB20_468:
	shl.b64 	%rd386, %rd27, 2;
	add.s64 	%rd387, %rd62, %rd386;
	ld.s32 	%rd471, [%rd387];
	bra.uni 	$L__BB20_483;
$L__BB20_470:
	setp.eq.b32 	%p285, %r420, 5;
	@%p285 bra 	$L__BB20_480;
	setp.eq.b32 	%p286, %r420, 6;
	@%p286 bra 	$L__BB20_472;
	bra.uni 	$L__BB20_482;
$L__BB20_472:
	shl.b64 	%rd383, %rd27, 1;
	add.s64 	%rd384, %rd62, %rd383;
	ld.b16 	%rd471, [%rd384];
	bra.uni 	$L__BB20_483;
$L__BB20_458:
	shl.b32 	%r364, %r76, 13;
	or.b32 	%r365, %r421, %r364;
	or.b32 	%r421, %r365, 2139095040;
	bra.uni 	$L__BB20_460;
$L__BB20_459:
	shl.b32 	%r375, %r77, 23;
	shl.b32 	%r376, %r78, 13;
	or.b32 	%r377, %r375, %r376;
	add.s32 	%r378, %r377, %r421;
	add.s32 	%r421, %r378, 939524096;
$L__BB20_460:
	cvt.f64.f32 	%rd472, %r421;
	bra.uni 	$L__BB20_484;
$L__BB20_399:
	neg.s32 	%r293, %r67;
	shl.b64 	%rd469, %rd47, %r293;
$L__BB20_402:
	or.b64 	%rd280, %rd469, %rd48;
	cvt.u16.u64 	%rs15, %rd280;
$L__BB20_406:
	shl.b64 	%rd281, %rd27, 1;
	add.s64 	%rd282, %rd58, %rd281;
	st.b16 	[%rd282], %rs15;
$L__BB20_410:
	@%p92 bra 	$L__BB20_552;
	neg.f64 	%rd44, %rd30;
	@%p196 bra 	$L__BB20_426;
	shr.u64 	%rd52, %rd44, 48;
	cvt.u32.u64 	%r295, %rd52;
	and.b32 	%r69, %r295, 32768;
	shr.u64 	%rd287, %rd44, 52;
	cvt.u32.u64 	%r296, %rd287;
	and.b32 	%r70, %r296, 2047;
	setp.eq.b32 	%p219, %r70, 0;
	@%p219 bra 	$L__BB20_415;
	and.b64 	%rd51, %rd44, 4503599627370495;
	setp.eq.b32 	%p218, %r417, 12;
	selp.b32 	%r71, 11, 8, %p218;
	selp.b32 	%r419, 31744, 32640, %p218;
	setp.ne.b32 	%p220, %r70, 2047;
	@%p220 bra 	$L__BB20_416;
	setp.eq.b64 	%p221, %rd51, 0;
	add.s32 	%r297, %r71, -2;
	mov.b32 	%r298, 1;
	shl.b32 	%r299, %r298, %r297;
	selp.b32 	%r300, 0, %r299, %p221;
	or.b32 	%r301, %r69, %r300;
	or.b32 	%r302, %r301, %r419;
	cvt.u16.u32 	%rs16, %r302;
	bra.uni 	$L__BB20_425;
$L__BB20_426:
	setp.ne.b32 	%p217, %r417, 10;
	@%p217 bra 	$L__BB20_428;
	cvt.rn.f32.f64 	%r294, %rd44;
	shl.b64 	%rd285, %rd27, 2;
	add.s64 	%rd286, %rd58, %rd285;
	st.b32 	[%rd286+4], %r294;
	bra.uni 	$L__BB20_552;
$L__BB20_428:
	shl.b64 	%rd283, %rd27, 3;
	add.s64 	%rd284, %rd58, %rd283;
	st.b64 	[%rd284+8], %rd44;
	bra.uni 	$L__BB20_552;
$L__BB20_415:
	cvt.u16.u32 	%rs16, %r69;
	bra.uni 	$L__BB20_425;
$L__BB20_416:
	selp.b32 	%r303, -14, -126, %p218;
	add.s32 	%r73, %r70, -1023;
	or.b64 	%rd53, %rd51, 4503599627370496;
	setp.ge.s32 	%p222, %r73, %r303;
	@%p222 bra 	$L__BB20_422;
	and.b64 	%rd54, %rd52, 32768;
	selp.b32 	%r313, 28, -81, %p218;
	sub.s32 	%r74, %r313, %r73;
	setp.gt.s32 	%p230, %r74, 0;
	@%p230 bra 	$L__BB20_419;
	bra.uni 	$L__BB20_418;
$L__BB20_419:
	setp.gt.u32 	%p231, %r74, 63;
	mov.b64 	%rd470, 0;
	@%p231 bra 	$L__BB20_421;
	shr.u64 	%rd301, %rd53, %r74;
	mov.b64 	%rd302, -1;
	shl.b64 	%rd303, %rd302, %r74;
	not.b64 	%rd304, %rd303;
	and.b64 	%rd305, %rd53, %rd304;
	add.s32 	%r314, %r74, -1;
	mov.b64 	%rd306, 1;
	shl.b64 	%rd307, %rd306, %r314;
	setp.gt.u64 	%p232, %rd305, %rd307;
	setp.eq.b64 	%p233, %rd305, %rd307;
	and.b64 	%rd308, %rd301, 1;
	setp.ne.b64 	%p234, %rd308, 0;
	and.pred 	%p235, %p233, %p234;
	or.pred 	%p236, %p232, %p235;
	selp.b64 	%rd309, 1, 0, %p236;
	add.s64 	%rd470, %rd301, %rd309;
	bra.uni 	$L__BB20_421;
$L__BB20_422:
	selp.b32 	%r72, 15, 127, %p218;
	sub.s32 	%r304, 53, %r71;
	shr.u64 	%rd288, %rd53, %r304;
	mov.b64 	%rd289, -1;
	shl.b64 	%rd290, %rd289, %r304;
	not.b64 	%rd291, %rd290;
	and.b64 	%rd292, %rd291, %rd44;
	sub.s32 	%r305, 52, %r71;
	mov.b64 	%rd293, 1;
	shl.b64 	%rd294, %rd293, %r305;
	setp.gt.u64 	%p223, %rd292, %rd294;
	setp.eq.b64 	%p224, %rd292, %rd294;
	and.b64 	%rd295, %rd288, 1;
	setp.ne.b64 	%p225, %rd295, 0;
	and.pred 	%p226, %p224, %p225;
	or.pred 	%p227, %p223, %p226;
	selp.b64 	%rd296, 1, 0, %p227;
	add.s64 	%rd55, %rd288, %rd296;
	shl.b64 	%rd56, %rd293, %r71;
	setp.eq.b64 	%p228, %rd55, %rd56;
	add.s32 	%r306, %r70, -1022;
	selp.b32 	%r75, %r306, %r73, %p228;
	setp.gt.s32 	%p229, %r75, %r72;
	@%p229 bra 	$L__BB20_424;
	selp.b32 	%r307, 1, 0, %p228;
	shr.u64 	%rd297, %rd55, %r307;
	add.s32 	%r308, %r75, %r72;
	add.s32 	%r309, %r71, -1;
	shl.b32 	%r310, %r308, %r309;
	shl.b64 	%rd298, %rd289, %r309;
	not.b64 	%rd299, %rd298;
	and.b64 	%rd300, %rd297, %rd299;
	cvt.u32.u64 	%r311, %rd300;
	or.b32 	%r419, %r310, %r311;
$L__BB20_424:
	or.b32 	%r312, %r419, %r69;
	cvt.u16.u32 	%rs16, %r312;
	bra.uni 	$L__BB20_425;
$L__BB20_356:
	neg.s32 	%r337, %r52;
	shl.b64 	%rd467, %rd33, %r337;
$L__BB20_359:
	or.b64 	%rd348, %rd467, %rd34;
	cvt.u16.u64 	%rs13, %rd348;
$L__BB20_363:
	shl.b64 	%rd349, %rd27, 1;
	add.s64 	%rd350, %rd58, %rd349;
	st.b16 	[%rd350], %rs13;
$L__BB20_367:
	@%p92 bra 	$L__BB20_552;
	@%p237 bra 	$L__BB20_383;
	shr.u64 	%rd38, %rd319, 48;
	cvt.u32.u64 	%r339, %rd38;
	and.b32 	%r54, %r339, 32768;
	shr.u64 	%rd355, %rd319, 52;
	cvt.u32.u64 	%r340, %rd355;
	and.b32 	%r55, %r340, 2047;
	setp.eq.b32 	%p260, %r55, 0;
	@%p260 bra 	$L__BB20_372;
	and.b64 	%rd37, %rd319, 4503599627370495;
	setp.eq.b32 	%p259, %r414, 12;
	selp.b32 	%r56, 11, 8, %p259;
	selp.b32 	%r416, 31744, 32640, %p259;
	setp.ne.b32 	%p261, %r55, 2047;
	@%p261 bra 	$L__BB20_373;
	setp.eq.b64 	%p262, %rd37, 0;
	add.s32 	%r341, %r56, -2;
	mov.b32 	%r342, 1;
	shl.b32 	%r343, %r342, %r341;
	selp.b32 	%r344, 0, %r343, %p262;
	or.b32 	%r345, %r54, %r344;
	or.b32 	%r346, %r345, %r416;
	cvt.u16.u32 	%rs14, %r346;
	bra.uni 	$L__BB20_382;
$L__BB20_383:
	setp.ne.b32 	%p258, %r414, 10;
	@%p258 bra 	$L__BB20_385;
	cvt.rn.f32.f64 	%r338, %rd319;
	shl.b64 	%rd353, %rd27, 2;
	add.s64 	%rd354, %rd58, %rd353;
	st.b32 	[%rd354+4], %r338;
	bra.uni 	$L__BB20_552;
$L__BB20_385:
	shl.b64 	%rd351, %rd27, 3;
	add.s64 	%rd352, %rd58, %rd351;
	st.b64 	[%rd352+8], %rd319;
	bra.uni 	$L__BB20_552;
$L__BB20_372:
	cvt.u16.u32 	%rs14, %r54;
	bra.uni 	$L__BB20_382;
$L__BB20_373:
	selp.b32 	%r347, -14, -126, %p259;
	add.s32 	%r58, %r55, -1023;
	or.b64 	%rd39, %rd37, 4503599627370496;
	setp.ge.s32 	%p263, %r58, %r347;
	@%p263 bra 	$L__BB20_379;
	and.b64 	%rd40, %rd38, 32768;
	selp.b32 	%r357, 28, -81, %p259;
	sub.s32 	%r59, %r357, %r58;
	setp.gt.s32 	%p271, %r59, 0;
	@%p271 bra 	$L__BB20_376;
	bra.uni 	$L__BB20_375;
$L__BB20_376:
	setp.gt.u32 	%p272, %r59, 63;
	mov.b64 	%rd468, 0;
	@%p272 bra 	$L__BB20_378;
	shr.u64 	%rd369, %rd39, %r59;
	mov.b64 	%rd370, -1;
	shl.b64 	%rd371, %rd370, %r59;
	not.b64 	%rd372, %rd371;
	and.b64 	%rd373, %rd39, %rd372;
	add.s32 	%r358, %r59, -1;
	mov.b64 	%rd374, 1;
	shl.b64 	%rd375, %rd374, %r358;
	setp.gt.u64 	%p273, %rd373, %rd375;
	setp.eq.b64 	%p274, %rd373, %rd375;
	and.b64 	%rd376, %rd369, 1;
	setp.ne.b64 	%p275, %rd376, 0;
	and.pred 	%p276, %p274, %p275;
	or.pred 	%p277, %p273, %p276;
	selp.b64 	%rd377, 1, 0, %p277;
	add.s64 	%rd468, %rd369, %rd377;
	bra.uni 	$L__BB20_378;
$L__BB20_379:
	selp.b32 	%r57, 15, 127, %p259;
	sub.s32 	%r348, 53, %r56;
	shr.u64 	%rd356, %rd39, %r348;
	mov.b64 	%rd357, -1;
	shl.b64 	%rd358, %rd357, %r348;
	not.b64 	%rd359, %rd358;
	and.b64 	%rd360, %rd359, %rd319;
	sub.s32 	%r349, 52, %r56;
	mov.b64 	%rd361, 1;
	shl.b64 	%rd362, %rd361, %r349;
	setp.gt.u64 	%p264, %rd360, %rd362;
	setp.eq.b64 	%p265, %rd360, %rd362;
	and.b64 	%rd363, %rd356, 1;
	setp.ne.b64 	%p266, %rd363, 0;
	and.pred 	%p267, %p265, %p266;
	or.pred 	%p268, %p264, %p267;
	selp.b64 	%rd364, 1, 0, %p268;
	add.s64 	%rd41, %rd356, %rd364;
	shl.b64 	%rd42, %rd361, %r56;
	setp.eq.b64 	%p269, %rd41, %rd42;
	add.s32 	%r350, %r55, -1022;
	selp.b32 	%r60, %r350, %r58, %p269;
	setp.gt.s32 	%p270, %r60, %r57;
	@%p270 bra 	$L__BB20_381;
	selp.b32 	%r351, 1, 0, %p269;
	shr.u64 	%rd365, %rd41, %r351;
	add.s32 	%r352, %r60, %r57;
	add.s32 	%r353, %r56, -1;
	shl.b32 	%r354, %r352, %r353;
	shl.b64 	%rd366, %rd357, %r353;
	not.b64 	%rd367, %rd366;
	and.b64 	%rd368, %rd365, %rd367;
	cvt.u32.u64 	%r355, %rd368;
	or.b32 	%r416, %r354, %r355;
$L__BB20_381:
	or.b32 	%r356, %r416, %r54;
	cvt.u16.u32 	%rs14, %r356;
	bra.uni 	$L__BB20_382;
$L__BB20_478:
	shl.b64 	%rd391, %rd27, 3;
	add.s64 	%rd392, %rd62, %rd391;
	ld.b64 	%rd471, [%rd392];
	bra.uni 	$L__BB20_483;
$L__BB20_479:
	shl.b64 	%rd388, %rd27, 1;
	add.s64 	%rd389, %rd62, %rd388;
	ld.s16 	%rd471, [%rd389];
	bra.uni 	$L__BB20_483;
$L__BB20_481:
	shl.b64 	%rd381, %rd27, 2;
	add.s64 	%rd382, %rd62, %rd381;
	ld.b32 	%rd471, [%rd382];
	bra.uni 	$L__BB20_483;
$L__BB20_480:
	add.s64 	%rd385, %rd62, %rd27;
	ld.b8 	%rd471, [%rd385];
	bra.uni 	$L__BB20_483;
$L__BB20_477:
	shl.b64 	%rd393, %rd27, 3;
	add.s64 	%rd394, %rd62, %rd393;
	ld.b64 	%rd472, [%rd394];
	bra.uni 	$L__BB20_484;
$L__BB20_482:
	shl.b64 	%rd397, %rd27, 3;
	add.s64 	%rd398, %rd62, %rd397;
	ld.b64 	%rd471, [%rd398];
$L__BB20_483:
	setp.lt.s32 	%p292, %r420, 5;
	cvt.rn.f64.s64 	%rd399, %rd471;
	cvt.rn.f64.u64 	%rd400, %rd471;
	selp.f64 	%rd472, %rd399, %rd400, %p292;
$L__BB20_484:
	@%p328 bra 	$L__BB20_488;
	mov.b32 	%r422, 12;
	@%p331 bra 	$L__BB20_492;
	mov.b32 	%r422, %r82;
	@%p332 bra 	$L__BB20_487;
	bra.uni 	$L__BB20_492;
$L__BB20_487:
	mov.b32 	%r422, 13;
	bra.uni 	$L__BB20_492;
$L__BB20_488:
	@%p329 bra 	$L__BB20_491;
	mov.b32 	%r422, %r82;
	@%p330 bra 	$L__BB20_492;
	mov.b32 	%r422, 9;
	bra.uni 	$L__BB20_492;
$L__BB20_491:
	mov.b32 	%r422, 10;
$L__BB20_492:
	and.b32 	%r379, %r422, -2;
	setp.ne.b32 	%p297, %r379, 12;
	@%p297 bra 	$L__BB20_502;
	shl.b64 	%rd423, %rd27, 1;
	add.s64 	%rd424, %rd60, %rd423;
	ld.b16 	%rs9, [%rd424];
	setp.ne.b32 	%p311, %r422, 13;
	cvt.u32.u16 	%r79, %rs9;
	@%p311 bra 	$L__BB20_495;
	shl.b32 	%r423, %r79, 16;
	bra.uni 	$L__BB20_501;
$L__BB20_502:
	setp.gt.s32 	%p298, %r422, 4;
	@%p298 bra 	$L__BB20_510;
	bra.uni 	$L__BB20_503;
$L__BB20_510:
	setp.gt.s32 	%p299, %r422, 6;
	@%p299 bra 	$L__BB20_514;
	bra.uni 	$L__BB20_511;
$L__BB20_514:
	setp.eq.b32 	%p300, %r422, 7;
	@%p300 bra 	$L__BB20_522;
	setp.eq.b32 	%p301, %r422, 9;
	@%p301 bra 	$L__BB20_518;
	setp.ne.b32 	%p302, %r422, 10;
	@%p302 bra 	$L__BB20_523;
	shl.b64 	%rd417, %rd27, 2;
	add.s64 	%rd418, %rd60, %rd417;
	ld.b32 	%r380, [%rd418];
	cvt.f64.f32 	%rd474, %r380;
	bra.uni 	$L__BB20_525;
$L__BB20_495:
	cvt.s32.s16 	%r381, %rs9;
	and.b32 	%r423, %r381, -2147483648;
	bfe.u32 	%r80, %r79, 10, 5;
	setp.eq.b32 	%p312, %r80, 31;
	@%p312 bra 	$L__BB20_499;
	and.b32 	%r81, %r79, 1023;
	setp.ne.b32 	%p313, %r80, 0;
	@%p313 bra 	$L__BB20_500;
	setp.eq.b32 	%p314, %r81, 0;
	@%p314 bra 	$L__BB20_501;
	clz.b32 	%r384, %r81;
	xor.b32 	%r385, %r384, 31;
	sub.s32 	%r386, 9, %r385;
	shl.b32 	%r387, %r79, %r386;
	shl.b32 	%r388, %r385, 23;
	shl.b32 	%r389, %r387, 14;
	and.b32 	%r390, %r389, 8372224;
	add.s32 	%r391, %r388, %r423;
	add.s32 	%r392, %r391, %r390;
	add.s32 	%r423, %r392, 864026624;
	bra.uni 	$L__BB20_501;
$L__BB20_503:
	setp.gt.s32 	%p305, %r422, 2;
	@%p305 bra 	$L__BB20_507;
	setp.eq.b32 	%p308, %r422, 1;
	@%p308 bra 	$L__BB20_519;
	setp.eq.b32 	%p309, %r422, 2;
	@%p309 bra 	$L__BB20_506;
	bra.uni 	$L__BB20_523;
$L__BB20_506:
	add.s64 	%rd412, %rd60, %rd27;
	ld.s8 	%rd473, [%rd412];
	bra.uni 	$L__BB20_524;
$L__BB20_507:
	setp.eq.b32 	%p306, %r422, 3;
	@%p306 bra 	$L__BB20_520;
	setp.eq.b32 	%p307, %r422, 4;
	@%p307 bra 	$L__BB20_509;
	bra.uni 	$L__BB20_523;
$L__BB20_509:
	shl.b64 	%rd408, %rd27, 2;
	add.s64 	%rd409, %rd60, %rd408;
	ld.s32 	%rd473, [%rd409];
	bra.uni 	$L__BB20_524;
$L__BB20_511:
	setp.eq.b32 	%p303, %r422, 5;
	@%p303 bra 	$L__BB20_521;
	setp.eq.b32 	%p304, %r422, 6;
	@%p304 bra 	$L__BB20_513;
	bra.uni 	$L__BB20_523;
$L__BB20_513:
	shl.b64 	%rd405, %rd27, 1;
	add.s64 	%rd406, %rd60, %rd405;
	ld.b16 	%rd473, [%rd406];
	bra.uni 	$L__BB20_524;
$L__BB20_499:
	shl.b32 	%r382, %r79, 13;
	or.b32 	%r383, %r423, %r382;
	or.b32 	%r423, %r383, 2139095040;
	bra.uni 	$L__BB20_501;
$L__BB20_500:
	shl.b32 	%r393, %r80, 23;
	shl.b32 	%r394, %r81, 13;
	or.b32 	%r395, %r393, %r394;
	add.s32 	%r396, %r395, %r423;
	add.s32 	%r423, %r396, 939524096;
$L__BB20_501:
	cvt.f64.f32 	%rd474, %r423;
	bra.uni 	$L__BB20_525;
$L__BB20_519:
	shl.b64 	%rd413, %rd27, 3;
	add.s64 	%rd414, %rd60, %rd413;
	ld.b64 	%rd473, [%rd414];
	bra.uni 	$L__BB20_524;
$L__BB20_520:
	shl.b64 	%rd410, %rd27, 1;
	add.s64 	%rd411, %rd60, %rd410;
	ld.s16 	%rd473, [%rd411];
	bra.uni 	$L__BB20_524;
$L__BB20_522:
	shl.b64 	%rd403, %rd27, 2;
	add.s64 	%rd404, %rd60, %rd403;
	ld.b32 	%rd473, [%rd404];
	bra.uni 	$L__BB20_524;
$L__BB20_521:
	add.s64 	%rd407, %rd60, %rd27;
	ld.b8 	%rd473, [%rd407];
	bra.uni 	$L__BB20_524;
$L__BB20_518:
	shl.b64 	%rd415, %rd27, 3;
	add.s64 	%rd416, %rd60, %rd415;
	ld.b64 	%rd474, [%rd416];
	bra.uni 	$L__BB20_525;
$L__BB20_523:
)QPTX";
        result += R"QPTX(
	shl.b64 	%rd419, %rd27, 3;
	add.s64 	%rd420, %rd60, %rd419;
	ld.b64 	%rd473, [%rd420];
$L__BB20_524:
	setp.lt.s32 	%p310, %r422, 5;
	cvt.rn.f64.s64 	%rd421, %rd473;
	cvt.rn.f64.u64 	%rd422, %rd473;
	selp.f64 	%rd474, %rd421, %rd422, %p310;
$L__BB20_525:
	setp.eq.b32 	%p315, %r85, 6;
	mov.b64 	%rd57, 0d0000000000000000;
	@%p315 bra 	$L__BB20_527;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .b32 	param2;
	.param .align 8 .b8 	retval0[16];
	st.param.b32 	[param2], %r82;
	st.param.b64 	[param1], %rd66;
	st.param.b64 	[param0], %rd61;
	call.uni (retval0), _Z6q_readIdE5QPairIT_EPKvyi, (param0, param1, param2);
	ld.param.b64 	%rd57, [retval0];
	}
$L__BB20_527:
	setp.ne.b32 	%p316, %r83, 2;
	@%p316 bra 	$L__BB20_529;
	setp.eq.b32 	%p322, %r85, 5;
	setp.eq.b32 	%p323, %r84, 1;
	neg.f64 	%rd428, %rd472;
	selp.f64 	%rd429, %rd428, %rd472, %p323;
	selp.f64 	%rd475, %rd472, %rd429, %p322;
	selp.f64 	%rd476, %rd428, %rd472, %p322;
	bra.uni 	$L__BB20_533;
$L__BB20_529:
	setp.ne.b32 	%p317, %r85, 5;
	setp.ne.b32 	%p318, %r83, 3;
	or.pred 	%p319, %p318, %p317;
	@%p319 bra 	$L__BB20_531;
	mul.rn.f64 	%rd475, %rd472, %rd57;
	mul.rn.f64 	%rd476, %rd472, %rd474;
	bra.uni 	$L__BB20_533;
$L__BB20_531:
	setp.ne.b32 	%p320, %r83, 4;
	or.pred 	%p321, %p320, %p317;
	mov.b64 	%rd475, %rd472;
	mov.b64 	%rd476, %rd472;
	@%p321 bra 	$L__BB20_533;
	div.rn.f64 	%rd475, %rd472, %rd57;
	mul.rn.f64 	%rd425, %rd57, %rd57;
	neg.f64 	%rd426, %rd474;
	mul.rn.f64 	%rd427, %rd472, %rd426;
	div.rn.f64 	%rd476, %rd427, %rd425;
$L__BB20_533:
	setp.ne.b32 	%p324, %r85, 6;
	@%p324 bra 	$L__BB20_541;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .b32 	param2;
	.param .align 8 .b8 	retval0[16];
	st.param.b32 	[param2], %r82;
	st.param.b64 	[param0], %rd68;
	st.param.b64 	[param1], 0;
	call.uni (retval0), _Z6q_readIdE5QPairIT_EPKvyi, (param0, param1, param2);
	ld.param.b64 	%rd442, [retval0];
	}
	setp.eq.b32 	%p326, %r83, 4;
	@%p326 bra 	$L__BB20_537;
	setp.ne.b32 	%p327, %r83, 3;
	@%p327 bra 	$L__BB20_540;
	mul.rn.f64 	%rd475, %rd472, %rd442;
	bra.uni 	$L__BB20_540;
$L__BB20_541:
	ld.param.b64 	%rd59, [_Z5q_runIdEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_1];
	setp.ne.b64 	%p325, %rd58, %rd59;
	@%p325 bra 	$L__BB20_551;
	bra.uni 	$L__BB20_542;
$L__BB20_551:
	st.local.b64 	[%rd6], %rd475;
	st.local.b64 	[%rd6+8], 0;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .align 8 .b8 	param2[16];
	.param .b32 	param3;
	st.param.b32 	[param3], %r82;
	cvta.to.local.u64 	%rd430, %rd73;
	ld.local.b64 	%rd431, [%rd430+8];
	st.param.b64 	[param2+8], %rd431;
	ld.local.b64 	%rd432, [%rd430];
	st.param.b64 	[param2], %rd432;
	st.param.b64 	[param1], %rd66;
	st.param.b64 	[param0], %rd58;
	call.uni _Z7q_storeIdEvPvy5QPairIT_Ei, (param0, param1, param2, param3);
	}
	st.local.b64 	[%rd7], %rd476;
	st.local.b64 	[%rd7+8], 0;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .align 8 .b8 	param2[16];
	.param .b32 	param3;
	st.param.b32 	[param3], %r82;
	cvta.to.local.u64 	%rd433, %rd74;
	ld.local.b64 	%rd434, [%rd433+8];
	st.param.b64 	[param2+8], %rd434;
	ld.local.b64 	%rd435, [%rd433];
	st.param.b64 	[param2], %rd435;
	st.param.b64 	[param1], %rd66;
	st.param.b64 	[param0], %rd59;
	call.uni _Z7q_storeIdEvPvy5QPairIT_Ei, (param0, param1, param2, param3);
	}
	bra.uni 	$L__BB20_552;
$L__BB20_542:
	@%p328 bra 	$L__BB20_546;
	mov.b32 	%r424, 12;
	@%p331 bra 	$L__BB20_550;
	mov.b32 	%r424, %r82;
	@%p332 bra 	$L__BB20_545;
	bra.uni 	$L__BB20_550;
$L__BB20_545:
	mov.b32 	%r424, 13;
	bra.uni 	$L__BB20_550;
$L__BB20_537:
	@%p181 bra 	$L__BB20_539;
	mul.rn.f64 	%rd443, %rd474, %rd474;
	neg.f64 	%rd444, %rd442;
	mul.rn.f64 	%rd445, %rd472, %rd444;
	div.rn.f64 	%rd475, %rd445, %rd443;
	bra.uni 	$L__BB20_540;
$L__BB20_546:
	@%p329 bra 	$L__BB20_549;
	mov.b32 	%r424, %r82;
	@%p330 bra 	$L__BB20_550;
	mov.b32 	%r424, 9;
	bra.uni 	$L__BB20_550;
$L__BB20_539:
	div.rn.f64 	%rd475, %rd472, %rd442;
$L__BB20_540:
	st.local.b64 	[%rd4], %rd475;
	st.local.b64 	[%rd4+8], 0;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .align 8 .b8 	param2[16];
	.param .b32 	param3;
	st.param.b32 	[param3], %r82;
	cvta.to.local.u64 	%rd446, %rd71;
	ld.local.b64 	%rd447, [%rd446+8];
	st.param.b64 	[param2+8], %rd447;
	ld.local.b64 	%rd448, [%rd446];
	st.param.b64 	[param2], %rd448;
	st.param.b64 	[param1], %rd66;
	st.param.b64 	[param0], %rd58;
	call.uni _Z7q_storeIdEvPvy5QPairIT_Ei, (param0, param1, param2, param3);
	}
	bra.uni 	$L__BB20_552;
$L__BB20_549:
	mov.b32 	%r424, 10;
$L__BB20_550:
	{
	.param .b64 	param0;
	.param .b32 	param1;
	.param .b64 	retval0;
	st.param.b32 	[param1], %r424;
	st.param.b64 	[param0], %rd475;
	call.uni (retval0), _Z7q_roundIdET_S0_i, (param0, param1);
	ld.param.b64 	%rd436, [retval0];
	}
	{
	.param .b64 	param0;
	.param .b32 	param1;
	.param .b64 	retval0;
	st.param.b32 	[param1], %r424;
	st.param.b64 	[param0], %rd476;
	call.uni (retval0), _Z7q_roundIdET_S0_i, (param0, param1);
	ld.param.b64 	%rd437, [retval0];
	}
	add.rn.f64 	%rd438, %rd436, %rd437;
	st.local.b64 	[%rd5], %rd438;
	st.local.b64 	[%rd5+8], 0;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .align 8 .b8 	param2[16];
	.param .b32 	param3;
	st.param.b32 	[param3], %r82;
	cvta.to.local.u64 	%rd439, %rd72;
	ld.local.b64 	%rd440, [%rd439+8];
	st.param.b64 	[param2+8], %rd440;
	ld.local.b64 	%rd441, [%rd439];
	st.param.b64 	[param2], %rd441;
	st.param.b64 	[param1], %rd66;
	st.param.b64 	[param0], %rd58;
	call.uni _Z7q_storeIdEvPvy5QPairIT_Ei, (param0, param1, param2, param3);
	}
	bra.uni 	$L__BB20_552;
$L__BB20_418:
	neg.s32 	%r315, %r74;
	shl.b64 	%rd470, %rd53, %r315;
$L__BB20_421:
	or.b64 	%rd310, %rd470, %rd54;
	cvt.u16.u64 	%rs16, %rd310;
$L__BB20_425:
	shl.b64 	%rd311, %rd27, 1;
	add.s64 	%rd312, %rd58, %rd311;
	st.b16 	[%rd312+2], %rs16;
	bra.uni 	$L__BB20_552;
$L__BB20_375:
	neg.s32 	%r359, %r59;
	shl.b64 	%rd468, %rd39, %r359;
$L__BB20_378:
	or.b64 	%rd378, %rd468, %rd40;
	cvt.u16.u64 	%rs14, %rd378;
$L__BB20_382:
	shl.b64 	%rd379, %rd27, 1;
	add.s64 	%rd380, %rd58, %rd379;
	st.b16 	[%rd380+2], %rs14;
$L__BB20_552:
	ret;
}
.weak .func _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj(
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_0,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_1,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_2,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_3,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_4,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_5,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_6,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_7,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_8,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_9,
	.param .b32 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_10,
	.param .b32 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_11,
	.param .b32 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_12,
	.param .b32 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_13,
	.param .b64 _Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_14
)
{
	.local .align 8 .b8 	__local_depot21[64];
	.reg .b64 	%SP;
	.reg .b64 	%SPL;
	.reg .pred 	%p<334>;
	.reg .b16 	%rs<17>;
	.reg .b32 	%r<462>;
	.reg .b64 	%rd<447>;
	mov.b64 	%SPL, __local_depot21;
	cvta.local.u64 	%SP, %SPL;
	ld.param.b32 	%r95, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_13];
	ld.param.b32 	%r92, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_10];
	ld.param.b64 	%rd66, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_9];
	ld.param.b64 	%rd62, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_4];
	ld.param.b64 	%rd58, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_0];
	add.u64 	%rd68, %SP, 0;
	add.u64 	%rd1, %SPL, 0;
	add.u64 	%rd69, %SP, 16;
	add.u64 	%rd2, %SPL, 16;
	add.u64 	%rd70, %SP, 24;
	add.u64 	%rd3, %SPL, 24;
	add.u64 	%rd71, %SP, 32;
	add.u64 	%rd4, %SPL, 32;
	add.u64 	%rd72, %SP, 40;
	add.u64 	%rd5, %SPL, 40;
	add.u64 	%rd73, %SP, 48;
	add.u64 	%rd6, %SPL, 48;
	add.u64 	%rd74, %SP, 56;
	add.u64 	%rd7, %SPL, 56;
	setp.eq.b32 	%p1, %r95, 11;
	setp.gt.s32 	%p328, %r92, 15;
	add.s32 	%r429, %r92, -14;
	setp.eq.b32 	%p329, %r92, 16;
	setp.ne.b32 	%p330, %r92, 17;
	setp.eq.b32 	%p331, %r92, 14;
	setp.eq.b32 	%p332, %r92, 15;
	@%p1 bra 	$L__BB21_2;
	setp.ne.b32 	%p2, %r95, 4;
	@%p2 bra 	$L__BB21_109;
$L__BB21_2:
	ld.param.b64 	%rd63, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_5];
	shl.b64 	%rd75, %rd66, 3;
	add.s64 	%rd76, %rd63, %rd75;
	ld.b64 	%rd425, [%rd76];
	ld.b64 	%rd8, [%rd76+8];
	setp.ge.u64 	%p3, %rd425, %rd8;
	mov.b32 	%r436, 0f00000000;
	@%p3 bra 	$L__BB21_6;
	ld.param.b64 	%rd64, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_6];
	setp.lt.u32 	%p4, %r429, 4;
	selp.b64 	%rd9, 1, 0, %p4;
	shl.b64 	%rd77, %rd425, 3;
	add.s64 	%rd424, %rd64, %rd77;
	mov.b32 	%r436, 0f00000000;
	setp.ne.b32 	%p23, %r95, 11;
	bra.uni 	$L__BB21_4;
$L__BB21_101:
	shl.b32 	%r436, %r19, 16;
$L__BB21_108:
	add.s64 	%rd425, %rd425, 1;
	add.s64 	%rd424, %rd424, 8;
	setp.lt.u64 	%p48, %rd425, %rd8;
	@%p48 bra 	$L__BB21_4;
	bra.uni 	$L__BB21_6;
$L__BB21_4:
	@%p328 bra 	$L__BB21_40;
	mov.b32 	%r432, 12;
	@%p331 bra 	$L__BB21_44;
	mov.b32 	%r432, %r92;
	@%p332 bra 	$L__BB21_39;
	bra.uni 	$L__BB21_44;
$L__BB21_39:
	mov.b32 	%r432, 13;
	bra.uni 	$L__BB21_44;
$L__BB21_40:
	@%p329 bra 	$L__BB21_43;
	mov.b32 	%r432, %r92;
	@%p330 bra 	$L__BB21_44;
	mov.b32 	%r432, 9;
	bra.uni 	$L__BB21_44;
$L__BB21_43:
	mov.b32 	%r432, 10;
$L__BB21_44:
	ld.b64 	%rd18, [%rd424];
	cvt.u32.u64 	%r96, %rd9;
	shl.b64 	%rd19, %rd18, %r96;
	and.b32 	%r97, %r432, -2;
	setp.ne.b32 	%p5, %r97, 12;
	@%p5 bra 	$L__BB21_54;
	shl.b64 	%rd98, %rd19, 1;
	add.s64 	%rd99, %rd62, %rd98;
	ld.b16 	%rs1, [%rd99];
	setp.ne.b32 	%p19, %r432, 13;
	cvt.u32.u16 	%r9, %rs1;
	@%p19 bra 	$L__BB21_47;
	shl.b32 	%r433, %r9, 16;
	bra.uni 	$L__BB21_53;
$L__BB21_54:
	setp.gt.s32 	%p6, %r432, 4;
	@%p6 bra 	$L__BB21_62;
	bra.uni 	$L__BB21_55;
$L__BB21_62:
	setp.gt.s32 	%p7, %r432, 6;
	@%p7 bra 	$L__BB21_66;
	bra.uni 	$L__BB21_63;
$L__BB21_66:
	setp.eq.b32 	%p8, %r432, 7;
	@%p8 bra 	$L__BB21_74;
	setp.eq.b32 	%p9, %r432, 9;
	@%p9 bra 	$L__BB21_70;
	setp.ne.b32 	%p10, %r432, 10;
	@%p10 bra 	$L__BB21_75;
	shl.b64 	%rd92, %rd19, 2;
	add.s64 	%rd93, %rd62, %rd92;
	ld.b32 	%r98, [%rd93];
	cvt.f64.f32 	%rd427, %r98;
	bra.uni 	$L__BB21_77;
$L__BB21_47:
	cvt.s32.s16 	%r99, %rs1;
	and.b32 	%r433, %r99, -2147483648;
	bfe.u32 	%r10, %r9, 10, 5;
	setp.eq.b32 	%p20, %r10, 31;
	@%p20 bra 	$L__BB21_51;
	and.b32 	%r11, %r9, 1023;
	setp.ne.b32 	%p21, %r10, 0;
	@%p21 bra 	$L__BB21_52;
	setp.eq.b32 	%p22, %r11, 0;
	@%p22 bra 	$L__BB21_53;
	clz.b32 	%r102, %r11;
	xor.b32 	%r103, %r102, 31;
	sub.s32 	%r104, 9, %r103;
	shl.b32 	%r105, %r9, %r104;
	shl.b32 	%r106, %r103, 23;
	shl.b32 	%r107, %r105, 14;
	and.b32 	%r108, %r107, 8372224;
	add.s32 	%r109, %r106, %r433;
	add.s32 	%r110, %r109, %r108;
	add.s32 	%r433, %r110, 864026624;
	bra.uni 	$L__BB21_53;
$L__BB21_55:
	setp.gt.s32 	%p13, %r432, 2;
	@%p13 bra 	$L__BB21_59;
	setp.eq.b32 	%p16, %r432, 1;
	@%p16 bra 	$L__BB21_71;
	setp.eq.b32 	%p17, %r432, 2;
	@%p17 bra 	$L__BB21_58;
	bra.uni 	$L__BB21_75;
$L__BB21_58:
	add.s64 	%rd87, %rd62, %rd19;
	ld.s8 	%rd426, [%rd87];
	bra.uni 	$L__BB21_76;
$L__BB21_59:
	setp.eq.b32 	%p14, %r432, 3;
	@%p14 bra 	$L__BB21_72;
	setp.eq.b32 	%p15, %r432, 4;
	@%p15 bra 	$L__BB21_61;
	bra.uni 	$L__BB21_75;
$L__BB21_61:
	shl.b64 	%rd83, %rd19, 2;
	add.s64 	%rd84, %rd62, %rd83;
	ld.s32 	%rd426, [%rd84];
	bra.uni 	$L__BB21_76;
$L__BB21_63:
	setp.eq.b32 	%p11, %r432, 5;
	@%p11 bra 	$L__BB21_73;
	setp.eq.b32 	%p12, %r432, 6;
	@%p12 bra 	$L__BB21_65;
	bra.uni 	$L__BB21_75;
$L__BB21_65:
	shl.b64 	%rd80, %rd19, 1;
	add.s64 	%rd81, %rd62, %rd80;
	ld.b16 	%rd426, [%rd81];
	bra.uni 	$L__BB21_76;
$L__BB21_51:
	shl.b32 	%r100, %r9, 13;
	or.b32 	%r101, %r433, %r100;
	or.b32 	%r433, %r101, 2139095040;
	bra.uni 	$L__BB21_53;
$L__BB21_52:
	shl.b32 	%r111, %r10, 23;
	shl.b32 	%r112, %r11, 13;
	or.b32 	%r113, %r111, %r112;
	add.s32 	%r114, %r113, %r433;
	add.s32 	%r433, %r114, 939524096;
$L__BB21_53:
	cvt.f64.f32 	%rd427, %r433;
	bra.uni 	$L__BB21_77;
$L__BB21_71:
	shl.b64 	%rd88, %rd19, 3;
	add.s64 	%rd89, %rd62, %rd88;
	ld.b64 	%rd426, [%rd89];
	bra.uni 	$L__BB21_76;
$L__BB21_72:
	shl.b64 	%rd85, %rd19, 1;
	add.s64 	%rd86, %rd62, %rd85;
	ld.s16 	%rd426, [%rd86];
	bra.uni 	$L__BB21_76;
$L__BB21_74:
	shl.b64 	%rd78, %rd19, 2;
	add.s64 	%rd79, %rd62, %rd78;
	ld.b32 	%rd426, [%rd79];
	bra.uni 	$L__BB21_76;
$L__BB21_73:
	add.s64 	%rd82, %rd62, %rd19;
	ld.b8 	%rd426, [%rd82];
	bra.uni 	$L__BB21_76;
$L__BB21_70:
	shl.b64 	%rd90, %rd19, 3;
	add.s64 	%rd91, %rd62, %rd90;
	ld.b64 	%rd427, [%rd91];
	bra.uni 	$L__BB21_77;
$L__BB21_75:
	shl.b64 	%rd94, %rd19, 3;
	add.s64 	%rd95, %rd62, %rd94;
	ld.b64 	%rd426, [%rd95];
$L__BB21_76:
	setp.lt.s32 	%p18, %r432, 5;
	cvt.rn.f64.s64 	%rd96, %rd426;
	cvt.rn.f64.u64 	%rd97, %rd426;
	selp.f64 	%rd427, %rd96, %rd97, %p18;
$L__BB21_77:
	cvt.rn.f32.f64 	%r115, %rd427;
	add.rn.f32 	%r436, %r436, %r115;
	@%p23 bra 	$L__BB21_108;
	@%p328 bra 	$L__BB21_82;
	mov.b32 	%r434, 12;
	@%p331 bra 	$L__BB21_86;
	mov.b32 	%r434, %r92;
	@%p332 bra 	$L__BB21_81;
	bra.uni 	$L__BB21_86;
$L__BB21_81:
	mov.b32 	%r434, 13;
	bra.uni 	$L__BB21_86;
$L__BB21_82:
	@%p329 bra 	$L__BB21_85;
	mov.b32 	%r434, %r92;
	@%p330 bra 	$L__BB21_86;
	mov.b32 	%r434, 9;
	bra.uni 	$L__BB21_86;
$L__BB21_85:
	mov.b32 	%r434, 10;
$L__BB21_86:
	and.b32 	%r116, %r434, -2;
	setp.ne.b32 	%p24, %r116, 12;
	@%p24 bra 	$L__BB21_108;
	cvt.f64.f32 	%rd20, %r436;
	shr.u64 	%rd22, %rd20, 48;
	cvt.u32.u64 	%r117, %rd22;
	and.b32 	%r12, %r117, 32768;
	shr.u64 	%rd100, %rd20, 52;
	cvt.u32.u64 	%r118, %rd100;
	and.b32 	%r13, %r118, 2047;
	setp.eq.b32 	%p26, %r13, 0;
	@%p26 bra 	$L__BB21_90;
	and.b64 	%rd21, %rd20, 4503599627370495;
	setp.eq.b32 	%p25, %r434, 12;
	selp.b32 	%r14, 11, 8, %p25;
	selp.b32 	%r435, 31744, 32640, %p25;
	setp.ne.b32 	%p27, %r13, 2047;
	@%p27 bra 	$L__BB21_91;
	setp.eq.b64 	%p28, %rd21, 0;
	add.s32 	%r119, %r14, -2;
	mov.b32 	%r120, 1;
	shl.b32 	%r121, %r120, %r119;
	selp.b32 	%r122, 0, %r121, %p28;
	or.b32 	%r123, %r12, %r122;
	or.b32 	%r124, %r123, %r435;
	cvt.u16.u32 	%rs12, %r124;
	bra.uni 	$L__BB21_100;
$L__BB21_90:
	cvt.u16.u32 	%rs12, %r12;
	bra.uni 	$L__BB21_100;
$L__BB21_91:
	selp.b32 	%r125, -14, -126, %p25;
	add.s32 	%r16, %r13, -1023;
	or.b64 	%rd23, %rd21, 4503599627370496;
	setp.ge.s32 	%p29, %r16, %r125;
	@%p29 bra 	$L__BB21_97;
	and.b64 	%rd24, %rd22, 32768;
	selp.b32 	%r135, 28, -81, %p25;
	sub.s32 	%r17, %r135, %r16;
	setp.gt.s32 	%p37, %r17, 0;
	@%p37 bra 	$L__BB21_94;
	bra.uni 	$L__BB21_93;
$L__BB21_94:
	setp.gt.u32 	%p38, %r17, 63;
	mov.b64 	%rd428, 0;
	@%p38 bra 	$L__BB21_96;
	shr.u64 	%rd114, %rd23, %r17;
	mov.b64 	%rd115, -1;
	shl.b64 	%rd116, %rd115, %r17;
	not.b64 	%rd117, %rd116;
	and.b64 	%rd118, %rd23, %rd117;
	add.s32 	%r136, %r17, -1;
	mov.b64 	%rd119, 1;
	shl.b64 	%rd120, %rd119, %r136;
	setp.gt.u64 	%p39, %rd118, %rd120;
	setp.eq.b64 	%p40, %rd118, %rd120;
	and.b64 	%rd121, %rd114, 1;
	setp.ne.b64 	%p41, %rd121, 0;
	and.pred 	%p42, %p40, %p41;
	or.pred 	%p43, %p39, %p42;
	selp.b64 	%rd122, 1, 0, %p43;
	add.s64 	%rd428, %rd114, %rd122;
	bra.uni 	$L__BB21_96;
$L__BB21_97:
	selp.b32 	%r15, 15, 127, %p25;
	sub.s32 	%r126, 53, %r14;
	shr.u64 	%rd101, %rd23, %r126;
	mov.b64 	%rd102, -1;
	shl.b64 	%rd103, %rd102, %r126;
	not.b64 	%rd104, %rd103;
	and.b64 	%rd105, %rd104, %rd20;
	sub.s32 	%r127, 52, %r14;
	mov.b64 	%rd106, 1;
	shl.b64 	%rd107, %rd106, %r127;
	setp.gt.u64 	%p30, %rd105, %rd107;
	setp.eq.b64 	%p31, %rd105, %rd107;
	and.b64 	%rd108, %rd101, 1;
	setp.ne.b64 	%p32, %rd108, 0;
	and.pred 	%p33, %p31, %p32;
	or.pred 	%p34, %p30, %p33;
	selp.b64 	%rd109, 1, 0, %p34;
	add.s64 	%rd25, %rd101, %rd109;
	shl.b64 	%rd26, %rd106, %r14;
	setp.eq.b64 	%p35, %rd25, %rd26;
	add.s32 	%r128, %r13, -1022;
	selp.b32 	%r18, %r128, %r16, %p35;
	setp.gt.s32 	%p36, %r18, %r15;
	@%p36 bra 	$L__BB21_99;
	selp.b32 	%r129, 1, 0, %p35;
	shr.u64 	%rd110, %rd25, %r129;
	add.s32 	%r130, %r18, %r15;
	add.s32 	%r131, %r14, -1;
	shl.b32 	%r132, %r130, %r131;
	shl.b64 	%rd111, %rd102, %r131;
	not.b64 	%rd112, %rd111;
	and.b64 	%rd113, %rd110, %rd112;
	cvt.u32.u64 	%r133, %rd113;
	or.b32 	%r435, %r132, %r133;
$L__BB21_99:
	or.b32 	%r134, %r435, %r12;
	cvt.u16.u32 	%rs12, %r134;
	bra.uni 	$L__BB21_100;
$L__BB21_93:
	neg.s32 	%r137, %r17;
	shl.b64 	%rd428, %rd23, %r137;
$L__BB21_96:
	or.b64 	%rd123, %rd428, %rd24;
	cvt.u16.u64 	%rs12, %rd123;
$L__BB21_100:
	setp.ne.b32 	%p44, %r434, 13;
	cvt.u32.u16 	%r19, %rs12;
	@%p44 bra 	$L__BB21_102;
	bra.uni 	$L__BB21_101;
$L__BB21_102:
	cvt.s32.s16 	%r138, %rs12;
	and.b32 	%r436, %r138, -2147483648;
	bfe.u32 	%r20, %r19, 10, 5;
	setp.eq.b32 	%p45, %r20, 31;
	@%p45 bra 	$L__BB21_106;
	and.b32 	%r21, %r19, 1023;
	setp.ne.b32 	%p46, %r20, 0;
	@%p46 bra 	$L__BB21_107;
	setp.eq.b32 	%p47, %r21, 0;
	@%p47 bra 	$L__BB21_108;
	clz.b32 	%r141, %r21;
	xor.b32 	%r142, %r141, 31;
	sub.s32 	%r143, 9, %r142;
	shl.b32 	%r144, %r19, %r143;
	shl.b32 	%r145, %r142, 23;
	shl.b32 	%r146, %r144, 14;
	and.b32 	%r147, %r146, 8372224;
	add.s32 	%r148, %r145, %r436;
	add.s32 	%r149, %r148, %r147;
	add.s32 	%r436, %r149, 864026624;
	bra.uni 	$L__BB21_108;
$L__BB21_106:
	shl.b32 	%r139, %r19, 13;
	or.b32 	%r140, %r436, %r139;
	or.b32 	%r436, %r140, 2139095040;
	bra.uni 	$L__BB21_108;
$L__BB21_107:
	shl.b32 	%r150, %r20, 23;
	shl.b32 	%r151, %r21, 13;
	or.b32 	%r152, %r150, %r151;
	add.s32 	%r153, %r152, %r436;
	add.s32 	%r436, %r153, 939524096;
	bra.uni 	$L__BB21_108;
$L__BB21_6:
	@%p328 bra 	$L__BB21_10;
	mov.b32 	%r430, 12;
	@%p331 bra 	$L__BB21_14;
	mov.b32 	%r430, %r92;
	@%p332 bra 	$L__BB21_9;
	bra.uni 	$L__BB21_14;
$L__BB21_9:
	mov.b32 	%r430, 13;
	bra.uni 	$L__BB21_14;
$L__BB21_10:
	@%p329 bra 	$L__BB21_13;
	mov.b32 	%r430, %r92;
	@%p330 bra 	$L__BB21_14;
	mov.b32 	%r430, 9;
	bra.uni 	$L__BB21_14;
$L__BB21_109:
	ld.param.b64 	%rd434, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_8];
	ld.param.b64 	%rd65, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_7];
	st.local.b64 	[%rd1], %rd65;
	st.local.b64 	[%rd1+8], %rd434;
	@%p328 bra 	$L__BB21_113;
	mov.b32 	%r437, 12;
	@%p331 bra 	$L__BB21_117;
	mov.b32 	%r437, %r92;
	@%p332 bra 	$L__BB21_112;
	bra.uni 	$L__BB21_117;
$L__BB21_112:
	mov.b32 	%r437, 13;
	bra.uni 	$L__BB21_117;
$L__BB21_113:
	@%p329 bra 	$L__BB21_116;
	mov.b32 	%r437, %r92;
	@%p330 bra 	$L__BB21_117;
	mov.b32 	%r437, 9;
	bra.uni 	$L__BB21_117;
$L__BB21_13:
	mov.b32 	%r430, 10;
$L__BB21_14:
	setp.lt.u32 	%p49, %r429, 4;
	selp.b32 	%r154, 1, 0, %p49;
	shl.b64 	%rd10, %rd66, %r154;
	cvt.f64.f32 	%rd11, %r436;
	and.b32 	%r1, %r430, -2;
	setp.ne.b32 	%p50, %r1, 12;
	@%p50 bra 	$L__BB21_29;
	shr.u64 	%rd13, %rd11, 48;
	cvt.u32.u64 	%r155, %rd13;
	and.b32 	%r2, %r155, 32768;
	shr.u64 	%rd128, %rd11, 52;
	cvt.u32.u64 	%r156, %rd128;
	and.b32 	%r3, %r156, 2047;
	setp.eq.b32 	%p53, %r3, 0;
	@%p53 bra 	$L__BB21_18;
	and.b64 	%rd12, %rd11, 4503599627370495;
	setp.eq.b32 	%p52, %r430, 12;
	selp.b32 	%r4, 11, 8, %p52;
	selp.b32 	%r431, 31744, 32640, %p52;
	setp.ne.b32 	%p54, %r3, 2047;
	@%p54 bra 	$L__BB21_19;
	setp.eq.b64 	%p55, %rd12, 0;
	add.s32 	%r157, %r4, -2;
	mov.b32 	%r158, 1;
	shl.b32 	%r159, %r158, %r157;
	selp.b32 	%r160, 0, %r159, %p55;
	or.b32 	%r161, %r2, %r160;
	or.b32 	%r162, %r161, %r431;
	cvt.u16.u32 	%rs11, %r162;
	bra.uni 	$L__BB21_28;
$L__BB21_29:
	setp.ne.b32 	%p51, %r430, 10;
	@%p51 bra 	$L__BB21_31;
	shl.b64 	%rd126, %rd10, 2;
	add.s64 	%rd127, %rd58, %rd126;
	st.b32 	[%rd127], %r436;
	bra.uni 	$L__BB21_32;
$L__BB21_31:
	shl.b64 	%rd124, %rd10, 3;
	add.s64 	%rd125, %rd58, %rd124;
	st.b64 	[%rd125], %rd11;
	bra.uni 	$L__BB21_32;
$L__BB21_18:
	cvt.u16.u32 	%rs11, %r2;
	bra.uni 	$L__BB21_28;
$L__BB21_19:
	selp.b32 	%r163, -14, -126, %p52;
	add.s32 	%r6, %r3, -1023;
	or.b64 	%rd14, %rd12, 4503599627370496;
	setp.ge.s32 	%p56, %r6, %r163;
	@%p56 bra 	$L__BB21_25;
	and.b64 	%rd15, %rd13, 32768;
	selp.b32 	%r173, 28, -81, %p52;
	sub.s32 	%r7, %r173, %r6;
	setp.gt.s32 	%p64, %r7, 0;
	@%p64 bra 	$L__BB21_22;
	bra.uni 	$L__BB21_21;
$L__BB21_22:
	setp.gt.u32 	%p65, %r7, 63;
	mov.b64 	%rd423, 0;
	@%p65 bra 	$L__BB21_24;
	shr.u64 	%rd142, %rd14, %r7;
	mov.b64 	%rd143, -1;
	shl.b64 	%rd144, %rd143, %r7;
	not.b64 	%rd145, %rd144;
	and.b64 	%rd146, %rd14, %rd145;
	add.s32 	%r174, %r7, -1;
	mov.b64 	%rd147, 1;
	shl.b64 	%rd148, %rd147, %r174;
	setp.gt.u64 	%p66, %rd146, %rd148;
	setp.eq.b64 	%p67, %rd146, %rd148;
	and.b64 	%rd149, %rd142, 1;
	setp.ne.b64 	%p68, %rd149, 0;
	and.pred 	%p69, %p67, %p68;
	or.pred 	%p70, %p66, %p69;
	selp.b64 	%rd150, 1, 0, %p70;
	add.s64 	%rd423, %rd142, %rd150;
	bra.uni 	$L__BB21_24;
$L__BB21_116:
	mov.b32 	%r437, 10;
$L__BB21_117:
	ld.param.b64 	%rd60, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_2];
	setp.lt.u32 	%p73, %r429, 4;
	selp.b32 	%r176, 1, 0, %p73;
	shl.b64 	%rd29, %rd66, %r176;
	and.b32 	%r24, %r437, -2;
	setp.ne.b32 	%p74, %r24, 12;
	@%p74 bra 	$L__BB21_127;
	shl.b64 	%rd180, %rd29, 1;
	add.s64 	%rd181, %rd60, %rd180;
	ld.b16 	%rs4, [%rd181];
	setp.ne.b32 	%p88, %r437, 13;
	cvt.u32.u16 	%r25, %rs4;
	@%p88 bra 	$L__BB21_120;
	shl.b32 	%r438, %r25, 16;
	bra.uni 	$L__BB21_126;
$L__BB21_127:
	setp.gt.s32 	%p75, %r437, 4;
	@%p75 bra 	$L__BB21_135;
	bra.uni 	$L__BB21_128;
$L__BB21_135:
	setp.gt.s32 	%p76, %r437, 6;
	@%p76 bra 	$L__BB21_139;
	bra.uni 	$L__BB21_136;
$L__BB21_139:
	setp.eq.b32 	%p77, %r437, 7;
	@%p77 bra 	$L__BB21_147;
	setp.eq.b32 	%p78, %r437, 9;
	@%p78 bra 	$L__BB21_143;
	setp.ne.b32 	%p79, %r437, 10;
	@%p79 bra 	$L__BB21_148;
	shl.b64 	%rd174, %rd29, 2;
	add.s64 	%rd175, %rd60, %rd174;
	ld.b32 	%r177, [%rd175];
	cvt.f64.f32 	%rd430, %r177;
	bra.uni 	$L__BB21_150;
$L__BB21_120:
	cvt.s32.s16 	%r178, %rs4;
	and.b32 	%r438, %r178, -2147483648;
	bfe.u32 	%r26, %r25, 10, 5;
	setp.eq.b32 	%p89, %r26, 31;
	@%p89 bra 	$L__BB21_124;
	and.b32 	%r27, %r25, 1023;
	setp.ne.b32 	%p90, %r26, 0;
	@%p90 bra 	$L__BB21_125;
	setp.eq.b32 	%p91, %r27, 0;
	@%p91 bra 	$L__BB21_126;
	clz.b32 	%r181, %r27;
	xor.b32 	%r182, %r181, 31;
	sub.s32 	%r183, 9, %r182;
	shl.b32 	%r184, %r25, %r183;
	shl.b32 	%r185, %r182, 23;
	shl.b32 	%r186, %r184, 14;
	and.b32 	%r187, %r186, 8372224;
	add.s32 	%r188, %r185, %r438;
	add.s32 	%r189, %r188, %r187;
	add.s32 	%r438, %r189, 864026624;
	bra.uni 	$L__BB21_126;
$L__BB21_128:
	setp.gt.s32 	%p82, %r437, 2;
	@%p82 bra 	$L__BB21_132;
	setp.eq.b32 	%p85, %r437, 1;
	@%p85 bra 	$L__BB21_144;
	setp.eq.b32 	%p86, %r437, 2;
	@%p86 bra 	$L__BB21_131;
	bra.uni 	$L__BB21_148;
$L__BB21_131:
	add.s64 	%rd169, %rd60, %rd29;
	ld.s8 	%rd429, [%rd169];
	bra.uni 	$L__BB21_149;
$L__BB21_25:
	selp.b32 	%r5, 15, 127, %p52;
	sub.s32 	%r164, 53, %r4;
	shr.u64 	%rd129, %rd14, %r164;
	mov.b64 	%rd130, -1;
	shl.b64 	%rd131, %rd130, %r164;
	not.b64 	%rd132, %rd131;
	and.b64 	%rd133, %rd132, %rd11;
	sub.s32 	%r165, 52, %r4;
	mov.b64 	%rd134, 1;
	shl.b64 	%rd135, %rd134, %r165;
	setp.gt.u64 	%p57, %rd133, %rd135;
	setp.eq.b64 	%p58, %rd133, %rd135;
	and.b64 	%rd136, %rd129, 1;
	setp.ne.b64 	%p59, %rd136, 0;
	and.pred 	%p60, %p58, %p59;
	or.pred 	%p61, %p57, %p60;
	selp.b64 	%rd137, 1, 0, %p61;
	add.s64 	%rd16, %rd129, %rd137;
	shl.b64 	%rd17, %rd134, %r4;
	setp.eq.b64 	%p62, %rd16, %rd17;
	add.s32 	%r166, %r3, -1022;
	selp.b32 	%r8, %r166, %r6, %p62;
	setp.gt.s32 	%p63, %r8, %r5;
	@%p63 bra 	$L__BB21_27;
	selp.b32 	%r167, 1, 0, %p62;
	shr.u64 	%rd138, %rd16, %r167;
	add.s32 	%r168, %r8, %r5;
	add.s32 	%r169, %r4, -1;
	shl.b32 	%r170, %r168, %r169;
	shl.b64 	%rd139, %rd130, %r169;
	not.b64 	%rd140, %rd139;
	and.b64 	%rd141, %rd138, %rd140;
	cvt.u32.u64 	%r171, %rd141;
	or.b32 	%r431, %r170, %r171;
$L__BB21_27:
	or.b32 	%r172, %r431, %r2;
	cvt.u16.u32 	%rs11, %r172;
	bra.uni 	$L__BB21_28;
$L__BB21_132:
	setp.eq.b32 	%p83, %r437, 3;
	@%p83 bra 	$L__BB21_145;
	setp.eq.b32 	%p84, %r437, 4;
	@%p84 bra 	$L__BB21_134;
	bra.uni 	$L__BB21_148;
$L__BB21_134:
	shl.b64 	%rd165, %rd29, 2;
	add.s64 	%rd166, %rd60, %rd165;
	ld.s32 	%rd429, [%rd166];
	bra.uni 	$L__BB21_149;
$L__BB21_136:
	setp.eq.b32 	%p80, %r437, 5;
	@%p80 bra 	$L__BB21_146;
	setp.eq.b32 	%p81, %r437, 6;
	@%p81 bra 	$L__BB21_138;
	bra.uni 	$L__BB21_148;
$L__BB21_138:
	shl.b64 	%rd162, %rd29, 1;
	add.s64 	%rd163, %rd60, %rd162;
	ld.b16 	%rd429, [%rd163];
	bra.uni 	$L__BB21_149;
$L__BB21_124:
	shl.b32 	%r179, %r25, 13;
	or.b32 	%r180, %r438, %r179;
	or.b32 	%r438, %r180, 2139095040;
	bra.uni 	$L__BB21_126;
$L__BB21_125:
	shl.b32 	%r190, %r26, 23;
	shl.b32 	%r191, %r27, 13;
	or.b32 	%r192, %r190, %r191;
	add.s32 	%r193, %r192, %r438;
	add.s32 	%r438, %r193, 939524096;
$L__BB21_126:
	cvt.f64.f32 	%rd430, %r438;
	bra.uni 	$L__BB21_150;
$L__BB21_21:
	neg.s32 	%r175, %r7;
	shl.b64 	%rd423, %rd14, %r175;
$L__BB21_24:
	or.b64 	%rd151, %rd423, %rd15;
	cvt.u16.u64 	%rs11, %rd151;
$L__BB21_28:
	shl.b64 	%rd152, %rd10, 1;
	add.s64 	%rd153, %rd58, %rd152;
	st.b16 	[%rd153], %rs11;
$L__BB21_32:
	setp.gt.u32 	%p71, %r429, 3;
	@%p71 bra 	$L__BB21_555;
	@%p50 bra 	$L__BB21_35;
	shl.b64 	%rd158, %rd10, 1;
	add.s64 	%rd159, %rd58, %rd158;
	st.b16 	[%rd159+2], 0;
	bra.uni 	$L__BB21_555;
$L__BB21_35:
	setp.ne.b32 	%p72, %r430, 10;
	@%p72 bra 	$L__BB21_37;
	shl.b64 	%rd156, %rd10, 2;
	add.s64 	%rd157, %rd58, %rd156;
	st.b32 	[%rd157+4], 0;
	bra.uni 	$L__BB21_555;
$L__BB21_37:
	shl.b64 	%rd154, %rd10, 3;
	add.s64 	%rd155, %rd58, %rd154;
	st.b64 	[%rd155+8], 0;
	bra.uni 	$L__BB21_555;
$L__BB21_144:
	shl.b64 	%rd170, %rd29, 3;
	add.s64 	%rd171, %rd60, %rd170;
	ld.b64 	%rd429, [%rd171];
	bra.uni 	$L__BB21_149;
$L__BB21_145:
	shl.b64 	%rd167, %rd29, 1;
	add.s64 	%rd168, %rd60, %rd167;
	ld.s16 	%rd429, [%rd168];
	bra.uni 	$L__BB21_149;
$L__BB21_147:
	shl.b64 	%rd160, %rd29, 2;
	add.s64 	%rd161, %rd60, %rd160;
	ld.b32 	%rd429, [%rd161];
	bra.uni 	$L__BB21_149;
$L__BB21_146:
	add.s64 	%rd164, %rd60, %rd29;
	ld.b8 	%rd429, [%rd164];
	bra.uni 	$L__BB21_149;
$L__BB21_143:
	shl.b64 	%rd172, %rd29, 3;
	add.s64 	%rd173, %rd60, %rd172;
	ld.b64 	%rd430, [%rd173];
	bra.uni 	$L__BB21_150;
$L__BB21_148:
	shl.b64 	%rd176, %rd29, 3;
	add.s64 	%rd177, %rd60, %rd176;
	ld.b64 	%rd429, [%rd177];
$L__BB21_149:
	setp.lt.s32 	%p87, %r437, 5;
	cvt.rn.f64.s64 	%rd178, %rd429;
	cvt.rn.f64.u64 	%rd179, %rd429;
	selp.f64 	%rd430, %rd178, %rd179, %p87;
$L__BB21_150:
	setp.gt.u32 	%p92, %r429, 3;
	mov.b32 	%r446, 0f00000000;
	mov.b32 	%r31, %r446;
	@%p92 bra 	$L__BB21_185;
	@%p74 bra 	$L__BB21_161;
	shl.b64 	%rd202, %rd29, 1;
	add.s64 	%rd203, %rd60, %rd202;
	ld.b16 	%rs5, [%rd203+2];
	setp.ne.b32 	%p106, %r437, 13;
	cvt.u32.u16 	%r28, %rs5;
	@%p106 bra 	$L__BB21_154;
	shl.b32 	%r439, %r28, 16;
	bra.uni 	$L__BB21_160;
$L__BB21_161:
	setp.gt.s32 	%p93, %r437, 4;
	@%p93 bra 	$L__BB21_169;
	bra.uni 	$L__BB21_162;
$L__BB21_169:
	setp.gt.s32 	%p94, %r437, 6;
	@%p94 bra 	$L__BB21_173;
	bra.uni 	$L__BB21_170;
$L__BB21_173:
	setp.eq.b32 	%p95, %r437, 7;
	@%p95 bra 	$L__BB21_181;
	setp.eq.b32 	%p96, %r437, 9;
	@%p96 bra 	$L__BB21_177;
	setp.ne.b32 	%p97, %r437, 10;
	@%p97 bra 	$L__BB21_182;
	shl.b64 	%rd196, %rd29, 2;
	add.s64 	%rd197, %rd60, %rd196;
	ld.b32 	%r194, [%rd197+4];
	cvt.f64.f32 	%rd432, %r194;
	bra.uni 	$L__BB21_184;
$L__BB21_154:
	cvt.s32.s16 	%r195, %rs5;
	and.b32 	%r439, %r195, -2147483648;
	bfe.u32 	%r29, %r28, 10, 5;
	setp.eq.b32 	%p107, %r29, 31;
	@%p107 bra 	$L__BB21_158;
	and.b32 	%r30, %r28, 1023;
	setp.ne.b32 	%p108, %r29, 0;
	@%p108 bra 	$L__BB21_159;
	setp.eq.b32 	%p109, %r30, 0;
	@%p109 bra 	$L__BB21_160;
	clz.b32 	%r198, %r30;
	xor.b32 	%r199, %r198, 31;
	sub.s32 	%r200, 9, %r199;
	shl.b32 	%r201, %r28, %r200;
	shl.b32 	%r202, %r199, 23;
	shl.b32 	%r203, %r201, 14;
	and.b32 	%r204, %r203, 8372224;
	add.s32 	%r205, %r202, %r439;
	add.s32 	%r206, %r205, %r204;
	add.s32 	%r439, %r206, 864026624;
	bra.uni 	$L__BB21_160;
$L__BB21_162:
	setp.gt.s32 	%p100, %r437, 2;
	@%p100 bra 	$L__BB21_166;
	setp.eq.b32 	%p103, %r437, 1;
	@%p103 bra 	$L__BB21_178;
	setp.eq.b32 	%p104, %r437, 2;
	@%p104 bra 	$L__BB21_165;
	bra.uni 	$L__BB21_182;
$L__BB21_165:
	add.s64 	%rd191, %rd60, %rd29;
	ld.s8 	%rd431, [%rd191+1];
	bra.uni 	$L__BB21_183;
$L__BB21_166:
	setp.eq.b32 	%p101, %r437, 3;
	@%p101 bra 	$L__BB21_179;
	setp.eq.b32 	%p102, %r437, 4;
	@%p102 bra 	$L__BB21_168;
	bra.uni 	$L__BB21_182;
$L__BB21_168:
	shl.b64 	%rd187, %rd29, 2;
	add.s64 	%rd188, %rd60, %rd187;
	ld.s32 	%rd431, [%rd188+4];
	bra.uni 	$L__BB21_183;
$L__BB21_170:
	setp.eq.b32 	%p98, %r437, 5;
	@%p98 bra 	$L__BB21_180;
	setp.eq.b32 	%p99, %r437, 6;
	@%p99 bra 	$L__BB21_172;
	bra.uni 	$L__BB21_182;
$L__BB21_172:
	shl.b64 	%rd184, %rd29, 1;
	add.s64 	%rd185, %rd60, %rd184;
	ld.b16 	%rd431, [%rd185+2];
	bra.uni 	$L__BB21_183;
$L__BB21_158:
	shl.b32 	%r196, %r28, 13;
	or.b32 	%r197, %r439, %r196;
	or.b32 	%r439, %r197, 2139095040;
	bra.uni 	$L__BB21_160;
$L__BB21_159:
	shl.b32 	%r207, %r29, 23;
	shl.b32 	%r208, %r30, 13;
	or.b32 	%r209, %r207, %r208;
	add.s32 	%r210, %r209, %r439;
	add.s32 	%r439, %r210, 939524096;
$L__BB21_160:
	cvt.f64.f32 	%rd432, %r439;
	bra.uni 	$L__BB21_184;
$L__BB21_178:
	shl.b64 	%rd192, %rd29, 3;
	add.s64 	%rd193, %rd60, %rd192;
	ld.b64 	%rd431, [%rd193+8];
	bra.uni 	$L__BB21_183;
$L__BB21_179:
	shl.b64 	%rd189, %rd29, 1;
	add.s64 	%rd190, %rd60, %rd189;
	ld.s16 	%rd431, [%rd190+2];
	bra.uni 	$L__BB21_183;
$L__BB21_181:
	shl.b64 	%rd182, %rd29, 2;
	add.s64 	%rd183, %rd60, %rd182;
	ld.b32 	%rd431, [%rd183+4];
	bra.uni 	$L__BB21_183;
$L__BB21_180:
	add.s64 	%rd186, %rd60, %rd29;
	ld.b8 	%rd431, [%rd186+1];
	bra.uni 	$L__BB21_183;
$L__BB21_177:
	shl.b64 	%rd194, %rd29, 3;
	add.s64 	%rd195, %rd60, %rd194;
	ld.b64 	%rd432, [%rd195+8];
	bra.uni 	$L__BB21_184;
$L__BB21_182:
	shl.b64 	%rd198, %rd29, 3;
	add.s64 	%rd199, %rd60, %rd198;
	ld.b64 	%rd431, [%rd199+8];
$L__BB21_183:
	setp.lt.s32 	%p105, %r437, 5;
	cvt.rn.f64.s64 	%rd200, %rd431;
	cvt.rn.f64.u64 	%rd201, %rd431;
	selp.f64 	%rd432, %rd200, %rd201, %p105;
$L__BB21_184:
	cvt.rn.f32.f64 	%r31, %rd432;
$L__BB21_185:
)QPTX";
        result += R"QPTX(
	ld.param.b32 	%r94, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_12];
	ld.param.b64 	%rd61, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_3];
	setp.gt.u32 	%p110, %r95, 10;
	mov.b32 	%r447, %r446;
	@%p110 bra 	$L__BB21_333;
	mov.b32 	%r211, 1;
	shl.b32 	%r212, %r211, %r95;
	and.b32 	%r213, %r212, 1033;
	setp.ne.b32 	%p111, %r213, 0;
	mov.b32 	%r447, %r446;
	@%p111 bra 	$L__BB21_187;
	bra.uni 	$L__BB21_333;
$L__BB21_187:
	setp.eq.b32 	%p112, %r94, 0;
	@%p112 bra 	$L__BB21_256;
	@%p328 bra 	$L__BB21_192;
	mov.b32 	%r440, 12;
	@%p331 bra 	$L__BB21_196;
	mov.b32 	%r440, %r92;
	@%p332 bra 	$L__BB21_191;
	bra.uni 	$L__BB21_196;
$L__BB21_191:
	mov.b32 	%r440, 13;
	bra.uni 	$L__BB21_196;
$L__BB21_256:
	@%p328 bra 	$L__BB21_260;
	mov.b32 	%r443, 12;
	@%p331 bra 	$L__BB21_264;
	mov.b32 	%r443, %r92;
	@%p332 bra 	$L__BB21_259;
	bra.uni 	$L__BB21_264;
$L__BB21_259:
	mov.b32 	%r443, 13;
	bra.uni 	$L__BB21_264;
$L__BB21_192:
	@%p329 bra 	$L__BB21_195;
	mov.b32 	%r440, %r92;
	@%p330 bra 	$L__BB21_196;
	mov.b32 	%r440, 9;
	bra.uni 	$L__BB21_196;
$L__BB21_260:
	@%p329 bra 	$L__BB21_263;
	mov.b32 	%r443, %r92;
	@%p330 bra 	$L__BB21_264;
	mov.b32 	%r443, 9;
	bra.uni 	$L__BB21_264;
$L__BB21_195:
	mov.b32 	%r440, 10;
$L__BB21_196:
	cvt.u32.u64 	%r22, %rd65;
	and.b32 	%r33, %r440, -2;
	setp.ne.b32 	%p113, %r33, 12;
	@%p113 bra 	$L__BB21_206;
	setp.ne.b32 	%p126, %r440, 13;
	and.b32 	%r34, %r22, 65535;
	@%p126 bra 	$L__BB21_199;
	shl.b32 	%r441, %r34, 16;
	bra.uni 	$L__BB21_205;
$L__BB21_206:
	setp.gt.s32 	%p114, %r440, 5;
	@%p114 bra 	$L__BB21_214;
	setp.gt.s32 	%p120, %r440, 3;
	@%p120 bra 	$L__BB21_211;
	setp.eq.b32 	%p123, %r440, 2;
	@%p123 bra 	$L__BB21_221;
	setp.eq.b32 	%p124, %r440, 3;
	mov.b64 	%rd433, %rd65;
	@%p124 bra 	$L__BB21_210;
	bra.uni 	$L__BB21_224;
$L__BB21_210:
	cvt.s64.s16 	%rd433, %rd65;
	bra.uni 	$L__BB21_224;
$L__BB21_199:
	cvt.u16.u64 	%rs2, %rd65;
	cvt.s32.s16 	%r214, %rs2;
	and.b32 	%r441, %r214, -2147483648;
	bfe.u32 	%r35, %r22, 10, 5;
	setp.eq.b32 	%p127, %r35, 31;
	@%p127 bra 	$L__BB21_203;
	and.b32 	%r36, %r22, 1023;
	setp.ne.b32 	%p128, %r35, 0;
	@%p128 bra 	$L__BB21_204;
	setp.eq.b32 	%p129, %r36, 0;
	@%p129 bra 	$L__BB21_205;
	clz.b32 	%r217, %r36;
	xor.b32 	%r218, %r217, 31;
	sub.s32 	%r219, 9, %r218;
	shl.b32 	%r220, %r22, %r219;
	shl.b32 	%r221, %r218, 23;
	shl.b32 	%r222, %r220, 14;
	and.b32 	%r223, %r222, 8372224;
	add.s32 	%r224, %r221, %r441;
	add.s32 	%r225, %r224, %r223;
	add.s32 	%r441, %r225, 864026624;
	bra.uni 	$L__BB21_205;
$L__BB21_214:
	setp.gt.s32 	%p115, %r440, 8;
	@%p115 bra 	$L__BB21_218;
	setp.eq.b32 	%p118, %r440, 6;
	@%p118 bra 	$L__BB21_223;
	setp.eq.b32 	%p119, %r440, 7;
	mov.b64 	%rd433, %rd65;
	@%p119 bra 	$L__BB21_217;
	bra.uni 	$L__BB21_224;
$L__BB21_217:
	and.b64 	%rd433, %rd65, 4294967295;
	bra.uni 	$L__BB21_224;
$L__BB21_211:
	setp.eq.b32 	%p121, %r440, 4;
	@%p121 bra 	$L__BB21_222;
	setp.eq.b32 	%p122, %r440, 5;
	mov.b64 	%rd433, %rd65;
	@%p122 bra 	$L__BB21_213;
	bra.uni 	$L__BB21_224;
$L__BB21_213:
	and.b64 	%rd433, %rd65, 255;
	bra.uni 	$L__BB21_224;
$L__BB21_218:
	setp.eq.b32 	%p116, %r440, 9;
	mov.b64 	%rd438, %rd65;
	@%p116 bra 	$L__BB21_225;
	setp.ne.b32 	%p117, %r440, 10;
	mov.b64 	%rd433, %rd65;
	@%p117 bra 	$L__BB21_224;
	cvt.f64.f32 	%rd438, %r22;
	bra.uni 	$L__BB21_225;
$L__BB21_263:
	mov.b32 	%r443, 10;
$L__BB21_264:
	and.b32 	%r41, %r443, -2;
	setp.ne.b32 	%p146, %r41, 12;
	@%p146 bra 	$L__BB21_274;
	shl.b64 	%rd228, %rd29, 1;
	add.s64 	%rd229, %rd61, %rd228;
	ld.b16 	%rs6, [%rd229];
	setp.ne.b32 	%p160, %r443, 13;
	cvt.u32.u16 	%r42, %rs6;
	@%p160 bra 	$L__BB21_267;
	shl.b32 	%r444, %r42, 16;
	bra.uni 	$L__BB21_273;
$L__BB21_274:
	setp.gt.s32 	%p147, %r443, 4;
	@%p147 bra 	$L__BB21_282;
	bra.uni 	$L__BB21_275;
$L__BB21_282:
	setp.gt.s32 	%p148, %r443, 6;
	@%p148 bra 	$L__BB21_286;
	bra.uni 	$L__BB21_283;
$L__BB21_286:
	setp.eq.b32 	%p149, %r443, 7;
	@%p149 bra 	$L__BB21_294;
	setp.eq.b32 	%p150, %r443, 9;
	@%p150 bra 	$L__BB21_290;
	setp.ne.b32 	%p151, %r443, 10;
	@%p151 bra 	$L__BB21_295;
	shl.b64 	%rd222, %rd29, 2;
	add.s64 	%rd223, %rd61, %rd222;
	ld.b32 	%r246, [%rd223];
	cvt.f64.f32 	%rd438, %r246;
	bra.uni 	$L__BB21_297;
$L__BB21_267:
	cvt.s32.s16 	%r247, %rs6;
	and.b32 	%r444, %r247, -2147483648;
	bfe.u32 	%r43, %r42, 10, 5;
	setp.eq.b32 	%p161, %r43, 31;
	@%p161 bra 	$L__BB21_271;
	and.b32 	%r44, %r42, 1023;
	setp.ne.b32 	%p162, %r43, 0;
	@%p162 bra 	$L__BB21_272;
	setp.eq.b32 	%p163, %r44, 0;
	@%p163 bra 	$L__BB21_273;
	clz.b32 	%r250, %r44;
	xor.b32 	%r251, %r250, 31;
	sub.s32 	%r252, 9, %r251;
	shl.b32 	%r253, %r42, %r252;
	shl.b32 	%r254, %r251, 23;
	shl.b32 	%r255, %r253, 14;
	and.b32 	%r256, %r255, 8372224;
	add.s32 	%r257, %r254, %r444;
	add.s32 	%r258, %r257, %r256;
	add.s32 	%r444, %r258, 864026624;
	bra.uni 	$L__BB21_273;
$L__BB21_275:
	setp.gt.s32 	%p154, %r443, 2;
	@%p154 bra 	$L__BB21_279;
	setp.eq.b32 	%p157, %r443, 1;
	@%p157 bra 	$L__BB21_291;
	setp.eq.b32 	%p158, %r443, 2;
	@%p158 bra 	$L__BB21_278;
	bra.uni 	$L__BB21_295;
$L__BB21_278:
	add.s64 	%rd217, %rd61, %rd29;
	ld.s8 	%rd435, [%rd217];
	bra.uni 	$L__BB21_296;
$L__BB21_203:
	shl.b32 	%r215, %r34, 13;
	or.b32 	%r216, %r441, %r215;
	or.b32 	%r441, %r216, 2139095040;
	bra.uni 	$L__BB21_205;
$L__BB21_204:
	shl.b32 	%r226, %r35, 23;
	shl.b32 	%r227, %r36, 13;
	or.b32 	%r228, %r226, %r227;
	add.s32 	%r229, %r228, %r441;
	add.s32 	%r441, %r229, 939524096;
$L__BB21_205:
	cvt.f64.f32 	%rd438, %r441;
	bra.uni 	$L__BB21_225;
$L__BB21_279:
	setp.eq.b32 	%p155, %r443, 3;
	@%p155 bra 	$L__BB21_292;
	setp.eq.b32 	%p156, %r443, 4;
	@%p156 bra 	$L__BB21_281;
	bra.uni 	$L__BB21_295;
$L__BB21_281:
	shl.b64 	%rd213, %rd29, 2;
	add.s64 	%rd214, %rd61, %rd213;
	ld.s32 	%rd435, [%rd214];
	bra.uni 	$L__BB21_296;
$L__BB21_283:
	setp.eq.b32 	%p152, %r443, 5;
	@%p152 bra 	$L__BB21_293;
	setp.eq.b32 	%p153, %r443, 6;
	@%p153 bra 	$L__BB21_285;
	bra.uni 	$L__BB21_295;
$L__BB21_285:
	shl.b64 	%rd210, %rd29, 1;
	add.s64 	%rd211, %rd61, %rd210;
	ld.b16 	%rd435, [%rd211];
	bra.uni 	$L__BB21_296;
$L__BB21_221:
	cvt.s64.s8 	%rd433, %rd65;
	bra.uni 	$L__BB21_224;
$L__BB21_223:
	and.b64 	%rd433, %rd65, 65535;
	bra.uni 	$L__BB21_224;
$L__BB21_222:
	cvt.s64.s32 	%rd433, %rd65;
$L__BB21_224:
	setp.lt.s32 	%p125, %r440, 5;
	cvt.rn.f64.s64 	%rd204, %rd433;
	cvt.rn.f64.u64 	%rd205, %rd433;
	selp.f64 	%rd438, %rd204, %rd205, %p125;
$L__BB21_225:
	mov.b32 	%r446, 0f00000000;
	@%p92 bra 	$L__BB21_332;
	shr.u64 	%rd27, %rd65, 16;
	@%p113 bra 	$L__BB21_236;
	setp.ne.b32 	%p142, %r440, 13;
	cvt.u32.u64 	%r37, %rd27;
	and.b32 	%r38, %r37, 65535;
	@%p142 bra 	$L__BB21_229;
	shl.b32 	%r442, %r38, 16;
	bra.uni 	$L__BB21_235;
$L__BB21_236:
	setp.gt.s32 	%p130, %r440, 5;
	@%p130 bra 	$L__BB21_244;
	shr.u64 	%rd28, %rd65, 8;
	setp.gt.s32 	%p136, %r440, 3;
	@%p136 bra 	$L__BB21_241;
	setp.eq.b32 	%p139, %r440, 2;
	@%p139 bra 	$L__BB21_251;
	setp.eq.b32 	%p140, %r440, 3;
	@%p140 bra 	$L__BB21_240;
	bra.uni 	$L__BB21_254;
$L__BB21_240:
	cvt.s64.s16 	%rd434, %rd27;
	bra.uni 	$L__BB21_254;
$L__BB21_229:
	cvt.u16.u64 	%rs3, %rd27;
	cvt.s32.s16 	%r230, %rs3;
	and.b32 	%r442, %r230, -2147483648;
	bfe.u32 	%r39, %r37, 10, 5;
	setp.eq.b32 	%p143, %r39, 31;
	@%p143 bra 	$L__BB21_233;
	and.b32 	%r40, %r37, 1023;
	setp.ne.b32 	%p144, %r39, 0;
	@%p144 bra 	$L__BB21_234;
	setp.eq.b32 	%p145, %r40, 0;
	@%p145 bra 	$L__BB21_235;
	clz.b32 	%r233, %r40;
	xor.b32 	%r234, %r233, 31;
	sub.s32 	%r235, 9, %r234;
	shl.b32 	%r236, %r37, %r235;
	shl.b32 	%r237, %r234, 23;
	shl.b32 	%r238, %r236, 14;
	and.b32 	%r239, %r238, 8372224;
	add.s32 	%r240, %r237, %r442;
	add.s32 	%r241, %r240, %r239;
	add.s32 	%r442, %r241, 864026624;
	bra.uni 	$L__BB21_235;
$L__BB21_244:
	setp.gt.s32 	%p131, %r440, 8;
	@%p131 bra 	$L__BB21_248;
	setp.eq.b32 	%p134, %r440, 6;
	@%p134 bra 	$L__BB21_253;
	setp.eq.b32 	%p135, %r440, 7;
	@%p135 bra 	$L__BB21_247;
	bra.uni 	$L__BB21_254;
$L__BB21_247:
	shr.u64 	%rd434, %rd65, 32;
	bra.uni 	$L__BB21_254;
$L__BB21_241:
	setp.eq.b32 	%p137, %r440, 4;
	@%p137 bra 	$L__BB21_252;
	setp.eq.b32 	%p138, %r440, 5;
	@%p138 bra 	$L__BB21_243;
	bra.uni 	$L__BB21_254;
$L__BB21_243:
	and.b64 	%rd434, %rd28, 255;
	bra.uni 	$L__BB21_254;
$L__BB21_248:
	setp.eq.b32 	%p132, %r440, 9;
	@%p132 bra 	$L__BB21_255;
	setp.ne.b32 	%p133, %r440, 10;
	@%p133 bra 	$L__BB21_254;
	{ .reg .b32 tmp; mov.b64 {tmp, %r23}, %rd65; }
	cvt.f64.f32 	%rd434, %r23;
	bra.uni 	$L__BB21_255;
$L__BB21_271:
	shl.b32 	%r248, %r42, 13;
	or.b32 	%r249, %r444, %r248;
	or.b32 	%r444, %r249, 2139095040;
	bra.uni 	$L__BB21_273;
$L__BB21_272:
	shl.b32 	%r259, %r43, 23;
	shl.b32 	%r260, %r44, 13;
	or.b32 	%r261, %r259, %r260;
	add.s32 	%r262, %r261, %r444;
	add.s32 	%r444, %r262, 939524096;
$L__BB21_273:
	cvt.f64.f32 	%rd438, %r444;
	bra.uni 	$L__BB21_297;
$L__BB21_233:
	shl.b32 	%r231, %r38, 13;
	or.b32 	%r232, %r442, %r231;
	or.b32 	%r442, %r232, 2139095040;
	bra.uni 	$L__BB21_235;
$L__BB21_234:
	shl.b32 	%r242, %r39, 23;
	shl.b32 	%r243, %r40, 13;
	or.b32 	%r244, %r242, %r243;
	add.s32 	%r245, %r244, %r442;
	add.s32 	%r442, %r245, 939524096;
$L__BB21_235:
	cvt.f64.f32 	%rd434, %r442;
	bra.uni 	$L__BB21_255;
$L__BB21_291:
	shl.b64 	%rd218, %rd29, 3;
	add.s64 	%rd219, %rd61, %rd218;
	ld.b64 	%rd435, [%rd219];
	bra.uni 	$L__BB21_296;
$L__BB21_292:
	shl.b64 	%rd215, %rd29, 1;
	add.s64 	%rd216, %rd61, %rd215;
	ld.s16 	%rd435, [%rd216];
	bra.uni 	$L__BB21_296;
$L__BB21_294:
	shl.b64 	%rd208, %rd29, 2;
	add.s64 	%rd209, %rd61, %rd208;
	ld.b32 	%rd435, [%rd209];
	bra.uni 	$L__BB21_296;
$L__BB21_293:
	add.s64 	%rd212, %rd61, %rd29;
	ld.b8 	%rd435, [%rd212];
	bra.uni 	$L__BB21_296;
$L__BB21_290:
	shl.b64 	%rd220, %rd29, 3;
	add.s64 	%rd221, %rd61, %rd220;
	ld.b64 	%rd438, [%rd221];
	bra.uni 	$L__BB21_297;
$L__BB21_295:
	shl.b64 	%rd224, %rd29, 3;
	add.s64 	%rd225, %rd61, %rd224;
	ld.b64 	%rd435, [%rd225];
$L__BB21_296:
	setp.lt.s32 	%p159, %r443, 5;
	cvt.rn.f64.s64 	%rd226, %rd435;
	cvt.rn.f64.u64 	%rd227, %rd435;
	selp.f64 	%rd438, %rd226, %rd227, %p159;
$L__BB21_297:
	mov.b32 	%r446, 0f00000000;
	@%p92 bra 	$L__BB21_332;
	@%p146 bra 	$L__BB21_308;
	shl.b64 	%rd250, %rd29, 1;
	add.s64 	%rd251, %rd61, %rd250;
	ld.b16 	%rs7, [%rd251+2];
	setp.ne.b32 	%p177, %r443, 13;
	cvt.u32.u16 	%r45, %rs7;
	@%p177 bra 	$L__BB21_301;
	shl.b32 	%r445, %r45, 16;
	bra.uni 	$L__BB21_307;
$L__BB21_308:
	setp.gt.s32 	%p164, %r443, 4;
	@%p164 bra 	$L__BB21_316;
	bra.uni 	$L__BB21_309;
$L__BB21_316:
	setp.gt.s32 	%p165, %r443, 6;
	@%p165 bra 	$L__BB21_320;
	bra.uni 	$L__BB21_317;
$L__BB21_320:
	setp.eq.b32 	%p166, %r443, 7;
	@%p166 bra 	$L__BB21_328;
	setp.eq.b32 	%p167, %r443, 9;
	@%p167 bra 	$L__BB21_324;
	setp.ne.b32 	%p168, %r443, 10;
	@%p168 bra 	$L__BB21_329;
	shl.b64 	%rd244, %rd29, 2;
	add.s64 	%rd245, %rd61, %rd244;
	ld.b32 	%r263, [%rd245+4];
	cvt.f64.f32 	%rd437, %r263;
	bra.uni 	$L__BB21_331;
$L__BB21_301:
	cvt.s32.s16 	%r264, %rs7;
	and.b32 	%r445, %r264, -2147483648;
	bfe.u32 	%r46, %r45, 10, 5;
	setp.eq.b32 	%p178, %r46, 31;
	@%p178 bra 	$L__BB21_305;
	and.b32 	%r47, %r45, 1023;
	setp.ne.b32 	%p179, %r46, 0;
	@%p179 bra 	$L__BB21_306;
	setp.eq.b32 	%p180, %r47, 0;
	@%p180 bra 	$L__BB21_307;
	clz.b32 	%r267, %r47;
	xor.b32 	%r268, %r267, 31;
	sub.s32 	%r269, 9, %r268;
	shl.b32 	%r270, %r45, %r269;
	shl.b32 	%r271, %r268, 23;
	shl.b32 	%r272, %r270, 14;
	and.b32 	%r273, %r272, 8372224;
	add.s32 	%r274, %r271, %r445;
	add.s32 	%r275, %r274, %r273;
	add.s32 	%r445, %r275, 864026624;
	bra.uni 	$L__BB21_307;
$L__BB21_309:
	setp.gt.s32 	%p171, %r443, 2;
	@%p171 bra 	$L__BB21_313;
	setp.eq.b32 	%p174, %r443, 1;
	@%p174 bra 	$L__BB21_325;
	setp.eq.b32 	%p175, %r443, 2;
	@%p175 bra 	$L__BB21_312;
	bra.uni 	$L__BB21_329;
$L__BB21_312:
	add.s64 	%rd239, %rd61, %rd29;
	ld.s8 	%rd436, [%rd239+1];
	bra.uni 	$L__BB21_330;
$L__BB21_313:
	setp.eq.b32 	%p172, %r443, 3;
	@%p172 bra 	$L__BB21_326;
	setp.eq.b32 	%p173, %r443, 4;
	@%p173 bra 	$L__BB21_315;
	bra.uni 	$L__BB21_329;
$L__BB21_315:
	shl.b64 	%rd235, %rd29, 2;
	add.s64 	%rd236, %rd61, %rd235;
	ld.s32 	%rd436, [%rd236+4];
	bra.uni 	$L__BB21_330;
$L__BB21_317:
	setp.eq.b32 	%p169, %r443, 5;
	@%p169 bra 	$L__BB21_327;
	setp.eq.b32 	%p170, %r443, 6;
	@%p170 bra 	$L__BB21_319;
	bra.uni 	$L__BB21_329;
$L__BB21_319:
	shl.b64 	%rd232, %rd29, 1;
	add.s64 	%rd233, %rd61, %rd232;
	ld.b16 	%rd436, [%rd233+2];
	bra.uni 	$L__BB21_330;
$L__BB21_251:
	cvt.s64.s8 	%rd434, %rd28;
	bra.uni 	$L__BB21_254;
$L__BB21_253:
	and.b64 	%rd434, %rd27, 65535;
	bra.uni 	$L__BB21_254;
$L__BB21_252:
	shr.s64 	%rd434, %rd65, 32;
$L__BB21_254:
	setp.lt.s32 	%p141, %r440, 5;
	cvt.rn.f64.s64 	%rd206, %rd434;
	cvt.rn.f64.u64 	%rd207, %rd434;
	selp.f64 	%rd434, %rd206, %rd207, %p141;
$L__BB21_255:
	cvt.rn.f32.f64 	%r446, %rd434;
	bra.uni 	$L__BB21_332;
$L__BB21_305:
	shl.b32 	%r265, %r45, 13;
	or.b32 	%r266, %r445, %r265;
	or.b32 	%r445, %r266, 2139095040;
	bra.uni 	$L__BB21_307;
$L__BB21_306:
	shl.b32 	%r276, %r46, 23;
	shl.b32 	%r277, %r47, 13;
	or.b32 	%r278, %r276, %r277;
	add.s32 	%r279, %r278, %r445;
	add.s32 	%r445, %r279, 939524096;
$L__BB21_307:
	cvt.f64.f32 	%rd437, %r445;
	bra.uni 	$L__BB21_331;
$L__BB21_325:
	shl.b64 	%rd240, %rd29, 3;
	add.s64 	%rd241, %rd61, %rd240;
	ld.b64 	%rd436, [%rd241+8];
	bra.uni 	$L__BB21_330;
$L__BB21_326:
	shl.b64 	%rd237, %rd29, 1;
	add.s64 	%rd238, %rd61, %rd237;
	ld.s16 	%rd436, [%rd238+2];
	bra.uni 	$L__BB21_330;
$L__BB21_328:
	shl.b64 	%rd230, %rd29, 2;
	add.s64 	%rd231, %rd61, %rd230;
	ld.b32 	%rd436, [%rd231+4];
	bra.uni 	$L__BB21_330;
$L__BB21_327:
	add.s64 	%rd234, %rd61, %rd29;
	ld.b8 	%rd436, [%rd234+1];
	bra.uni 	$L__BB21_330;
$L__BB21_324:
	shl.b64 	%rd242, %rd29, 3;
	add.s64 	%rd243, %rd61, %rd242;
	ld.b64 	%rd437, [%rd243+8];
	bra.uni 	$L__BB21_331;
$L__BB21_329:
	shl.b64 	%rd246, %rd29, 3;
	add.s64 	%rd247, %rd61, %rd246;
	ld.b64 	%rd436, [%rd247+8];
$L__BB21_330:
	setp.lt.s32 	%p176, %r443, 5;
	cvt.rn.f64.s64 	%rd248, %rd436;
	cvt.rn.f64.u64 	%rd249, %rd436;
	selp.f64 	%rd437, %rd248, %rd249, %p176;
$L__BB21_331:
	cvt.rn.f32.f64 	%r446, %rd437;
$L__BB21_332:
	cvt.rn.f32.f64 	%r447, %rd438;
$L__BB21_333:
	cvt.rn.f32.f64 	%r32, %rd430;
	setp.ne.b32 	%p181, %r94, 1;
	mov.b32 	%r448, %r446;
	mov.b32 	%r48, %r447;
	mov.b32 	%r49, %r32;
	mov.b32 	%r50, %r31;
	@%p181 bra 	$L__BB21_335;
	mov.b32 	%r448, %r31;
	mov.b32 	%r48, %r32;
	mov.b32 	%r49, %r447;
	mov.b32 	%r50, %r446;
$L__BB21_335:
	ld.param.b64 	%rd67, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_14];
	ld.param.b32 	%r93, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_11];
	setp.gt.s32 	%p182, %r95, 2;
	@%p182 bra 	$L__BB21_340;
	setp.eq.b32 	%p185, %r95, 0;
	@%p185 bra 	$L__BB21_344;
	setp.eq.b32 	%p186, %r95, 1;
	@%p186 bra 	$L__BB21_338;
	bra.uni 	$L__BB21_445;
$L__BB21_338:
	neg.f32 	%r66, %r49;
	@%p328 bra 	$L__BB21_391;
	mov.b32 	%r452, 12;
	@%p331 bra 	$L__BB21_395;
	mov.b32 	%r452, %r92;
	@%p332 bra 	$L__BB21_390;
	bra.uni 	$L__BB21_395;
$L__BB21_390:
	mov.b32 	%r452, 13;
	bra.uni 	$L__BB21_395;
$L__BB21_340:
	setp.eq.b32 	%p183, %r95, 3;
	@%p183 bra 	$L__BB21_342;
	setp.eq.b32 	%p184, %r95, 10;
	@%p184 bra 	$L__BB21_342;
	bra.uni 	$L__BB21_445;
$L__BB21_342:
	setp.gt.s32 	%p189, %r93, 2;
	@%p189 bra 	$L__BB21_434;
	bra.uni 	$L__BB21_343;
$L__BB21_434:
	setp.eq.b32 	%p190, %r93, 3;
	@%p190 bra 	$L__BB21_438;
	setp.eq.b32 	%p191, %r93, 4;
	@%p191 bra 	$L__BB21_439;
	setp.eq.b32 	%p192, %r93, 5;
	@%p192 bra 	$L__BB21_437;
	bra.uni 	$L__BB21_440;
$L__BB21_437:
	setp.gt.f32 	%p333, %r49, %r48;
	bra.uni 	$L__BB21_441;
$L__BB21_445:
	add.s32 	%r372, %r95, -5;
	setp.gt.u32 	%p278, %r372, 1;
	@%p278 bra 	$L__BB21_555;
	@%p328 bra 	$L__BB21_450;
	mov.b32 	%r455, 12;
	@%p331 bra 	$L__BB21_454;
	mov.b32 	%r455, %r92;
	@%p332 bra 	$L__BB21_449;
	bra.uni 	$L__BB21_454;
$L__BB21_449:
	mov.b32 	%r455, 13;
	bra.uni 	$L__BB21_454;
$L__BB21_344:
	st.local.b32 	[%rd2], %r49;
	st.local.b32 	[%rd2+4], %r50;
	st.local.b32 	[%rd3], %r48;
	st.local.b32 	[%rd3+4], %r448;
	{
	.param .align 4 .b8 	param0[8];
	.param .align 4 .b8 	param1[8];
	.param .b32 	param2;
	.param .b32 	param3;
	.param .b64 	param4;
	.param .align 4 .b8 	retval0[8];
	st.param.b64 	[param4], %rd67;
	st.param.b32 	[param3], %r93;
	st.param.b32 	[param2], %r92;
	cvta.to.local.u64 	%rd313, %rd70;
	ld.local.b32 	%r324, [%rd313+4];
	st.param.b32 	[param1+4], %r324;
	ld.local.b32 	%r325, [%rd313];
	st.param.b32 	[param1], %r325;
	cvta.to.local.u64 	%rd314, %rd69;
	ld.local.b32 	%r326, [%rd314+4];
	st.param.b32 	[param0+4], %r326;
	ld.local.b32 	%r327, [%rd314];
	st.param.b32 	[param0], %r327;
	call.uni (retval0), _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj, (param0, param1, param2, param3, param4);
	ld.param.b32 	%r328, [retval0+4];
	ld.param.b32 	%r329, [retval0];
	}
	@%p328 bra 	$L__BB21_348;
	mov.b32 	%r449, 12;
	@%p331 bra 	$L__BB21_352;
	mov.b32 	%r449, %r92;
	@%p332 bra 	$L__BB21_347;
	bra.uni 	$L__BB21_352;
$L__BB21_347:
	mov.b32 	%r449, 13;
	bra.uni 	$L__BB21_352;
$L__BB21_343:
	setp.eq.f32 	%p187, %r447, %r32;
	setp.eq.f32 	%p188, %r446, %r31;
	and.pred 	%p333, %p187, %p188;
	setp.eq.b32 	%p193, %r93, 1;
	@%p193 bra 	$L__BB21_441;
	setp.eq.b32 	%p194, %r93, 2;
	@%p194 bra 	$L__BB21_433;
	bra.uni 	$L__BB21_440;
$L__BB21_433:
	not.pred 	%p333, %p333;
	bra.uni 	$L__BB21_441;
$L__BB21_391:
	@%p329 bra 	$L__BB21_394;
	mov.b32 	%r452, %r92;
	@%p330 bra 	$L__BB21_395;
	mov.b32 	%r452, 9;
	bra.uni 	$L__BB21_395;
$L__BB21_348:
	@%p329 bra 	$L__BB21_351;
	mov.b32 	%r449, %r92;
	@%p330 bra 	$L__BB21_352;
	mov.b32 	%r449, 9;
	bra.uni 	$L__BB21_352;
$L__BB21_438:
	setp.lt.f32 	%p333, %r49, %r48;
	bra.uni 	$L__BB21_441;
$L__BB21_439:
	setp.le.f32 	%p333, %r49, %r48;
	bra.uni 	$L__BB21_441;
$L__BB21_440:
	setp.ge.f32 	%p333, %r49, %r48;
$L__BB21_441:
	setp.ne.b32 	%p195, %r95, 3;
	@%p195 bra 	$L__BB21_443;
	selp.b16 	%rs10, 1, 0, %p333;
	add.s64 	%rd252, %rd58, %rd66;
	st.b8 	[%rd252], %rs10;
	bra.uni 	$L__BB21_555;
$L__BB21_443:
	@%p333 bra 	$L__BB21_555;
	mov.b32 	%r281, 1;
	atom.global.or.b32 %r280, [%rd67], %r281;
	bra.uni 	$L__BB21_555;
$L__BB21_450:
	@%p329 bra 	$L__BB21_453;
	mov.b32 	%r455, %r92;
	@%p330 bra 	$L__BB21_454;
	mov.b32 	%r455, 9;
	bra.uni 	$L__BB21_454;
$L__BB21_394:
	mov.b32 	%r452, 10;
$L__BB21_395:
	cvt.f64.f32 	%rd44, %r66;
	and.b32 	%r68, %r452, -2;
	setp.ne.b32 	%p196, %r68, 12;
	@%p196 bra 	$L__BB21_410;
	shr.u64 	%rd46, %rd44, 48;
	cvt.u32.u64 	%r282, %rd46;
	and.b32 	%r69, %r282, 32768;
	shr.u64 	%rd257, %rd44, 52;
	cvt.u32.u64 	%r283, %rd257;
	and.b32 	%r70, %r283, 2047;
	setp.eq.b32 	%p199, %r70, 0;
	@%p199 bra 	$L__BB21_399;
	and.b64 	%rd45, %rd44, 4503599627370495;
	setp.eq.b32 	%p198, %r452, 12;
	selp.b32 	%r71, 11, 8, %p198;
	selp.b32 	%r453, 31744, 32640, %p198;
	setp.ne.b32 	%p200, %r70, 2047;
	@%p200 bra 	$L__BB21_400;
	setp.eq.b64 	%p201, %rd45, 0;
	add.s32 	%r284, %r71, -2;
	mov.b32 	%r285, 1;
	shl.b32 	%r286, %r285, %r284;
	selp.b32 	%r287, 0, %r286, %p201;
	or.b32 	%r288, %r69, %r287;
	or.b32 	%r289, %r288, %r453;
	cvt.u16.u32 	%rs15, %r289;
	bra.uni 	$L__BB21_409;
$L__BB21_410:
	setp.ne.b32 	%p197, %r452, 10;
	@%p197 bra 	$L__BB21_412;
	shl.b64 	%rd255, %rd29, 2;
	add.s64 	%rd256, %rd58, %rd255;
	st.b32 	[%rd256], %r66;
	bra.uni 	$L__BB21_413;
$L__BB21_412:
	shl.b64 	%rd253, %rd29, 3;
	add.s64 	%rd254, %rd58, %rd253;
	st.b64 	[%rd254], %rd44;
	bra.uni 	$L__BB21_413;
$L__BB21_351:
	mov.b32 	%r449, 10;
$L__BB21_352:
	cvt.f64.f32 	%rd30, %r329;
	and.b32 	%r51, %r449, -2;
	setp.ne.b32 	%p237, %r51, 12;
	@%p237 bra 	$L__BB21_367;
	shr.u64 	%rd32, %rd30, 48;
	cvt.u32.u64 	%r330, %rd32;
	and.b32 	%r52, %r330, 32768;
	shr.u64 	%rd319, %rd30, 52;
	cvt.u32.u64 	%r331, %rd319;
	and.b32 	%r53, %r331, 2047;
	setp.eq.b32 	%p240, %r53, 0;
	@%p240 bra 	$L__BB21_356;
	and.b64 	%rd31, %rd30, 4503599627370495;
	setp.eq.b32 	%p239, %r449, 12;
	selp.b32 	%r54, 11, 8, %p239;
	selp.b32 	%r450, 31744, 32640, %p239;
	setp.ne.b32 	%p241, %r53, 2047;
	@%p241 bra 	$L__BB21_357;
	setp.eq.b64 	%p242, %rd31, 0;
	add.s32 	%r332, %r54, -2;
	mov.b32 	%r333, 1;
	shl.b32 	%r334, %r333, %r332;
	selp.b32 	%r335, 0, %r334, %p242;
	or.b32 	%r336, %r52, %r335;
	or.b32 	%r337, %r336, %r450;
	cvt.u16.u32 	%rs13, %r337;
	bra.uni 	$L__BB21_366;
$L__BB21_367:
	setp.ne.b32 	%p238, %r449, 10;
	@%p238 bra 	$L__BB21_369;
	shl.b64 	%rd317, %rd29, 2;
	add.s64 	%rd318, %rd58, %rd317;
	st.b32 	[%rd318], %r329;
	bra.uni 	$L__BB21_370;
$L__BB21_369:
	shl.b64 	%rd315, %rd29, 3;
	add.s64 	%rd316, %rd58, %rd315;
	st.b64 	[%rd316], %rd30;
	bra.uni 	$L__BB21_370;
$L__BB21_399:
	cvt.u16.u32 	%rs15, %r69;
	bra.uni 	$L__BB21_409;
$L__BB21_356:
	cvt.u16.u32 	%rs13, %r52;
	bra.uni 	$L__BB21_366;
$L__BB21_400:
	selp.b32 	%r290, -14, -126, %p198;
	add.s32 	%r73, %r70, -1023;
	or.b64 	%rd47, %rd45, 4503599627370496;
	setp.ge.s32 	%p202, %r73, %r290;
	@%p202 bra 	$L__BB21_406;
	and.b64 	%rd48, %rd46, 32768;
	selp.b32 	%r300, 28, -81, %p198;
	sub.s32 	%r74, %r300, %r73;
	setp.gt.s32 	%p210, %r74, 0;
	@%p210 bra 	$L__BB21_403;
	bra.uni 	$L__BB21_402;
$L__BB21_403:
	setp.gt.u32 	%p211, %r74, 63;
	mov.b64 	%rd441, 0;
	@%p211 bra 	$L__BB21_405;
	shr.u64 	%rd271, %rd47, %r74;
	mov.b64 	%rd272, -1;
	shl.b64 	%rd273, %rd272, %r74;
	not.b64 	%rd274, %rd273;
	and.b64 	%rd275, %rd47, %rd274;
	add.s32 	%r301, %r74, -1;
	mov.b64 	%rd276, 1;
	shl.b64 	%rd277, %rd276, %r301;
	setp.gt.u64 	%p212, %rd275, %rd277;
	setp.eq.b64 	%p213, %rd275, %rd277;
	and.b64 	%rd278, %rd271, 1;
	setp.ne.b64 	%p214, %rd278, 0;
	and.pred 	%p215, %p213, %p214;
	or.pred 	%p216, %p212, %p215;
	selp.b64 	%rd279, 1, 0, %p216;
	add.s64 	%rd441, %rd271, %rd279;
	bra.uni 	$L__BB21_405;
$L__BB21_357:
	selp.b32 	%r338, -14, -126, %p239;
	add.s32 	%r56, %r53, -1023;
	or.b64 	%rd33, %rd31, 4503599627370496;
	setp.ge.s32 	%p243, %r56, %r338;
	@%p243 bra 	$L__BB21_363;
	and.b64 	%rd34, %rd32, 32768;
	selp.b32 	%r348, 28, -81, %p239;
	sub.s32 	%r57, %r348, %r56;
	setp.gt.s32 	%p251, %r57, 0;
	@%p251 bra 	$L__BB21_360;
	bra.uni 	$L__BB21_359;
$L__BB21_360:
	setp.gt.u32 	%p252, %r57, 63;
	mov.b64 	%rd439, 0;
	@%p252 bra 	$L__BB21_362;
	shr.u64 	%rd333, %rd33, %r57;
	mov.b64 	%rd334, -1;
	shl.b64 	%rd335, %rd334, %r57;
	not.b64 	%rd336, %rd335;
	and.b64 	%rd337, %rd33, %rd336;
	add.s32 	%r349, %r57, -1;
	mov.b64 	%rd338, 1;
	shl.b64 	%rd339, %rd338, %r349;
	setp.gt.u64 	%p253, %rd337, %rd339;
	setp.eq.b64 	%p254, %rd337, %rd339;
	and.b64 	%rd340, %rd333, 1;
	setp.ne.b64 	%p255, %rd340, 0;
	and.pred 	%p256, %p254, %p255;
	or.pred 	%p257, %p253, %p256;
	selp.b64 	%rd341, 1, 0, %p257;
	add.s64 	%rd439, %rd333, %rd341;
	bra.uni 	$L__BB21_362;
$L__BB21_453:
	mov.b32 	%r455, 10;
$L__BB21_454:
	and.b32 	%r373, %r455, -2;
	setp.ne.b32 	%p279, %r373, 12;
	@%p279 bra 	$L__BB21_464;
	shl.b64 	%rd395, %rd29, 1;
	add.s64 	%rd396, %rd62, %rd395;
	ld.b16 	%rs8, [%rd396];
	setp.ne.b32 	%p293, %r455, 13;
	cvt.u32.u16 	%r83, %rs8;
	@%p293 bra 	$L__BB21_457;
	shl.b32 	%r456, %r83, 16;
	bra.uni 	$L__BB21_463;
$L__BB21_464:
	setp.gt.s32 	%p280, %r455, 4;
	@%p280 bra 	$L__BB21_472;
	bra.uni 	$L__BB21_465;
$L__BB21_472:
	setp.gt.s32 	%p281, %r455, 6;
	@%p281 bra 	$L__BB21_476;
	bra.uni 	$L__BB21_473;
$L__BB21_476:
	setp.eq.b32 	%p282, %r455, 7;
	@%p282 bra 	$L__BB21_484;
	setp.eq.b32 	%p283, %r455, 9;
	@%p283 bra 	$L__BB21_480;
	setp.ne.b32 	%p284, %r455, 10;
	@%p284 bra 	$L__BB21_485;
	shl.b64 	%rd389, %rd29, 2;
	add.s64 	%rd390, %rd62, %rd389;
	ld.b32 	%r374, [%rd390];
	cvt.f64.f32 	%rd444, %r374;
	bra.uni 	$L__BB21_487;
$L__BB21_457:
	cvt.s32.s16 	%r375, %rs8;
	and.b32 	%r456, %r375, -2147483648;
	bfe.u32 	%r84, %r83, 10, 5;
	setp.eq.b32 	%p294, %r84, 31;
	@%p294 bra 	$L__BB21_461;
	and.b32 	%r85, %r83, 1023;
	setp.ne.b32 	%p295, %r84, 0;
	@%p295 bra 	$L__BB21_462;
	setp.eq.b32 	%p296, %r85, 0;
	@%p296 bra 	$L__BB21_463;
	clz.b32 	%r378, %r85;
	xor.b32 	%r379, %r378, 31;
	sub.s32 	%r380, 9, %r379;
	shl.b32 	%r381, %r83, %r380;
	shl.b32 	%r382, %r379, 23;
	shl.b32 	%r383, %r381, 14;
	and.b32 	%r384, %r383, 8372224;
	add.s32 	%r385, %r382, %r456;
	add.s32 	%r386, %r385, %r384;
	add.s32 	%r456, %r386, 864026624;
	bra.uni 	$L__BB21_463;
$L__BB21_465:
	setp.gt.s32 	%p287, %r455, 2;
	@%p287 bra 	$L__BB21_469;
	setp.eq.b32 	%p290, %r455, 1;
	@%p290 bra 	$L__BB21_481;
	setp.eq.b32 	%p291, %r455, 2;
	@%p291 bra 	$L__BB21_468;
	bra.uni 	$L__BB21_485;
$L__BB21_468:
	add.s64 	%rd384, %rd62, %rd29;
	ld.s8 	%rd443, [%rd384];
	bra.uni 	$L__BB21_486;
$L__BB21_406:
	selp.b32 	%r72, 15, 127, %p198;
	sub.s32 	%r291, 53, %r71;
	shr.u64 	%rd258, %rd47, %r291;
	mov.b64 	%rd259, -1;
	shl.b64 	%rd260, %rd259, %r291;
	not.b64 	%rd261, %rd260;
	and.b64 	%rd262, %rd261, %rd44;
	sub.s32 	%r292, 52, %r71;
	mov.b64 	%rd263, 1;
	shl.b64 	%rd264, %rd263, %r292;
	setp.gt.u64 	%p203, %rd262, %rd264;
	setp.eq.b64 	%p204, %rd262, %rd264;
	and.b64 	%rd265, %rd258, 1;
	setp.ne.b64 	%p205, %rd265, 0;
	and.pred 	%p206, %p204, %p205;
	or.pred 	%p207, %p203, %p206;
	selp.b64 	%rd266, 1, 0, %p207;
	add.s64 	%rd49, %rd258, %rd266;
	shl.b64 	%rd50, %rd263, %r71;
	setp.eq.b64 	%p208, %rd49, %rd50;
	add.s32 	%r293, %r70, -1022;
	selp.b32 	%r75, %r293, %r73, %p208;
	setp.gt.s32 	%p209, %r75, %r72;
	@%p209 bra 	$L__BB21_408;
	selp.b32 	%r294, 1, 0, %p208;
	shr.u64 	%rd267, %rd49, %r294;
	add.s32 	%r295, %r75, %r72;
	add.s32 	%r296, %r71, -1;
	shl.b32 	%r297, %r295, %r296;
	shl.b64 	%rd268, %rd259, %r296;
	not.b64 	%rd269, %rd268;
	and.b64 	%rd270, %rd267, %rd269;
	cvt.u32.u64 	%r298, %rd270;
	or.b32 	%r453, %r297, %r298;
$L__BB21_408:
	or.b32 	%r299, %r453, %r69;
	cvt.u16.u32 	%rs15, %r299;
	bra.uni 	$L__BB21_409;
$L__BB21_363:
	selp.b32 	%r55, 15, 127, %p239;
	sub.s32 	%r339, 53, %r54;
	shr.u64 	%rd320, %rd33, %r339;
	mov.b64 	%rd321, -1;
	shl.b64 	%rd322, %rd321, %r339;
	not.b64 	%rd323, %rd322;
	and.b64 	%rd324, %rd323, %rd30;
	sub.s32 	%r340, 52, %r54;
	mov.b64 	%rd325, 1;
	shl.b64 	%rd326, %rd325, %r340;
	setp.gt.u64 	%p244, %rd324, %rd326;
	setp.eq.b64 	%p245, %rd324, %rd326;
	and.b64 	%rd327, %rd320, 1;
	setp.ne.b64 	%p246, %rd327, 0;
	and.pred 	%p247, %p245, %p246;
	or.pred 	%p248, %p244, %p247;
	selp.b64 	%rd328, 1, 0, %p248;
	add.s64 	%rd35, %rd320, %rd328;
	shl.b64 	%rd36, %rd325, %r54;
	setp.eq.b64 	%p249, %rd35, %rd36;
	add.s32 	%r341, %r53, -1022;
	selp.b32 	%r58, %r341, %r56, %p249;
	setp.gt.s32 	%p250, %r58, %r55;
	@%p250 bra 	$L__BB21_365;
	selp.b32 	%r342, 1, 0, %p249;
	shr.u64 	%rd329, %rd35, %r342;
	add.s32 	%r343, %r58, %r55;
	add.s32 	%r344, %r54, -1;
	shl.b32 	%r345, %r343, %r344;
	shl.b64 	%rd330, %rd321, %r344;
	not.b64 	%rd331, %rd330;
	and.b64 	%rd332, %rd329, %rd331;
	cvt.u32.u64 	%r346, %rd332;
	or.b32 	%r450, %r345, %r346;
$L__BB21_365:
	or.b32 	%r347, %r450, %r52;
	cvt.u16.u32 	%rs13, %r347;
	bra.uni 	$L__BB21_366;
$L__BB21_469:
	setp.eq.b32 	%p288, %r455, 3;
	@%p288 bra 	$L__BB21_482;
	setp.eq.b32 	%p289, %r455, 4;
	@%p289 bra 	$L__BB21_471;
	bra.uni 	$L__BB21_485;
$L__BB21_471:
	shl.b64 	%rd380, %rd29, 2;
	add.s64 	%rd381, %rd62, %rd380;
	ld.s32 	%rd443, [%rd381];
	bra.uni 	$L__BB21_486;
$L__BB21_473:
	setp.eq.b32 	%p285, %r455, 5;
	@%p285 bra 	$L__BB21_483;
	setp.eq.b32 	%p286, %r455, 6;
	@%p286 bra 	$L__BB21_475;
	bra.uni 	$L__BB21_485;
$L__BB21_475:
	shl.b64 	%rd377, %rd29, 1;
	add.s64 	%rd378, %rd62, %rd377;
	ld.b16 	%rd443, [%rd378];
	bra.uni 	$L__BB21_486;
$L__BB21_461:
	shl.b32 	%r376, %r83, 13;
	or.b32 	%r377, %r456, %r376;
	or.b32 	%r456, %r377, 2139095040;
	bra.uni 	$L__BB21_463;
$L__BB21_462:
	shl.b32 	%r387, %r84, 23;
	shl.b32 	%r388, %r85, 13;
	or.b32 	%r389, %r387, %r388;
	add.s32 	%r390, %r389, %r456;
	add.s32 	%r456, %r390, 939524096;
$L__BB21_463:
	cvt.f64.f32 	%rd444, %r456;
	bra.uni 	$L__BB21_487;
$L__BB21_402:
	neg.s32 	%r302, %r74;
	shl.b64 	%rd441, %rd47, %r302;
$L__BB21_405:
	or.b64 	%rd280, %rd441, %rd48;
	cvt.u16.u64 	%rs15, %rd280;
$L__BB21_409:
	shl.b64 	%rd281, %rd29, 1;
	add.s64 	%rd282, %rd58, %rd281;
	st.b16 	[%rd282], %rs15;
$L__BB21_413:
	@%p92 bra 	$L__BB21_555;
	neg.f32 	%r67, %r50;
	cvt.f64.f32 	%rd51, %r67;
	@%p196 bra 	$L__BB21_429;
	shr.u64 	%rd53, %rd51, 48;
	cvt.u32.u64 	%r303, %rd53;
	and.b32 	%r76, %r303, 32768;
	shr.u64 	%rd287, %rd51, 52;
	cvt.u32.u64 	%r304, %rd287;
	and.b32 	%r77, %r304, 2047;
	setp.eq.b32 	%p219, %r77, 0;
	@%p219 bra 	$L__BB21_418;
	and.b64 	%rd52, %rd51, 4503599627370495;
	setp.eq.b32 	%p218, %r452, 12;
	selp.b32 	%r78, 11, 8, %p218;
	selp.b32 	%r454, 31744, 32640, %p218;
	setp.ne.b32 	%p220, %r77, 2047;
	@%p220 bra 	$L__BB21_419;
	setp.eq.b64 	%p221, %rd52, 0;
	add.s32 	%r305, %r78, -2;
	mov.b32 	%r306, 1;
	shl.b32 	%r307, %r306, %r305;
	selp.b32 	%r308, 0, %r307, %p221;
	or.b32 	%r309, %r76, %r308;
	or.b32 	%r310, %r309, %r454;
	cvt.u16.u32 	%rs16, %r310;
	bra.uni 	$L__BB21_428;
$L__BB21_429:
	setp.ne.b32 	%p217, %r452, 10;
	@%p217 bra 	$L__BB21_431;
	shl.b64 	%rd285, %rd29, 2;
	add.s64 	%rd286, %rd58, %rd285;
	st.b32 	[%rd286+4], %r67;
	bra.uni 	$L__BB21_555;
$L__BB21_431:
	shl.b64 	%rd283, %rd29, 3;
	add.s64 	%rd284, %rd58, %rd283;
	st.b64 	[%rd284+8], %rd51;
	bra.uni 	$L__BB21_555;
$L__BB21_418:
	cvt.u16.u32 	%rs16, %r76;
	bra.uni 	$L__BB21_428;
$L__BB21_419:
	selp.b32 	%r311, -14, -126, %p218;
	add.s32 	%r80, %r77, -1023;
	or.b64 	%rd54, %rd52, 4503599627370496;
	setp.ge.s32 	%p222, %r80, %r311;
	@%p222 bra 	$L__BB21_425;
	and.b64 	%rd55, %rd53, 32768;
	selp.b32 	%r321, 28, -81, %p218;
	sub.s32 	%r81, %r321, %r80;
	setp.gt.s32 	%p230, %r81, 0;
	@%p230 bra 	$L__BB21_422;
	bra.uni 	$L__BB21_421;
$L__BB21_422:
	setp.gt.u32 	%p231, %r81, 63;
	mov.b64 	%rd442, 0;
	@%p231 bra 	$L__BB21_424;
	shr.u64 	%rd301, %rd54, %r81;
	mov.b64 	%rd302, -1;
	shl.b64 	%rd303, %rd302, %r81;
	not.b64 	%rd304, %rd303;
	and.b64 	%rd305, %rd54, %rd304;
	add.s32 	%r322, %r81, -1;
	mov.b64 	%rd306, 1;
	shl.b64 	%rd307, %rd306, %r322;
	setp.gt.u64 	%p232, %rd305, %rd307;
	setp.eq.b64 	%p233, %rd305, %rd307;
	and.b64 	%rd308, %rd301, 1;
	setp.ne.b64 	%p234, %rd308, 0;
	and.pred 	%p235, %p233, %p234;
	or.pred 	%p236, %p232, %p235;
	selp.b64 	%rd309, 1, 0, %p236;
	add.s64 	%rd442, %rd301, %rd309;
	bra.uni 	$L__BB21_424;
$L__BB21_425:
	selp.b32 	%r79, 15, 127, %p218;
	sub.s32 	%r312, 53, %r78;
	shr.u64 	%rd288, %rd54, %r312;
)QPTX";
        result += R"QPTX(
	mov.b64 	%rd289, -1;
	shl.b64 	%rd290, %rd289, %r312;
	not.b64 	%rd291, %rd290;
	and.b64 	%rd292, %rd291, %rd51;
	sub.s32 	%r313, 52, %r78;
	mov.b64 	%rd293, 1;
	shl.b64 	%rd294, %rd293, %r313;
	setp.gt.u64 	%p223, %rd292, %rd294;
	setp.eq.b64 	%p224, %rd292, %rd294;
	and.b64 	%rd295, %rd288, 1;
	setp.ne.b64 	%p225, %rd295, 0;
	and.pred 	%p226, %p224, %p225;
	or.pred 	%p227, %p223, %p226;
	selp.b64 	%rd296, 1, 0, %p227;
	add.s64 	%rd56, %rd288, %rd296;
	shl.b64 	%rd57, %rd293, %r78;
	setp.eq.b64 	%p228, %rd56, %rd57;
	add.s32 	%r314, %r77, -1022;
	selp.b32 	%r82, %r314, %r80, %p228;
	setp.gt.s32 	%p229, %r82, %r79;
	@%p229 bra 	$L__BB21_427;
	selp.b32 	%r315, 1, 0, %p228;
	shr.u64 	%rd297, %rd56, %r315;
	add.s32 	%r316, %r82, %r79;
	add.s32 	%r317, %r78, -1;
	shl.b32 	%r318, %r316, %r317;
	shl.b64 	%rd298, %rd289, %r317;
	not.b64 	%rd299, %rd298;
	and.b64 	%rd300, %rd297, %rd299;
	cvt.u32.u64 	%r319, %rd300;
	or.b32 	%r454, %r318, %r319;
$L__BB21_427:
	or.b32 	%r320, %r454, %r76;
	cvt.u16.u32 	%rs16, %r320;
	bra.uni 	$L__BB21_428;
$L__BB21_359:
	neg.s32 	%r350, %r57;
	shl.b64 	%rd439, %rd33, %r350;
$L__BB21_362:
	or.b64 	%rd342, %rd439, %rd34;
	cvt.u16.u64 	%rs13, %rd342;
$L__BB21_366:
	shl.b64 	%rd343, %rd29, 1;
	add.s64 	%rd344, %rd58, %rd343;
	st.b16 	[%rd344], %rs13;
$L__BB21_370:
	@%p92 bra 	$L__BB21_555;
	cvt.f64.f32 	%rd37, %r328;
	@%p237 bra 	$L__BB21_386;
	shr.u64 	%rd39, %rd37, 48;
	cvt.u32.u64 	%r351, %rd39;
	and.b32 	%r59, %r351, 32768;
	shr.u64 	%rd349, %rd37, 52;
	cvt.u32.u64 	%r352, %rd349;
	and.b32 	%r60, %r352, 2047;
	setp.eq.b32 	%p260, %r60, 0;
	@%p260 bra 	$L__BB21_375;
	and.b64 	%rd38, %rd37, 4503599627370495;
	setp.eq.b32 	%p259, %r449, 12;
	selp.b32 	%r61, 11, 8, %p259;
	selp.b32 	%r451, 31744, 32640, %p259;
	setp.ne.b32 	%p261, %r60, 2047;
	@%p261 bra 	$L__BB21_376;
	setp.eq.b64 	%p262, %rd38, 0;
	add.s32 	%r353, %r61, -2;
	mov.b32 	%r354, 1;
	shl.b32 	%r355, %r354, %r353;
	selp.b32 	%r356, 0, %r355, %p262;
	or.b32 	%r357, %r59, %r356;
	or.b32 	%r358, %r357, %r451;
	cvt.u16.u32 	%rs14, %r358;
	bra.uni 	$L__BB21_385;
$L__BB21_386:
	setp.ne.b32 	%p258, %r449, 10;
	@%p258 bra 	$L__BB21_388;
	shl.b64 	%rd347, %rd29, 2;
	add.s64 	%rd348, %rd58, %rd347;
	st.b32 	[%rd348+4], %r328;
	bra.uni 	$L__BB21_555;
$L__BB21_388:
	shl.b64 	%rd345, %rd29, 3;
	add.s64 	%rd346, %rd58, %rd345;
	st.b64 	[%rd346+8], %rd37;
	bra.uni 	$L__BB21_555;
$L__BB21_375:
	cvt.u16.u32 	%rs14, %r59;
	bra.uni 	$L__BB21_385;
$L__BB21_376:
	selp.b32 	%r359, -14, -126, %p259;
	add.s32 	%r63, %r60, -1023;
	or.b64 	%rd40, %rd38, 4503599627370496;
	setp.ge.s32 	%p263, %r63, %r359;
	@%p263 bra 	$L__BB21_382;
	and.b64 	%rd41, %rd39, 32768;
	selp.b32 	%r369, 28, -81, %p259;
	sub.s32 	%r64, %r369, %r63;
	setp.gt.s32 	%p271, %r64, 0;
	@%p271 bra 	$L__BB21_379;
	bra.uni 	$L__BB21_378;
$L__BB21_379:
	setp.gt.u32 	%p272, %r64, 63;
	mov.b64 	%rd440, 0;
	@%p272 bra 	$L__BB21_381;
	shr.u64 	%rd363, %rd40, %r64;
	mov.b64 	%rd364, -1;
	shl.b64 	%rd365, %rd364, %r64;
	not.b64 	%rd366, %rd365;
	and.b64 	%rd367, %rd40, %rd366;
	add.s32 	%r370, %r64, -1;
	mov.b64 	%rd368, 1;
	shl.b64 	%rd369, %rd368, %r370;
	setp.gt.u64 	%p273, %rd367, %rd369;
	setp.eq.b64 	%p274, %rd367, %rd369;
	and.b64 	%rd370, %rd363, 1;
	setp.ne.b64 	%p275, %rd370, 0;
	and.pred 	%p276, %p274, %p275;
	or.pred 	%p277, %p273, %p276;
	selp.b64 	%rd371, 1, 0, %p277;
	add.s64 	%rd440, %rd363, %rd371;
	bra.uni 	$L__BB21_381;
$L__BB21_382:
	selp.b32 	%r62, 15, 127, %p259;
	sub.s32 	%r360, 53, %r61;
	shr.u64 	%rd350, %rd40, %r360;
	mov.b64 	%rd351, -1;
	shl.b64 	%rd352, %rd351, %r360;
	not.b64 	%rd353, %rd352;
	and.b64 	%rd354, %rd353, %rd37;
	sub.s32 	%r361, 52, %r61;
	mov.b64 	%rd355, 1;
	shl.b64 	%rd356, %rd355, %r361;
	setp.gt.u64 	%p264, %rd354, %rd356;
	setp.eq.b64 	%p265, %rd354, %rd356;
	and.b64 	%rd357, %rd350, 1;
	setp.ne.b64 	%p266, %rd357, 0;
	and.pred 	%p267, %p265, %p266;
	or.pred 	%p268, %p264, %p267;
	selp.b64 	%rd358, 1, 0, %p268;
	add.s64 	%rd42, %rd350, %rd358;
	shl.b64 	%rd43, %rd355, %r61;
	setp.eq.b64 	%p269, %rd42, %rd43;
	add.s32 	%r362, %r60, -1022;
	selp.b32 	%r65, %r362, %r63, %p269;
	setp.gt.s32 	%p270, %r65, %r62;
	@%p270 bra 	$L__BB21_384;
	selp.b32 	%r363, 1, 0, %p269;
	shr.u64 	%rd359, %rd42, %r363;
	add.s32 	%r364, %r65, %r62;
	add.s32 	%r365, %r61, -1;
	shl.b32 	%r366, %r364, %r365;
	shl.b64 	%rd360, %rd351, %r365;
	not.b64 	%rd361, %rd360;
	and.b64 	%rd362, %rd359, %rd361;
	cvt.u32.u64 	%r367, %rd362;
	or.b32 	%r451, %r366, %r367;
$L__BB21_384:
	or.b32 	%r368, %r451, %r59;
	cvt.u16.u32 	%rs14, %r368;
	bra.uni 	$L__BB21_385;
$L__BB21_481:
	shl.b64 	%rd385, %rd29, 3;
	add.s64 	%rd386, %rd62, %rd385;
	ld.b64 	%rd443, [%rd386];
	bra.uni 	$L__BB21_486;
$L__BB21_482:
	shl.b64 	%rd382, %rd29, 1;
	add.s64 	%rd383, %rd62, %rd382;
	ld.s16 	%rd443, [%rd383];
	bra.uni 	$L__BB21_486;
$L__BB21_484:
	shl.b64 	%rd375, %rd29, 2;
	add.s64 	%rd376, %rd62, %rd375;
	ld.b32 	%rd443, [%rd376];
	bra.uni 	$L__BB21_486;
$L__BB21_483:
	add.s64 	%rd379, %rd62, %rd29;
	ld.b8 	%rd443, [%rd379];
	bra.uni 	$L__BB21_486;
$L__BB21_480:
	shl.b64 	%rd387, %rd29, 3;
	add.s64 	%rd388, %rd62, %rd387;
	ld.b64 	%rd444, [%rd388];
	bra.uni 	$L__BB21_487;
$L__BB21_485:
	shl.b64 	%rd391, %rd29, 3;
	add.s64 	%rd392, %rd62, %rd391;
	ld.b64 	%rd443, [%rd392];
$L__BB21_486:
	setp.lt.s32 	%p292, %r455, 5;
	cvt.rn.f64.s64 	%rd393, %rd443;
	cvt.rn.f64.u64 	%rd394, %rd443;
	selp.f64 	%rd444, %rd393, %rd394, %p292;
$L__BB21_487:
	@%p328 bra 	$L__BB21_491;
	mov.b32 	%r457, 12;
	@%p331 bra 	$L__BB21_495;
	mov.b32 	%r457, %r92;
	@%p332 bra 	$L__BB21_490;
	bra.uni 	$L__BB21_495;
$L__BB21_490:
	mov.b32 	%r457, 13;
	bra.uni 	$L__BB21_495;
$L__BB21_491:
	@%p329 bra 	$L__BB21_494;
	mov.b32 	%r457, %r92;
	@%p330 bra 	$L__BB21_495;
	mov.b32 	%r457, 9;
	bra.uni 	$L__BB21_495;
$L__BB21_494:
	mov.b32 	%r457, 10;
$L__BB21_495:
	and.b32 	%r391, %r457, -2;
	setp.ne.b32 	%p297, %r391, 12;
	@%p297 bra 	$L__BB21_505;
	shl.b64 	%rd417, %rd29, 1;
	add.s64 	%rd418, %rd60, %rd417;
	ld.b16 	%rs9, [%rd418];
	setp.ne.b32 	%p311, %r457, 13;
	cvt.u32.u16 	%r87, %rs9;
	@%p311 bra 	$L__BB21_498;
	shl.b32 	%r458, %r87, 16;
	bra.uni 	$L__BB21_504;
$L__BB21_505:
	setp.gt.s32 	%p298, %r457, 4;
	@%p298 bra 	$L__BB21_513;
	bra.uni 	$L__BB21_506;
$L__BB21_513:
	setp.gt.s32 	%p299, %r457, 6;
	@%p299 bra 	$L__BB21_517;
	bra.uni 	$L__BB21_514;
$L__BB21_517:
	setp.eq.b32 	%p300, %r457, 7;
	@%p300 bra 	$L__BB21_525;
	setp.eq.b32 	%p301, %r457, 9;
	@%p301 bra 	$L__BB21_521;
	setp.ne.b32 	%p302, %r457, 10;
	@%p302 bra 	$L__BB21_526;
	shl.b64 	%rd411, %rd29, 2;
	add.s64 	%rd412, %rd60, %rd411;
	ld.b32 	%r392, [%rd412];
	cvt.f64.f32 	%rd446, %r392;
	bra.uni 	$L__BB21_528;
$L__BB21_498:
	cvt.s32.s16 	%r393, %rs9;
	and.b32 	%r458, %r393, -2147483648;
	bfe.u32 	%r88, %r87, 10, 5;
	setp.eq.b32 	%p312, %r88, 31;
	@%p312 bra 	$L__BB21_502;
	and.b32 	%r89, %r87, 1023;
	setp.ne.b32 	%p313, %r88, 0;
	@%p313 bra 	$L__BB21_503;
	setp.eq.b32 	%p314, %r89, 0;
	@%p314 bra 	$L__BB21_504;
	clz.b32 	%r396, %r89;
	xor.b32 	%r397, %r396, 31;
	sub.s32 	%r398, 9, %r397;
	shl.b32 	%r399, %r87, %r398;
	shl.b32 	%r400, %r397, 23;
	shl.b32 	%r401, %r399, 14;
	and.b32 	%r402, %r401, 8372224;
	add.s32 	%r403, %r400, %r458;
	add.s32 	%r404, %r403, %r402;
	add.s32 	%r458, %r404, 864026624;
	bra.uni 	$L__BB21_504;
$L__BB21_506:
	setp.gt.s32 	%p305, %r457, 2;
	@%p305 bra 	$L__BB21_510;
	setp.eq.b32 	%p308, %r457, 1;
	@%p308 bra 	$L__BB21_522;
	setp.eq.b32 	%p309, %r457, 2;
	@%p309 bra 	$L__BB21_509;
	bra.uni 	$L__BB21_526;
$L__BB21_509:
	add.s64 	%rd406, %rd60, %rd29;
	ld.s8 	%rd445, [%rd406];
	bra.uni 	$L__BB21_527;
$L__BB21_510:
	setp.eq.b32 	%p306, %r457, 3;
	@%p306 bra 	$L__BB21_523;
	setp.eq.b32 	%p307, %r457, 4;
	@%p307 bra 	$L__BB21_512;
	bra.uni 	$L__BB21_526;
$L__BB21_512:
	shl.b64 	%rd402, %rd29, 2;
	add.s64 	%rd403, %rd60, %rd402;
	ld.s32 	%rd445, [%rd403];
	bra.uni 	$L__BB21_527;
$L__BB21_514:
	setp.eq.b32 	%p303, %r457, 5;
	@%p303 bra 	$L__BB21_524;
	setp.eq.b32 	%p304, %r457, 6;
	@%p304 bra 	$L__BB21_516;
	bra.uni 	$L__BB21_526;
$L__BB21_516:
	shl.b64 	%rd399, %rd29, 1;
	add.s64 	%rd400, %rd60, %rd399;
	ld.b16 	%rd445, [%rd400];
	bra.uni 	$L__BB21_527;
$L__BB21_502:
	shl.b32 	%r394, %r87, 13;
	or.b32 	%r395, %r458, %r394;
	or.b32 	%r458, %r395, 2139095040;
	bra.uni 	$L__BB21_504;
$L__BB21_503:
	shl.b32 	%r405, %r88, 23;
	shl.b32 	%r406, %r89, 13;
	or.b32 	%r407, %r405, %r406;
	add.s32 	%r408, %r407, %r458;
	add.s32 	%r458, %r408, 939524096;
$L__BB21_504:
	cvt.f64.f32 	%rd446, %r458;
	bra.uni 	$L__BB21_528;
$L__BB21_522:
	shl.b64 	%rd407, %rd29, 3;
	add.s64 	%rd408, %rd60, %rd407;
	ld.b64 	%rd445, [%rd408];
	bra.uni 	$L__BB21_527;
$L__BB21_523:
	shl.b64 	%rd404, %rd29, 1;
	add.s64 	%rd405, %rd60, %rd404;
	ld.s16 	%rd445, [%rd405];
	bra.uni 	$L__BB21_527;
$L__BB21_525:
	shl.b64 	%rd397, %rd29, 2;
	add.s64 	%rd398, %rd60, %rd397;
	ld.b32 	%rd445, [%rd398];
	bra.uni 	$L__BB21_527;
$L__BB21_524:
	add.s64 	%rd401, %rd60, %rd29;
	ld.b8 	%rd445, [%rd401];
	bra.uni 	$L__BB21_527;
$L__BB21_521:
	shl.b64 	%rd409, %rd29, 3;
	add.s64 	%rd410, %rd60, %rd409;
	ld.b64 	%rd446, [%rd410];
	bra.uni 	$L__BB21_528;
$L__BB21_526:
	shl.b64 	%rd413, %rd29, 3;
	add.s64 	%rd414, %rd60, %rd413;
	ld.b64 	%rd445, [%rd414];
$L__BB21_527:
	setp.lt.s32 	%p310, %r457, 5;
	cvt.rn.f64.s64 	%rd415, %rd445;
	cvt.rn.f64.u64 	%rd416, %rd445;
	selp.f64 	%rd446, %rd415, %rd416, %p310;
$L__BB21_528:
	setp.eq.b32 	%p315, %r95, 6;
	mov.b32 	%r91, 0f00000000;
	@%p315 bra 	$L__BB21_530;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .b32 	param2;
	.param .align 4 .b8 	retval0[8];
	st.param.b32 	[param2], %r92;
	st.param.b64 	[param1], %rd66;
	st.param.b64 	[param0], %rd61;
	call.uni (retval0), _Z6q_readIfE5QPairIT_EPKvyi, (param0, param1, param2);
	ld.param.b32 	%r91, [retval0];
	}
$L__BB21_530:
	cvt.rn.f32.f64 	%r86, %rd444;
	cvt.rn.f32.f64 	%r90, %rd446;
	setp.ne.b32 	%p316, %r93, 2;
	@%p316 bra 	$L__BB21_532;
	setp.eq.b32 	%p322, %r95, 5;
	setp.eq.b32 	%p323, %r94, 1;
	neg.f32 	%r412, %r86;
	selp.f32 	%r413, %r412, %r86, %p323;
	selp.f32 	%r459, %r86, %r413, %p322;
	selp.f32 	%r460, %r412, %r86, %p322;
	bra.uni 	$L__BB21_536;
$L__BB21_532:
	setp.ne.b32 	%p317, %r95, 5;
	setp.ne.b32 	%p318, %r93, 3;
	or.pred 	%p319, %p318, %p317;
	@%p319 bra 	$L__BB21_534;
	mul.rn.f32 	%r459, %r91, %r86;
	mul.rn.f32 	%r460, %r86, %r90;
	bra.uni 	$L__BB21_536;
$L__BB21_534:
	setp.ne.b32 	%p320, %r93, 4;
	or.pred 	%p321, %p320, %p317;
	mov.b32 	%r459, %r86;
	mov.b32 	%r460, %r86;
	@%p321 bra 	$L__BB21_536;
	div.rn.f32 	%r459, %r86, %r91;
	mul.rn.f32 	%r409, %r91, %r91;
	neg.f32 	%r410, %r90;
	mul.rn.f32 	%r411, %r86, %r410;
	div.rn.f32 	%r460, %r411, %r409;
$L__BB21_536:
	setp.ne.b32 	%p324, %r95, 6;
	@%p324 bra 	$L__BB21_544;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .b32 	param2;
	.param .align 4 .b8 	retval0[8];
	st.param.b32 	[param2], %r92;
	st.param.b64 	[param0], %rd68;
	st.param.b64 	[param1], 0;
	call.uni (retval0), _Z6q_readIfE5QPairIT_EPKvyi, (param0, param1, param2);
	ld.param.b32 	%r423, [retval0];
	}
	setp.eq.b32 	%p326, %r93, 4;
	@%p326 bra 	$L__BB21_540;
	setp.ne.b32 	%p327, %r93, 3;
	@%p327 bra 	$L__BB21_543;
	mul.rn.f32 	%r459, %r423, %r86;
	bra.uni 	$L__BB21_543;
$L__BB21_544:
	ld.param.b64 	%rd59, [_Z5q_runIfEvPvS0_PKvS2_S2_PKyS4_yyyiiiiPj_param_1];
	setp.ne.b64 	%p325, %rd58, %rd59;
	@%p325 bra 	$L__BB21_554;
	bra.uni 	$L__BB21_545;
$L__BB21_554:
	st.local.b32 	[%rd6], %r459;
	st.local.b32 	[%rd6+4], 0;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .align 4 .b8 	param2[8];
	.param .b32 	param3;
	st.param.b32 	[param3], %r92;
	cvta.to.local.u64 	%rd419, %rd73;
	ld.local.b32 	%r414, [%rd419+4];
	st.param.b32 	[param2+4], %r414;
	ld.local.b32 	%r415, [%rd419];
	st.param.b32 	[param2], %r415;
	st.param.b64 	[param1], %rd66;
	st.param.b64 	[param0], %rd58;
	call.uni _Z7q_storeIfEvPvy5QPairIT_Ei, (param0, param1, param2, param3);
	}
	st.local.b32 	[%rd7], %r460;
	st.local.b32 	[%rd7+4], 0;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .align 4 .b8 	param2[8];
	.param .b32 	param3;
	st.param.b32 	[param3], %r92;
	cvta.to.local.u64 	%rd420, %rd74;
	ld.local.b32 	%r416, [%rd420+4];
	st.param.b32 	[param2+4], %r416;
	ld.local.b32 	%r417, [%rd420];
	st.param.b32 	[param2], %r417;
	st.param.b64 	[param1], %rd66;
	st.param.b64 	[param0], %rd59;
	call.uni _Z7q_storeIfEvPvy5QPairIT_Ei, (param0, param1, param2, param3);
	}
	bra.uni 	$L__BB21_555;
$L__BB21_545:
	@%p328 bra 	$L__BB21_549;
	mov.b32 	%r461, 12;
	@%p331 bra 	$L__BB21_553;
	mov.b32 	%r461, %r92;
	@%p332 bra 	$L__BB21_548;
	bra.uni 	$L__BB21_553;
$L__BB21_548:
	mov.b32 	%r461, 13;
	bra.uni 	$L__BB21_553;
$L__BB21_540:
	@%p181 bra 	$L__BB21_542;
	mul.rn.f32 	%r424, %r90, %r90;
	neg.f32 	%r425, %r423;
	mul.rn.f32 	%r426, %r86, %r425;
	div.rn.f32 	%r459, %r426, %r424;
	bra.uni 	$L__BB21_543;
$L__BB21_549:
	@%p329 bra 	$L__BB21_552;
	mov.b32 	%r461, %r92;
	@%p330 bra 	$L__BB21_553;
	mov.b32 	%r461, 9;
	bra.uni 	$L__BB21_553;
$L__BB21_542:
	div.rn.f32 	%r459, %r86, %r423;
$L__BB21_543:
	st.local.b32 	[%rd4], %r459;
	st.local.b32 	[%rd4+4], 0;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .align 4 .b8 	param2[8];
	.param .b32 	param3;
	st.param.b32 	[param3], %r92;
	cvta.to.local.u64 	%rd422, %rd71;
	ld.local.b32 	%r427, [%rd422+4];
	st.param.b32 	[param2+4], %r427;
	ld.local.b32 	%r428, [%rd422];
	st.param.b32 	[param2], %r428;
	st.param.b64 	[param1], %rd66;
	st.param.b64 	[param0], %rd58;
	call.uni _Z7q_storeIfEvPvy5QPairIT_Ei, (param0, param1, param2, param3);
	}
	bra.uni 	$L__BB21_555;
$L__BB21_552:
	mov.b32 	%r461, 10;
$L__BB21_553:
	{
	.param .b32 	param0;
	.param .b32 	param1;
	.param .b32 	retval0;
	st.param.b32 	[param1], %r461;
	st.param.b32 	[param0], %r459;
	call.uni (retval0), _Z7q_roundIfET_S0_i, (param0, param1);
	ld.param.b32 	%r418, [retval0];
	}
	{
	.param .b32 	param0;
	.param .b32 	param1;
	.param .b32 	retval0;
	st.param.b32 	[param1], %r461;
	st.param.b32 	[param0], %r460;
	call.uni (retval0), _Z7q_roundIfET_S0_i, (param0, param1);
	ld.param.b32 	%r419, [retval0];
	}
	add.rn.f32 	%r420, %r418, %r419;
	st.local.b32 	[%rd5], %r420;
	st.local.b32 	[%rd5+4], 0;
	{
	.param .b64 	param0;
	.param .b64 	param1;
	.param .align 4 .b8 	param2[8];
	.param .b32 	param3;
	st.param.b32 	[param3], %r92;
	cvta.to.local.u64 	%rd421, %rd72;
	ld.local.b32 	%r421, [%rd421+4];
	st.param.b32 	[param2+4], %r421;
	ld.local.b32 	%r422, [%rd421];
	st.param.b32 	[param2], %r422;
	st.param.b64 	[param1], %rd66;
	st.param.b64 	[param0], %rd58;
	call.uni _Z7q_storeIfEvPvy5QPairIT_Ei, (param0, param1, param2, param3);
	}
	bra.uni 	$L__BB21_555;
$L__BB21_421:
	neg.s32 	%r323, %r81;
	shl.b64 	%rd442, %rd54, %r323;
$L__BB21_424:
	or.b64 	%rd310, %rd442, %rd55;
	cvt.u16.u64 	%rs16, %rd310;
$L__BB21_428:
	shl.b64 	%rd311, %rd29, 1;
	add.s64 	%rd312, %rd58, %rd311;
	st.b16 	[%rd312+2], %rs16;
	bra.uni 	$L__BB21_555;
$L__BB21_378:
	neg.s32 	%r371, %r64;
	shl.b64 	%rd440, %rd40, %r371;
$L__BB21_381:
	or.b64 	%rd372, %rd440, %rd41;
	cvt.u16.u64 	%rs14, %rd372;
$L__BB21_385:
	shl.b64 	%rd373, %rd29, 1;
	add.s64 	%rd374, %rd58, %rd373;
	st.b16 	[%rd374+2], %rs14;
$L__BB21_555:
	ret;
}
.weak .func  (.param .b64 func_retval0) _Z7q_roundIdET_S0_i(
	.param .b64 _Z7q_roundIdET_S0_i_param_0,
	.param .b32 _Z7q_roundIdET_S0_i_param_1
)
{
	.reg .pred 	%p<25>;
	.reg .b16 	%rs<2>;
	.reg .b32 	%r<53>;
	.reg .b64 	%rd<33>;
	ld.param.b32 	%r12, [_Z7q_roundIdET_S0_i_param_1];
	ld.param.b64 	%rd32, [_Z7q_roundIdET_S0_i_param_0];
	and.b32 	%r13, %r12, -2;
	setp.ne.b32 	%p1, %r13, 12;
	@%p1 bra 	$L__BB22_24;
	shr.u64 	%rd2, %rd32, 48;
	cvt.u32.u64 	%r14, %rd2;
	and.b32 	%r1, %r14, 32768;
	shr.u64 	%rd7, %rd32, 52;
	cvt.u32.u64 	%r15, %rd7;
	and.b32 	%r2, %r15, 2047;
	setp.eq.b32 	%p3, %r2, 0;
	@%p3 bra 	$L__BB22_4;
	and.b64 	%rd1, %rd32, 4503599627370495;
	setp.eq.b32 	%p2, %r12, 12;
	selp.b32 	%r3, 11, 8, %p2;
	selp.b32 	%r5, 31744, 32640, %p2;
	setp.ne.b32 	%p4, %r2, 2047;
	@%p4 bra 	$L__BB22_5;
	setp.eq.b64 	%p5, %rd1, 0;
	add.s32 	%r16, %r3, -2;
	mov.b32 	%r17, 1;
	shl.b32 	%r18, %r17, %r16;
	selp.b32 	%r19, 0, %r18, %p5;
	or.b32 	%r20, %r5, %r19;
	or.b32 	%r21, %r20, %r1;
	cvt.u16.u32 	%rs1, %r21;
	bra.uni 	$L__BB22_15;
$L__BB22_4:
	cvt.u16.u32 	%rs1, %r1;
	bra.uni 	$L__BB22_15;
$L__BB22_5:
	selp.b32 	%r22, -14, -126, %p2;
	add.s32 	%r6, %r2, -1023;
	or.b64 	%rd3, %rd1, 4503599627370496;
	setp.ge.s32 	%p6, %r6, %r22;
	@%p6 bra 	$L__BB22_11;
	and.b64 	%rd4, %rd2, 32768;
	selp.b32 	%r32, 28, -81, %p2;
	sub.s32 	%r7, %r32, %r6;
	setp.gt.s32 	%p14, %r7, 0;
	@%p14 bra 	$L__BB22_8;
	bra.uni 	$L__BB22_7;
$L__BB22_8:
	setp.gt.u32 	%p15, %r7, 63;
	mov.b64 	%rd31, 0;
	@%p15 bra 	$L__BB22_10;
	shr.u64 	%rd21, %rd3, %r7;
	mov.b64 	%rd22, -1;
	shl.b64 	%rd23, %rd22, %r7;
	not.b64 	%rd24, %rd23;
	and.b64 	%rd25, %rd3, %rd24;
	add.s32 	%r33, %r7, -1;
	mov.b64 	%rd26, 1;
	shl.b64 	%rd27, %rd26, %r33;
	setp.gt.u64 	%p16, %rd25, %rd27;
	setp.eq.b64 	%p17, %rd25, %rd27;
	and.b64 	%rd28, %rd21, 1;
	setp.ne.b64 	%p18, %rd28, 0;
	and.pred 	%p19, %p17, %p18;
	or.pred 	%p20, %p16, %p19;
	selp.b64 	%rd29, 1, 0, %p20;
	add.s64 	%rd31, %rd21, %rd29;
	bra.uni 	$L__BB22_10;
$L__BB22_11:
	selp.b32 	%r4, 15, 127, %p2;
	sub.s32 	%r23, 53, %r3;
	shr.u64 	%rd8, %rd3, %r23;
	mov.b64 	%rd9, -1;
	shl.b64 	%rd10, %rd9, %r23;
	not.b64 	%rd11, %rd10;
	and.b64 	%rd12, %rd11, %rd32;
	sub.s32 	%r24, 52, %r3;
	mov.b64 	%rd13, 1;
	shl.b64 	%rd14, %rd13, %r24;
	setp.gt.u64 	%p7, %rd12, %rd14;
	setp.eq.b64 	%p8, %rd12, %rd14;
	and.b64 	%rd15, %rd8, 1;
	setp.ne.b64 	%p9, %rd15, 0;
	and.pred 	%p10, %p8, %p9;
	or.pred 	%p11, %p7, %p10;
	selp.b64 	%rd16, 1, 0, %p11;
	add.s64 	%rd5, %rd8, %rd16;
	shl.b64 	%rd6, %rd13, %r3;
	setp.eq.b64 	%p12, %rd5, %rd6;
	add.s32 	%r25, %r2, -1022;
	selp.b32 	%r8, %r25, %r6, %p12;
	setp.le.s32 	%p13, %r8, %r4;
	@%p13 bra 	$L__BB22_13;
	or.b32 	%r51, %r1, %r5;
	bra.uni 	$L__BB22_14;
$L__BB22_13:
	selp.b32 	%r26, 1, 0, %p12;
	shr.u64 	%rd17, %rd5, %r26;
	add.s32 	%r27, %r8, %r4;
	add.s32 	%r28, %r3, -1;
	shl.b32 	%r29, %r27, %r28;
	shl.b64 	%rd18, %rd9, %r28;
	not.b64 	%rd19, %rd18;
	and.b64 	%rd20, %rd17, %rd19;
	cvt.u32.u64 	%r30, %rd20;
	or.b32 	%r31, %r29, %r30;
	or.b32 	%r51, %r31, %r1;
$L__BB22_14:
	cvt.u16.u32 	%rs1, %r51;
	bra.uni 	$L__BB22_15;
$L__BB22_7:
	neg.s32 	%r34, %r7;
	shl.b64 	%rd31, %rd3, %r34;
$L__BB22_10:
	or.b64 	%rd30, %rd31, %rd4;
	cvt.u16.u64 	%rs1, %rd30;
$L__BB22_15:
	setp.ne.b32 	%p21, %r12, 13;
	cvt.u32.u16 	%r9, %rs1;
	@%p21 bra 	$L__BB22_17;
	shl.b32 	%r52, %r9, 16;
	bra.uni 	$L__BB22_23;
$L__BB22_17:
	cvt.s32.s16 	%r35, %rs1;
	and.b32 	%r52, %r35, -2147483648;
	bfe.u32 	%r10, %r9, 10, 5;
	setp.eq.b32 	%p22, %r10, 31;
	@%p22 bra 	$L__BB22_21;
	and.b32 	%r11, %r9, 1023;
	setp.ne.b32 	%p23, %r10, 0;
	@%p23 bra 	$L__BB22_22;
	setp.eq.b32 	%p24, %r11, 0;
	@%p24 bra 	$L__BB22_23;
	clz.b32 	%r38, %r11;
	xor.b32 	%r39, %r38, 31;
	sub.s32 	%r40, 9, %r39;
	shl.b32 	%r41, %r9, %r40;
	shl.b32 	%r42, %r39, 23;
	shl.b32 	%r43, %r41, 14;
	and.b32 	%r44, %r43, 8372224;
	add.s32 	%r45, %r42, %r52;
	add.s32 	%r46, %r45, %r44;
	add.s32 	%r52, %r46, 864026624;
	bra.uni 	$L__BB22_23;
$L__BB22_21:
	shl.b32 	%r36, %r9, 13;
	or.b32 	%r37, %r52, %r36;
	or.b32 	%r52, %r37, 2139095040;
	bra.uni 	$L__BB22_23;
$L__BB22_22:
	shl.b32 	%r47, %r10, 23;
	shl.b32 	%r48, %r11, 13;
	or.b32 	%r49, %r47, %r48;
	add.s32 	%r50, %r49, %r52;
	add.s32 	%r52, %r50, 939524096;
$L__BB22_23:
	cvt.f64.f32 	%rd32, %r52;
$L__BB22_24:
	st.param.b64 	[func_retval0], %rd32;
	ret;
}
.weak .func  (.param .align 8 .b8 func_retval0[16]) _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj(
	.param .align 8 .b8 _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_0[16],
	.param .align 8 .b8 _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_1[16],
	.param .b32 _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_2,
	.param .b32 _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_3,
	.param .b64 _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_4
)
{
	.local .align 8 .b8 	__local_depot23[32];
	.reg .b64 	%SP;
	.reg .b64 	%SPL;
	.reg .pred 	%p<679>;
	.reg .b16 	%rs<29>;
	.reg .b32 	%r<1417>;
	.reg .b64 	%rd<934>;
	mov.b64 	%SPL, __local_depot23;
	cvta.local.u64 	%SP, %SPL;
	ld.param.b32 	%r313, [_Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_3];
	ld.param.b32 	%r312, [_Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_2];
	setp.gt.s32 	%p2, %r312, 15;
	@%p2 bra 	$L__BB23_4;
	mov.b32 	%r1360, 12;
	setp.eq.b32 	%p5, %r312, 14;
	@%p5 bra 	$L__BB23_8;
	setp.eq.b32 	%p6, %r312, 15;
	mov.b32 	%r1360, %r312;
	@%p6 bra 	$L__BB23_3;
	bra.uni 	$L__BB23_8;
$L__BB23_3:
	mov.b32 	%r1360, 13;
	bra.uni 	$L__BB23_8;
$L__BB23_4:
	setp.eq.b32 	%p3, %r312, 16;
	@%p3 bra 	$L__BB23_7;
	setp.ne.b32 	%p4, %r312, 17;
	mov.b32 	%r1360, %r312;
	@%p4 bra 	$L__BB23_8;
	mov.b32 	%r1360, 9;
	bra.uni 	$L__BB23_8;
$L__BB23_7:
	mov.b32 	%r1360, 10;
$L__BB23_8:
	ld.param.b64 	%rd887, [_Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_4];
	mov.b64 	%rd1, _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_0;
	mov.b64 	%rd2, _Z8q_binaryIdE5QPairIT_ES2_S2_iiPj_param_1;
	mov.b64 	%rd932, 0d0000000000000000;
	setp.gt.s32 	%p7, %r313, 2;
	@%p7 bra 	$L__BB23_15;
	setp.eq.b32 	%p10, %r313, 1;
	@%p10 bra 	$L__BB23_22;
	setp.eq.b32 	%p11, %r313, 2;
	mov.b64 	%rd933, %rd932;
	@%p11 bra 	$L__BB23_11;
	bra.uni 	$L__BB23_690;
$L__BB23_11:
	ld.local.b64 	%rd781, [%rd1];
	ld.local.b64 	%rd782, [%rd2];
	sub.rn.f64 	%rd933, %rd781, %rd782;
	and.b32 	%r24, %r1360, -2;
	setp.ne.b32 	%p577, %r24, 12;
	@%p577 bra 	$L__BB23_90;
	shr.u64 	%rd16, %rd933, 48;
	cvt.u32.u64 	%r1207, %rd16;
	and.b32 	%r25, %r1207, 32768;
	shr.u64 	%rd783, %rd933, 52;
	cvt.u32.u64 	%r1208, %rd783;
	and.b32 	%r26, %r1208, 2047;
	setp.eq.b32 	%p579, %r26, 0;
	@%p579 bra 	$L__BB23_70;
	and.b64 	%rd15, %rd933, 4503599627370495;
	setp.eq.b32 	%p578, %r1360, 12;
	selp.b32 	%r27, 11, 8, %p578;
	selp.b32 	%r29, 31744, 32640, %p578;
	setp.ne.b32 	%p580, %r26, 2047;
	@%p580 bra 	$L__BB23_71;
	setp.eq.b64 	%p581, %rd15, 0;
	add.s32 	%r1209, %r27, -2;
	mov.b32 	%r1210, 1;
	shl.b32 	%r1211, %r1210, %r1209;
	selp.b32 	%r1212, 0, %r1211, %p581;
	or.b32 	%r1213, %r1212, %r29;
	or.b32 	%r1214, %r1213, %r25;
	cvt.u16.u32 	%rs3, %r1214;
	bra.uni 	$L__BB23_81;
$L__BB23_15:
	setp.eq.b32 	%p8, %r313, 3;
	@%p8 bra 	$L__BB23_114;
	setp.eq.b32 	%p9, %r313, 4;
	mov.b64 	%rd933, %rd932;
	@%p9 bra 	$L__BB23_17;
	bra.uni 	$L__BB23_690;
$L__BB23_17:
	add.s32 	%r314, %r312, -14;
	setp.lt.u32 	%p12, %r314, 4;
	and.b32 	%r1359, %r1360, -2;
	@%p12 bra 	$L__BB23_303;
	bra.uni 	$L__BB23_18;
$L__BB23_303:
	ld.local.b64 	%rd75, [%rd2];
	abs.f64 	%rd203, %rd75;
	ld.local.b64 	%rd76, [%rd2+8];
	abs.f64 	%rd204, %rd76;
	setp.ltu.f64 	%p37, %rd203, %rd204;
	setp.ne.b32 	%p677, %r1359, 12;
	@%p37 bra 	$L__BB23_472;
	bra.uni 	$L__BB23_304;
$L__BB23_472:
	div.rn.f64 	%rd928, %rd75, %rd76;
	@%p677 bra 	$L__BB23_496;
	shr.u64 	%rd122, %rd928, 48;
	cvt.u32.u64 	%r611, %rd122;
	and.b32 	%r213, %r611, 32768;
	shr.u64 	%rd373, %rd928, 52;
	cvt.u32.u64 	%r612, %rd373;
	and.b32 	%r214, %r612, 2047;
	setp.eq.b32 	%p200, %r214, 0;
	@%p200 bra 	$L__BB23_476;
	and.b64 	%rd121, %rd928, 4503599627370495;
	setp.eq.b32 	%p199, %r1360, 12;
	selp.b32 	%r215, 11, 8, %p199;
	selp.b32 	%r217, 31744, 32640, %p199;
	setp.ne.b32 	%p201, %r214, 2047;
	@%p201 bra 	$L__BB23_477;
	setp.eq.b64 	%p202, %rd121, 0;
	add.s32 	%r613, %r215, -2;
	mov.b32 	%r614, 1;
	shl.b32 	%r615, %r614, %r613;
	selp.b32 	%r616, 0, %r615, %p202;
	or.b32 	%r617, %r616, %r217;
	or.b32 	%r618, %r617, %r213;
	cvt.u16.u32 	%rs20, %r618;
	bra.uni 	$L__BB23_487;
$L__BB23_22:
	ld.local.b64 	%rd833, [%rd1];
	ld.local.b64 	%rd834, [%rd2];
	add.rn.f64 	%rd933, %rd833, %rd834;
	and.b32 	%r1, %r1360, -2;
	setp.ne.b32 	%p624, %r1, 12;
	@%p624 bra 	$L__BB23_46;
	shr.u64 	%rd4, %rd933, 48;
	cvt.u32.u64 	%r1281, %rd4;
	and.b32 	%r2, %r1281, 32768;
	shr.u64 	%rd835, %rd933, 52;
	cvt.u32.u64 	%r1282, %rd835;
	and.b32 	%r3, %r1282, 2047;
	setp.eq.b32 	%p626, %r3, 0;
	@%p626 bra 	$L__BB23_26;
	and.b64 	%rd3, %rd933, 4503599627370495;
	setp.eq.b32 	%p625, %r1360, 12;
	selp.b32 	%r4, 11, 8, %p625;
	selp.b32 	%r6, 31744, 32640, %p625;
	setp.ne.b32 	%p627, %r3, 2047;
	@%p627 bra 	$L__BB23_27;
	setp.eq.b64 	%p628, %rd3, 0;
	add.s32 	%r1283, %r4, -2;
	mov.b32 	%r1284, 1;
	shl.b32 	%r1285, %r1284, %r1283;
	selp.b32 	%r1286, 0, %r1285, %p628;
	or.b32 	%r1287, %r1286, %r6;
	or.b32 	%r1288, %r1287, %r2;
	cvt.u16.u32 	%rs1, %r1288;
	bra.uni 	$L__BB23_37;
$L__BB23_114:
	add.s32 	%r946, %r312, -14;
	setp.lt.u32 	%p413, %r946, 4;
	@%p413 bra 	$L__BB23_139;
	bra.uni 	$L__BB23_115;
$L__BB23_139:
	ld.local.b64 	%rd619, [%rd1];
	ld.local.b64 	%rd620, [%rd2];
	mul.rn.f64 	%rd621, %rd619, %rd620;
	add.u64 	%rd622, %SPL, 0;
	st.local.b64 	[%rd622], %rd621;
	ld.local.b64 	%rd623, [%rd1+8];
	ld.local.b64 	%rd624, [%rd2+8];
	mul.rn.f64 	%rd625, %rd623, %rd624;
	add.u64 	%rd626, %SP, 8;
	add.u64 	%rd627, %SPL, 8;
	st.local.b64 	[%rd627], %rd625;
	mul.rn.f64 	%rd628, %rd619, %rd624;
	add.u64 	%rd629, %SP, 16;
	add.u64 	%rd630, %SPL, 16;
	st.local.b64 	[%rd630], %rd628;
	mul.rn.f64 	%rd631, %rd620, %rd623;
	add.u64 	%rd632, %SP, 24;
	add.u64 	%rd633, %SPL, 24;
	st.local.b64 	[%rd633], %rd631;
	ld.local.b64 	%rd896, [%rd622];
	and.b32 	%r58, %r1360, -2;
	setp.ne.b32 	%p438, %r58, 12;
	@%p438 bra 	$L__BB23_163;
	shr.u64 	%rd34, %rd896, 48;
	cvt.u32.u64 	%r985, %rd34;
	and.b32 	%r59, %r985, 32768;
	shr.u64 	%rd634, %rd896, 52;
	cvt.u32.u64 	%r986, %rd634;
	and.b32 	%r60, %r986, 2047;
	setp.eq.b32 	%p440, %r60, 0;
	@%p440 bra 	$L__BB23_143;
	and.b64 	%rd33, %rd896, 4503599627370495;
	setp.eq.b32 	%p439, %r1360, 12;
	selp.b32 	%r61, 11, 8, %p439;
	selp.b32 	%r63, 31744, 32640, %p439;
	setp.ne.b32 	%p441, %r60, 2047;
	@%p441 bra 	$L__BB23_144;
	setp.eq.b64 	%p442, %rd33, 0;
	add.s32 	%r987, %r61, -2;
	mov.b32 	%r988, 1;
	shl.b32 	%r989, %r988, %r987;
	selp.b32 	%r990, 0, %r989, %p442;
	or.b32 	%r991, %r990, %r63;
	or.b32 	%r992, %r991, %r59;
	cvt.u16.u32 	%rs6, %r992;
	bra.uni 	$L__BB23_154;
$L__BB23_18:
	ld.local.b64 	%rd177, [%rd1];
	ld.local.b64 	%rd178, [%rd2];
	div.rn.f64 	%rd933, %rd177, %rd178;
	setp.ne.b32 	%p13, %r1359, 12;
	@%p13 bra 	$L__BB23_690;
	shr.u64 	%rd70, %rd933, 48;
	cvt.u32.u64 	%r315, %rd70;
	and.b32 	%r125, %r315, 32768;
	shr.u64 	%rd179, %rd933, 52;
	cvt.u32.u64 	%r316, %rd179;
	and.b32 	%r126, %r316, 2047;
	setp.eq.b32 	%p15, %r126, 0;
	@%p15 bra 	$L__BB23_283;
	and.b64 	%rd69, %rd933, 4503599627370495;
	setp.eq.b32 	%p14, %r1360, 12;
	selp.b32 	%r127, 11, 8, %p14;
	selp.b32 	%r129, 31744, 32640, %p14;
	setp.ne.b32 	%p16, %r126, 2047;
	@%p16 bra 	$L__BB23_284;
	setp.eq.b64 	%p17, %rd69, 0;
	add.s32 	%r317, %r127, -2;
	mov.b32 	%r318, 1;
	shl.b32 	%r319, %r318, %r317;
	selp.b32 	%r320, 0, %r319, %p17;
	or.b32 	%r321, %r320, %r129;
	or.b32 	%r322, %r321, %r125;
	cvt.u16.u32 	%rs12, %r322;
	bra.uni 	$L__BB23_294;
$L__BB23_115:
	ld.local.b64 	%rd593, [%rd1];
	ld.local.b64 	%rd594, [%rd2];
	mul.rn.f64 	%rd933, %rd593, %rd594;
	and.b32 	%r947, %r1360, -2;
	setp.ne.b32 	%p414, %r947, 12;
	@%p414 bra 	$L__BB23_690;
	shr.u64 	%rd28, %rd933, 48;
	cvt.u32.u64 	%r948, %rd28;
	and.b32 	%r47, %r948, 32768;
	shr.u64 	%rd595, %rd933, 52;
	cvt.u32.u64 	%r949, %rd595;
	and.b32 	%r48, %r949, 2047;
	setp.eq.b32 	%p416, %r48, 0;
	@%p416 bra 	$L__BB23_119;
	and.b64 	%rd27, %rd933, 4503599627370495;
	setp.eq.b32 	%p415, %r1360, 12;
	selp.b32 	%r49, 11, 8, %p415;
	selp.b32 	%r51, 31744, 32640, %p415;
	setp.ne.b32 	%p417, %r48, 2047;
	@%p417 bra 	$L__BB23_120;
	setp.eq.b64 	%p418, %rd27, 0;
	add.s32 	%r950, %r49, -2;
	mov.b32 	%r951, 1;
	shl.b32 	%r952, %r951, %r950;
	selp.b32 	%r953, 0, %r952, %p418;
	or.b32 	%r954, %r953, %r51;
	or.b32 	%r955, %r954, %r47;
	cvt.u16.u32 	%rs5, %r955;
	bra.uni 	$L__BB23_130;
$L__BB23_304:
	div.rn.f64 	%rd928, %rd76, %rd75;
	@%p677 bra 	$L__BB23_328;
	shr.u64 	%rd78, %rd928, 48;
	cvt.u32.u64 	%r352, %rd78;
	and.b32 	%r136, %r352, 32768;
	shr.u64 	%rd205, %rd928, 52;
	cvt.u32.u64 	%r353, %rd205;
	and.b32 	%r137, %r353, 2047;
	setp.eq.b32 	%p39, %r137, 0;
	@%p39 bra 	$L__BB23_308;
	and.b64 	%rd77, %rd928, 4503599627370495;
	setp.eq.b32 	%p38, %r1360, 12;
	selp.b32 	%r138, 11, 8, %p38;
	selp.b32 	%r140, 31744, 32640, %p38;
	setp.ne.b32 	%p40, %r137, 2047;
	@%p40 bra 	$L__BB23_309;
	setp.eq.b64 	%p41, %rd77, 0;
	add.s32 	%r354, %r138, -2;
	mov.b32 	%r355, 1;
	shl.b32 	%r356, %r355, %r354;
	selp.b32 	%r357, 0, %r356, %p41;
	or.b32 	%r358, %r357, %r140;
	or.b32 	%r359, %r358, %r136;
	cvt.u16.u32 	%rs13, %r359;
	bra.uni 	$L__BB23_319;
$L__BB23_70:
	cvt.u16.u32 	%rs3, %r25;
	bra.uni 	$L__BB23_81;
$L__BB23_26:
	cvt.u16.u32 	%rs1, %r2;
	bra.uni 	$L__BB23_37;
$L__BB23_71:
	selp.b32 	%r1215, -14, -126, %p578;
	add.s32 	%r30, %r26, -1023;
	or.b64 	%rd17, %rd15, 4503599627370496;
	setp.ge.s32 	%p582, %r30, %r1215;
	@%p582 bra 	$L__BB23_77;
	and.b64 	%rd18, %rd16, 32768;
	selp.b32 	%r1225, 28, -81, %p578;
	sub.s32 	%r31, %r1225, %r30;
	setp.gt.s32 	%p590, %r31, 0;
	@%p590 bra 	$L__BB23_74;
	bra.uni 	$L__BB23_73;
$L__BB23_74:
	setp.gt.u32 	%p591, %r31, 63;
	mov.b64 	%rd892, 0;
	@%p591 bra 	$L__BB23_76;
	shr.u64 	%rd797, %rd17, %r31;
	mov.b64 	%rd798, -1;
	shl.b64 	%rd799, %rd798, %r31;
	not.b64 	%rd800, %rd799;
	and.b64 	%rd801, %rd17, %rd800;
	add.s32 	%r1226, %r31, -1;
	mov.b64 	%rd802, 1;
	shl.b64 	%rd803, %rd802, %r1226;
	setp.gt.u64 	%p592, %rd801, %rd803;
	setp.eq.b64 	%p593, %rd801, %rd803;
	and.b64 	%rd804, %rd797, 1;
	setp.ne.b64 	%p594, %rd804, 0;
	and.pred 	%p595, %p593, %p594;
	or.pred 	%p596, %p592, %p595;
	selp.b64 	%rd805, 1, 0, %p596;
	add.s64 	%rd892, %rd797, %rd805;
	bra.uni 	$L__BB23_76;
$L__BB23_27:
	selp.b32 	%r1289, -14, -126, %p625;
	add.s32 	%r7, %r3, -1023;
	or.b64 	%rd5, %rd3, 4503599627370496;
	setp.ge.s32 	%p629, %r7, %r1289;
	@%p629 bra 	$L__BB23_33;
	and.b64 	%rd6, %rd4, 32768;
	selp.b32 	%r1299, 28, -81, %p625;
	sub.s32 	%r8, %r1299, %r7;
	setp.gt.s32 	%p637, %r8, 0;
	@%p637 bra 	$L__BB23_30;
	bra.uni 	$L__BB23_29;
$L__BB23_30:
	setp.gt.u32 	%p638, %r8, 63;
	mov.b64 	%rd890, 0;
	@%p638 bra 	$L__BB23_32;
	shr.u64 	%rd849, %rd5, %r8;
	mov.b64 	%rd850, -1;
	shl.b64 	%rd851, %rd850, %r8;
)QPTX";
        result += R"QPTX(
	not.b64 	%rd852, %rd851;
	and.b64 	%rd853, %rd5, %rd852;
	add.s32 	%r1300, %r8, -1;
	mov.b64 	%rd854, 1;
	shl.b64 	%rd855, %rd854, %r1300;
	setp.gt.u64 	%p639, %rd853, %rd855;
	setp.eq.b64 	%p640, %rd853, %rd855;
	and.b64 	%rd856, %rd849, 1;
	setp.ne.b64 	%p641, %rd856, 0;
	and.pred 	%p642, %p640, %p641;
	or.pred 	%p643, %p639, %p642;
	selp.b64 	%rd857, 1, 0, %p643;
	add.s64 	%rd890, %rd849, %rd857;
	bra.uni 	$L__BB23_32;
$L__BB23_283:
	cvt.u16.u32 	%rs12, %r125;
	bra.uni 	$L__BB23_294;
$L__BB23_143:
	cvt.u16.u32 	%rs6, %r59;
	bra.uni 	$L__BB23_154;
$L__BB23_119:
	cvt.u16.u32 	%rs5, %r47;
	bra.uni 	$L__BB23_130;
$L__BB23_284:
	selp.b32 	%r323, -14, -126, %p14;
	add.s32 	%r130, %r126, -1023;
	or.b64 	%rd71, %rd69, 4503599627370496;
	setp.ge.s32 	%p18, %r130, %r323;
	@%p18 bra 	$L__BB23_290;
	and.b64 	%rd72, %rd70, 32768;
	selp.b32 	%r333, 28, -81, %p14;
	sub.s32 	%r131, %r333, %r130;
	setp.gt.s32 	%p26, %r131, 0;
	@%p26 bra 	$L__BB23_287;
	bra.uni 	$L__BB23_286;
$L__BB23_287:
	setp.gt.u32 	%p27, %r131, 63;
	mov.b64 	%rd905, 0;
	@%p27 bra 	$L__BB23_289;
	shr.u64 	%rd193, %rd71, %r131;
	mov.b64 	%rd194, -1;
	shl.b64 	%rd195, %rd194, %r131;
	not.b64 	%rd196, %rd195;
	and.b64 	%rd197, %rd71, %rd196;
	add.s32 	%r334, %r131, -1;
	mov.b64 	%rd198, 1;
	shl.b64 	%rd199, %rd198, %r334;
	setp.gt.u64 	%p28, %rd197, %rd199;
	setp.eq.b64 	%p29, %rd197, %rd199;
	and.b64 	%rd200, %rd193, 1;
	setp.ne.b64 	%p30, %rd200, 0;
	and.pred 	%p31, %p29, %p30;
	or.pred 	%p32, %p28, %p31;
	selp.b64 	%rd201, 1, 0, %p32;
	add.s64 	%rd905, %rd193, %rd201;
	bra.uni 	$L__BB23_289;
$L__BB23_77:
	selp.b32 	%r28, 15, 127, %p578;
	sub.s32 	%r1216, 53, %r27;
	shr.u64 	%rd784, %rd17, %r1216;
	mov.b64 	%rd785, -1;
	shl.b64 	%rd786, %rd785, %r1216;
	not.b64 	%rd787, %rd786;
	and.b64 	%rd788, %rd933, %rd787;
	sub.s32 	%r1217, 52, %r27;
	mov.b64 	%rd789, 1;
	shl.b64 	%rd790, %rd789, %r1217;
	setp.gt.u64 	%p583, %rd788, %rd790;
	setp.eq.b64 	%p584, %rd788, %rd790;
	and.b64 	%rd791, %rd784, 1;
	setp.ne.b64 	%p585, %rd791, 0;
	and.pred 	%p586, %p584, %p585;
	or.pred 	%p587, %p583, %p586;
	selp.b64 	%rd792, 1, 0, %p587;
	add.s64 	%rd19, %rd784, %rd792;
	shl.b64 	%rd20, %rd789, %r27;
	setp.eq.b64 	%p588, %rd19, %rd20;
	add.s32 	%r1218, %r26, -1022;
	selp.b32 	%r32, %r1218, %r30, %p588;
	setp.le.s32 	%p589, %r32, %r28;
	@%p589 bra 	$L__BB23_79;
	or.b32 	%r1365, %r25, %r29;
	bra.uni 	$L__BB23_80;
$L__BB23_144:
	selp.b32 	%r993, -14, -126, %p439;
	add.s32 	%r64, %r60, -1023;
	or.b64 	%rd35, %rd33, 4503599627370496;
	setp.ge.s32 	%p443, %r64, %r993;
	@%p443 bra 	$L__BB23_150;
	and.b64 	%rd36, %rd34, 32768;
	selp.b32 	%r1003, 28, -81, %p439;
	sub.s32 	%r65, %r1003, %r64;
	setp.gt.s32 	%p451, %r65, 0;
	@%p451 bra 	$L__BB23_147;
	bra.uni 	$L__BB23_146;
$L__BB23_147:
	setp.gt.u32 	%p452, %r65, 63;
	mov.b64 	%rd895, 0;
	@%p452 bra 	$L__BB23_149;
	shr.u64 	%rd648, %rd35, %r65;
	mov.b64 	%rd649, -1;
	shl.b64 	%rd650, %rd649, %r65;
	not.b64 	%rd651, %rd650;
	and.b64 	%rd652, %rd35, %rd651;
	add.s32 	%r1004, %r65, -1;
	mov.b64 	%rd653, 1;
	shl.b64 	%rd654, %rd653, %r1004;
	setp.gt.u64 	%p453, %rd652, %rd654;
	setp.eq.b64 	%p454, %rd652, %rd654;
	and.b64 	%rd655, %rd648, 1;
	setp.ne.b64 	%p455, %rd655, 0;
	and.pred 	%p456, %p454, %p455;
	or.pred 	%p457, %p453, %p456;
	selp.b64 	%rd656, 1, 0, %p457;
	add.s64 	%rd895, %rd648, %rd656;
	bra.uni 	$L__BB23_149;
$L__BB23_120:
	selp.b32 	%r956, -14, -126, %p415;
	add.s32 	%r52, %r48, -1023;
	or.b64 	%rd29, %rd27, 4503599627370496;
	setp.ge.s32 	%p419, %r52, %r956;
	@%p419 bra 	$L__BB23_126;
	and.b64 	%rd30, %rd28, 32768;
	selp.b32 	%r966, 28, -81, %p415;
	sub.s32 	%r53, %r966, %r52;
	setp.gt.s32 	%p427, %r53, 0;
	@%p427 bra 	$L__BB23_123;
	bra.uni 	$L__BB23_122;
$L__BB23_123:
	setp.gt.u32 	%p428, %r53, 63;
	mov.b64 	%rd894, 0;
	@%p428 bra 	$L__BB23_125;
	shr.u64 	%rd609, %rd29, %r53;
	mov.b64 	%rd610, -1;
	shl.b64 	%rd611, %rd610, %r53;
	not.b64 	%rd612, %rd611;
	and.b64 	%rd613, %rd29, %rd612;
	add.s32 	%r967, %r53, -1;
	mov.b64 	%rd614, 1;
	shl.b64 	%rd615, %rd614, %r967;
	setp.gt.u64 	%p429, %rd613, %rd615;
	setp.eq.b64 	%p430, %rd613, %rd615;
	and.b64 	%rd616, %rd609, 1;
	setp.ne.b64 	%p431, %rd616, 0;
	and.pred 	%p432, %p430, %p431;
	or.pred 	%p433, %p429, %p432;
	selp.b64 	%rd617, 1, 0, %p433;
	add.s64 	%rd894, %rd609, %rd617;
	bra.uni 	$L__BB23_125;
$L__BB23_33:
	selp.b32 	%r5, 15, 127, %p625;
	sub.s32 	%r1290, 53, %r4;
	shr.u64 	%rd836, %rd5, %r1290;
	mov.b64 	%rd837, -1;
	shl.b64 	%rd838, %rd837, %r1290;
	not.b64 	%rd839, %rd838;
	and.b64 	%rd840, %rd933, %rd839;
	sub.s32 	%r1291, 52, %r4;
	mov.b64 	%rd841, 1;
	shl.b64 	%rd842, %rd841, %r1291;
	setp.gt.u64 	%p630, %rd840, %rd842;
	setp.eq.b64 	%p631, %rd840, %rd842;
	and.b64 	%rd843, %rd836, 1;
	setp.ne.b64 	%p632, %rd843, 0;
	and.pred 	%p633, %p631, %p632;
	or.pred 	%p634, %p630, %p633;
	selp.b64 	%rd844, 1, 0, %p634;
	add.s64 	%rd7, %rd836, %rd844;
	shl.b64 	%rd8, %rd841, %r4;
	setp.eq.b64 	%p635, %rd7, %rd8;
	add.s32 	%r1292, %r3, -1022;
	selp.b32 	%r9, %r1292, %r7, %p635;
	setp.le.s32 	%p636, %r9, %r5;
	@%p636 bra 	$L__BB23_35;
	or.b32 	%r1361, %r2, %r6;
	bra.uni 	$L__BB23_36;
$L__BB23_476:
	cvt.u16.u32 	%rs20, %r213;
	bra.uni 	$L__BB23_487;
$L__BB23_308:
	cvt.u16.u32 	%rs13, %r136;
	bra.uni 	$L__BB23_319;
$L__BB23_477:
	selp.b32 	%r619, -14, -126, %p199;
	add.s32 	%r218, %r214, -1023;
	or.b64 	%rd123, %rd121, 4503599627370496;
	setp.ge.s32 	%p203, %r218, %r619;
	@%p203 bra 	$L__BB23_483;
	and.b64 	%rd124, %rd122, 32768;
	selp.b32 	%r629, 28, -81, %p199;
	sub.s32 	%r219, %r629, %r218;
	setp.gt.s32 	%p211, %r219, 0;
	@%p211 bra 	$L__BB23_480;
	bra.uni 	$L__BB23_479;
$L__BB23_480:
	setp.gt.u32 	%p212, %r219, 63;
	mov.b64 	%rd918, 0;
	@%p212 bra 	$L__BB23_482;
	shr.u64 	%rd387, %rd123, %r219;
	mov.b64 	%rd388, -1;
	shl.b64 	%rd389, %rd388, %r219;
	not.b64 	%rd390, %rd389;
	and.b64 	%rd391, %rd123, %rd390;
	add.s32 	%r630, %r219, -1;
	mov.b64 	%rd392, 1;
	shl.b64 	%rd393, %rd392, %r630;
	setp.gt.u64 	%p213, %rd391, %rd393;
	setp.eq.b64 	%p214, %rd391, %rd393;
	and.b64 	%rd394, %rd387, 1;
	setp.ne.b64 	%p215, %rd394, 0;
	and.pred 	%p216, %p214, %p215;
	or.pred 	%p217, %p213, %p216;
	selp.b64 	%rd395, 1, 0, %p217;
	add.s64 	%rd918, %rd387, %rd395;
	bra.uni 	$L__BB23_482;
$L__BB23_309:
	selp.b32 	%r360, -14, -126, %p38;
	add.s32 	%r141, %r137, -1023;
	or.b64 	%rd79, %rd77, 4503599627370496;
	setp.ge.s32 	%p42, %r141, %r360;
	@%p42 bra 	$L__BB23_315;
	and.b64 	%rd80, %rd78, 32768;
	selp.b32 	%r370, 28, -81, %p38;
	sub.s32 	%r142, %r370, %r141;
	setp.gt.s32 	%p50, %r142, 0;
	@%p50 bra 	$L__BB23_312;
	bra.uni 	$L__BB23_311;
$L__BB23_312:
	setp.gt.u32 	%p51, %r142, 63;
	mov.b64 	%rd906, 0;
	@%p51 bra 	$L__BB23_314;
	shr.u64 	%rd219, %rd79, %r142;
	mov.b64 	%rd220, -1;
	shl.b64 	%rd221, %rd220, %r142;
	not.b64 	%rd222, %rd221;
	and.b64 	%rd223, %rd79, %rd222;
	add.s32 	%r371, %r142, -1;
	mov.b64 	%rd224, 1;
	shl.b64 	%rd225, %rd224, %r371;
	setp.gt.u64 	%p52, %rd223, %rd225;
	setp.eq.b64 	%p53, %rd223, %rd225;
	and.b64 	%rd226, %rd219, 1;
	setp.ne.b64 	%p54, %rd226, 0;
	and.pred 	%p55, %p53, %p54;
	or.pred 	%p56, %p52, %p55;
	selp.b64 	%rd227, 1, 0, %p56;
	add.s64 	%rd906, %rd219, %rd227;
	bra.uni 	$L__BB23_314;
$L__BB23_290:
	selp.b32 	%r128, 15, 127, %p14;
	sub.s32 	%r324, 53, %r127;
	shr.u64 	%rd180, %rd71, %r324;
	mov.b64 	%rd181, -1;
	shl.b64 	%rd182, %rd181, %r324;
	not.b64 	%rd183, %rd182;
	and.b64 	%rd184, %rd933, %rd183;
	sub.s32 	%r325, 52, %r127;
	mov.b64 	%rd185, 1;
	shl.b64 	%rd186, %rd185, %r325;
	setp.gt.u64 	%p19, %rd184, %rd186;
	setp.eq.b64 	%p20, %rd184, %rd186;
	and.b64 	%rd187, %rd180, 1;
	setp.ne.b64 	%p21, %rd187, 0;
	and.pred 	%p22, %p20, %p21;
	or.pred 	%p23, %p19, %p22;
	selp.b64 	%rd188, 1, 0, %p23;
	add.s64 	%rd73, %rd180, %rd188;
	shl.b64 	%rd74, %rd185, %r127;
	setp.eq.b64 	%p24, %rd73, %rd74;
	add.s32 	%r326, %r126, -1022;
	selp.b32 	%r132, %r326, %r130, %p24;
	setp.le.s32 	%p25, %r132, %r128;
	@%p25 bra 	$L__BB23_292;
	or.b32 	%r1383, %r125, %r129;
	bra.uni 	$L__BB23_293;
$L__BB23_79:
	selp.b32 	%r1219, 1, 0, %p588;
	shr.u64 	%rd793, %rd19, %r1219;
	add.s32 	%r1220, %r32, %r28;
	add.s32 	%r1221, %r27, -1;
	shl.b32 	%r1222, %r1220, %r1221;
	shl.b64 	%rd794, %rd785, %r1221;
	not.b64 	%rd795, %rd794;
	and.b64 	%rd796, %rd793, %rd795;
	cvt.u32.u64 	%r1223, %rd796;
	or.b32 	%r1224, %r1222, %r1223;
	or.b32 	%r1365, %r1224, %r25;
$L__BB23_80:
	cvt.u16.u32 	%rs3, %r1365;
	bra.uni 	$L__BB23_81;
$L__BB23_150:
	selp.b32 	%r62, 15, 127, %p439;
	sub.s32 	%r994, 53, %r61;
	shr.u64 	%rd635, %rd35, %r994;
	mov.b64 	%rd636, -1;
	shl.b64 	%rd637, %rd636, %r994;
	not.b64 	%rd638, %rd637;
	and.b64 	%rd639, %rd896, %rd638;
	sub.s32 	%r995, 52, %r61;
	mov.b64 	%rd640, 1;
	shl.b64 	%rd641, %rd640, %r995;
	setp.gt.u64 	%p444, %rd639, %rd641;
	setp.eq.b64 	%p445, %rd639, %rd641;
	and.b64 	%rd642, %rd635, 1;
	setp.ne.b64 	%p446, %rd642, 0;
	and.pred 	%p447, %p445, %p446;
	or.pred 	%p448, %p444, %p447;
	selp.b64 	%rd643, 1, 0, %p448;
	add.s64 	%rd37, %rd635, %rd643;
	shl.b64 	%rd38, %rd640, %r61;
	setp.eq.b64 	%p449, %rd37, %rd38;
	add.s32 	%r996, %r60, -1022;
	selp.b32 	%r66, %r996, %r64, %p449;
	setp.le.s32 	%p450, %r66, %r62;
	@%p450 bra 	$L__BB23_152;
	or.b32 	%r1371, %r59, %r63;
	bra.uni 	$L__BB23_153;
$L__BB23_126:
	selp.b32 	%r50, 15, 127, %p415;
	sub.s32 	%r957, 53, %r49;
	shr.u64 	%rd596, %rd29, %r957;
	mov.b64 	%rd597, -1;
	shl.b64 	%rd598, %rd597, %r957;
	not.b64 	%rd599, %rd598;
	and.b64 	%rd600, %rd933, %rd599;
	sub.s32 	%r958, 52, %r49;
	mov.b64 	%rd601, 1;
	shl.b64 	%rd602, %rd601, %r958;
	setp.gt.u64 	%p420, %rd600, %rd602;
	setp.eq.b64 	%p421, %rd600, %rd602;
	and.b64 	%rd603, %rd596, 1;
	setp.ne.b64 	%p422, %rd603, 0;
	and.pred 	%p423, %p421, %p422;
	or.pred 	%p424, %p420, %p423;
	selp.b64 	%rd604, 1, 0, %p424;
	add.s64 	%rd31, %rd596, %rd604;
	shl.b64 	%rd32, %rd601, %r49;
	setp.eq.b64 	%p425, %rd31, %rd32;
	add.s32 	%r959, %r48, -1022;
	selp.b32 	%r54, %r959, %r52, %p425;
	setp.le.s32 	%p426, %r54, %r50;
	@%p426 bra 	$L__BB23_128;
	or.b32 	%r1369, %r47, %r51;
	bra.uni 	$L__BB23_129;
$L__BB23_35:
	selp.b32 	%r1293, 1, 0, %p635;
	shr.u64 	%rd845, %rd7, %r1293;
	add.s32 	%r1294, %r9, %r5;
	add.s32 	%r1295, %r4, -1;
	shl.b32 	%r1296, %r1294, %r1295;
	shl.b64 	%rd846, %rd837, %r1295;
	not.b64 	%rd847, %rd846;
	and.b64 	%rd848, %rd845, %rd847;
	cvt.u32.u64 	%r1297, %rd848;
	or.b32 	%r1298, %r1296, %r1297;
	or.b32 	%r1361, %r1298, %r2;
$L__BB23_36:
	cvt.u16.u32 	%rs1, %r1361;
	bra.uni 	$L__BB23_37;
$L__BB23_73:
	neg.s32 	%r1227, %r31;
	shl.b64 	%rd892, %rd17, %r1227;
$L__BB23_76:
	or.b64 	%rd806, %rd892, %rd18;
	cvt.u16.u64 	%rs3, %rd806;
$L__BB23_81:
	setp.ne.b32 	%p597, %r1360, 13;
	cvt.u32.u16 	%r33, %rs3;
	@%p597 bra 	$L__BB23_83;
	shl.b32 	%r1366, %r33, 16;
	bra.uni 	$L__BB23_89;
$L__BB23_83:
	cvt.s32.s16 	%r1228, %rs3;
	and.b32 	%r1366, %r1228, -2147483648;
	bfe.u32 	%r34, %r33, 10, 5;
	setp.eq.b32 	%p598, %r34, 31;
	@%p598 bra 	$L__BB23_87;
	and.b32 	%r35, %r33, 1023;
	setp.ne.b32 	%p599, %r34, 0;
	@%p599 bra 	$L__BB23_88;
	setp.eq.b32 	%p600, %r35, 0;
	@%p600 bra 	$L__BB23_89;
	clz.b32 	%r1231, %r35;
	xor.b32 	%r1232, %r1231, 31;
	sub.s32 	%r1233, 9, %r1232;
	shl.b32 	%r1234, %r33, %r1233;
	shl.b32 	%r1235, %r1232, 23;
	shl.b32 	%r1236, %r1234, 14;
	and.b32 	%r1237, %r1236, 8372224;
	add.s32 	%r1238, %r1235, %r1366;
	add.s32 	%r1239, %r1238, %r1237;
	add.s32 	%r1366, %r1239, 864026624;
	bra.uni 	$L__BB23_89;
$L__BB23_87:
	shl.b32 	%r1229, %r33, 13;
	or.b32 	%r1230, %r1366, %r1229;
	or.b32 	%r1366, %r1230, 2139095040;
	bra.uni 	$L__BB23_89;
$L__BB23_88:
	shl.b32 	%r1240, %r34, 23;
	shl.b32 	%r1241, %r35, 13;
	or.b32 	%r1242, %r1240, %r1241;
	add.s32 	%r1243, %r1242, %r1366;
	add.s32 	%r1366, %r1243, 939524096;
$L__BB23_89:
	cvt.f64.f32 	%rd933, %r1366;
$L__BB23_90:
	ld.local.b64 	%rd807, [%rd1+8];
	ld.local.b64 	%rd808, [%rd2+8];
	sub.rn.f64 	%rd932, %rd807, %rd808;
	@%p577 bra 	$L__BB23_690;
	shr.u64 	%rd22, %rd932, 48;
	cvt.u32.u64 	%r1244, %rd22;
	and.b32 	%r36, %r1244, 32768;
	shr.u64 	%rd809, %rd932, 52;
	cvt.u32.u64 	%r1245, %rd809;
	and.b32 	%r37, %r1245, 2047;
	setp.eq.b32 	%p602, %r37, 0;
	@%p602 bra 	$L__BB23_94;
	and.b64 	%rd21, %rd932, 4503599627370495;
	setp.eq.b32 	%p601, %r1360, 12;
	selp.b32 	%r38, 11, 8, %p601;
	selp.b32 	%r40, 31744, 32640, %p601;
	setp.ne.b32 	%p603, %r37, 2047;
	@%p603 bra 	$L__BB23_95;
	setp.eq.b64 	%p604, %rd21, 0;
	add.s32 	%r1246, %r38, -2;
	mov.b32 	%r1247, 1;
	shl.b32 	%r1248, %r1247, %r1246;
	selp.b32 	%r1249, 0, %r1248, %p604;
	or.b32 	%r1250, %r1249, %r40;
	or.b32 	%r1251, %r1250, %r36;
	cvt.u16.u32 	%rs4, %r1251;
	bra.uni 	$L__BB23_105;
$L__BB23_94:
	cvt.u16.u32 	%rs4, %r36;
	bra.uni 	$L__BB23_105;
$L__BB23_95:
	selp.b32 	%r1252, -14, -126, %p601;
	add.s32 	%r41, %r37, -1023;
	or.b64 	%rd23, %rd21, 4503599627370496;
	setp.ge.s32 	%p605, %r41, %r1252;
	@%p605 bra 	$L__BB23_101;
	and.b64 	%rd24, %rd22, 32768;
	selp.b32 	%r1262, 28, -81, %p601;
	sub.s32 	%r42, %r1262, %r41;
	setp.gt.s32 	%p613, %r42, 0;
	@%p613 bra 	$L__BB23_98;
	bra.uni 	$L__BB23_97;
$L__BB23_98:
	setp.gt.u32 	%p614, %r42, 63;
	mov.b64 	%rd893, 0;
	@%p614 bra 	$L__BB23_100;
	shr.u64 	%rd823, %rd23, %r42;
	mov.b64 	%rd824, -1;
	shl.b64 	%rd825, %rd824, %r42;
	not.b64 	%rd826, %rd825;
	and.b64 	%rd827, %rd23, %rd826;
	add.s32 	%r1263, %r42, -1;
	mov.b64 	%rd828, 1;
	shl.b64 	%rd829, %rd828, %r1263;
	setp.gt.u64 	%p615, %rd827, %rd829;
	setp.eq.b64 	%p616, %rd827, %rd829;
	and.b64 	%rd830, %rd823, 1;
	setp.ne.b64 	%p617, %rd830, 0;
	and.pred 	%p618, %p616, %p617;
	or.pred 	%p619, %p615, %p618;
	selp.b64 	%rd831, 1, 0, %p619;
	add.s64 	%rd893, %rd823, %rd831;
	bra.uni 	$L__BB23_100;
$L__BB23_101:
	selp.b32 	%r39, 15, 127, %p601;
	sub.s32 	%r1253, 53, %r38;
	shr.u64 	%rd810, %rd23, %r1253;
	mov.b64 	%rd811, -1;
	shl.b64 	%rd812, %rd811, %r1253;
	not.b64 	%rd813, %rd812;
	and.b64 	%rd814, %rd932, %rd813;
	sub.s32 	%r1254, 52, %r38;
	mov.b64 	%rd815, 1;
	shl.b64 	%rd816, %rd815, %r1254;
	setp.gt.u64 	%p606, %rd814, %rd816;
	setp.eq.b64 	%p607, %rd814, %rd816;
	and.b64 	%rd817, %rd810, 1;
	setp.ne.b64 	%p608, %rd817, 0;
	and.pred 	%p609, %p607, %p608;
	or.pred 	%p610, %p606, %p609;
	selp.b64 	%rd818, 1, 0, %p610;
	add.s64 	%rd25, %rd810, %rd818;
	shl.b64 	%rd26, %rd815, %r38;
	setp.eq.b64 	%p611, %rd25, %rd26;
	add.s32 	%r1255, %r37, -1022;
	selp.b32 	%r43, %r1255, %r41, %p611;
	setp.le.s32 	%p612, %r43, %r39;
	@%p612 bra 	$L__BB23_103;
	or.b32 	%r1367, %r36, %r40;
	bra.uni 	$L__BB23_104;
$L__BB23_103:
	selp.b32 	%r1256, 1, 0, %p611;
	shr.u64 	%rd819, %rd25, %r1256;
	add.s32 	%r1257, %r43, %r39;
	add.s32 	%r1258, %r38, -1;
	shl.b32 	%r1259, %r1257, %r1258;
	shl.b64 	%rd820, %rd811, %r1258;
	not.b64 	%rd821, %rd820;
	and.b64 	%rd822, %rd819, %rd821;
	cvt.u32.u64 	%r1260, %rd822;
	or.b32 	%r1261, %r1259, %r1260;
	or.b32 	%r1367, %r1261, %r36;
$L__BB23_104:
	cvt.u16.u32 	%rs4, %r1367;
	bra.uni 	$L__BB23_105;
$L__BB23_97:
	neg.s32 	%r1264, %r42;
	shl.b64 	%rd893, %rd23, %r1264;
$L__BB23_100:
	or.b64 	%rd832, %rd893, %rd24;
	cvt.u16.u64 	%rs4, %rd832;
$L__BB23_105:
	setp.ne.b32 	%p620, %r1360, 13;
	cvt.u32.u16 	%r44, %rs4;
	@%p620 bra 	$L__BB23_107;
	shl.b32 	%r1368, %r44, 16;
	bra.uni 	$L__BB23_113;
$L__BB23_107:
	cvt.s32.s16 	%r1265, %rs4;
	and.b32 	%r1368, %r1265, -2147483648;
	bfe.u32 	%r45, %r44, 10, 5;
	setp.eq.b32 	%p621, %r45, 31;
	@%p621 bra 	$L__BB23_111;
	and.b32 	%r46, %r44, 1023;
	setp.ne.b32 	%p622, %r45, 0;
	@%p622 bra 	$L__BB23_112;
	setp.eq.b32 	%p623, %r46, 0;
	@%p623 bra 	$L__BB23_113;
	clz.b32 	%r1268, %r46;
	xor.b32 	%r1269, %r1268, 31;
	sub.s32 	%r1270, 9, %r1269;
	shl.b32 	%r1271, %r44, %r1270;
	shl.b32 	%r1272, %r1269, 23;
	shl.b32 	%r1273, %r1271, 14;
	and.b32 	%r1274, %r1273, 8372224;
	add.s32 	%r1275, %r1272, %r1368;
	add.s32 	%r1276, %r1275, %r1274;
	add.s32 	%r1368, %r1276, 864026624;
	bra.uni 	$L__BB23_113;
$L__BB23_111:
	shl.b32 	%r1266, %r44, 13;
	or.b32 	%r1267, %r1368, %r1266;
	or.b32 	%r1368, %r1267, 2139095040;
	bra.uni 	$L__BB23_113;
$L__BB23_112:
	shl.b32 	%r1277, %r45, 23;
	shl.b32 	%r1278, %r46, 13;
	or.b32 	%r1279, %r1277, %r1278;
	add.s32 	%r1280, %r1279, %r1368;
	add.s32 	%r1368, %r1280, 939524096;
$L__BB23_113:
	cvt.f64.f32 	%rd932, %r1368;
	bra.uni 	$L__BB23_690;
$L__BB23_29:
	neg.s32 	%r1301, %r8;
	shl.b64 	%rd890, %rd5, %r1301;
$L__BB23_32:
	or.b64 	%rd858, %rd890, %rd6;
	cvt.u16.u64 	%rs1, %rd858;
$L__BB23_37:
	setp.ne.b32 	%p644, %r1360, 13;
	cvt.u32.u16 	%r10, %rs1;
	@%p644 bra 	$L__BB23_39;
	shl.b32 	%r1362, %r10, 16;
	bra.uni 	$L__BB23_45;
$L__BB23_39:
	cvt.s32.s16 	%r1302, %rs1;
	and.b32 	%r1362, %r1302, -2147483648;
	bfe.u32 	%r11, %r10, 10, 5;
	setp.eq.b32 	%p645, %r11, 31;
	@%p645 bra 	$L__BB23_43;
	and.b32 	%r12, %r10, 1023;
	setp.ne.b32 	%p646, %r11, 0;
	@%p646 bra 	$L__BB23_44;
	setp.eq.b32 	%p647, %r12, 0;
	@%p647 bra 	$L__BB23_45;
	clz.b32 	%r1305, %r12;
	xor.b32 	%r1306, %r1305, 31;
	sub.s32 	%r1307, 9, %r1306;
	shl.b32 	%r1308, %r10, %r1307;
	shl.b32 	%r1309, %r1306, 23;
	shl.b32 	%r1310, %r1308, 14;
	and.b32 	%r1311, %r1310, 8372224;
	add.s32 	%r1312, %r1309, %r1362;
	add.s32 	%r1313, %r1312, %r1311;
	add.s32 	%r1362, %r1313, 864026624;
	bra.uni 	$L__BB23_45;
$L__BB23_43:
	shl.b32 	%r1303, %r10, 13;
	or.b32 	%r1304, %r1362, %r1303;
	or.b32 	%r1362, %r1304, 2139095040;
	bra.uni 	$L__BB23_45;
$L__BB23_44:
	shl.b32 	%r1314, %r11, 23;
	shl.b32 	%r1315, %r12, 13;
	or.b32 	%r1316, %r1314, %r1315;
	add.s32 	%r1317, %r1316, %r1362;
	add.s32 	%r1362, %r1317, 939524096;
$L__BB23_45:
	cvt.f64.f32 	%rd933, %r1362;
$L__BB23_46:
	ld.local.b64 	%rd859, [%rd1+8];
	ld.local.b64 	%rd860, [%rd2+8];
	add.rn.f64 	%rd932, %rd859, %rd860;
	@%p624 bra 	$L__BB23_690;
	shr.u64 	%rd10, %rd932, 48;
	cvt.u32.u64 	%r1318, %rd10;
	and.b32 	%r13, %r1318, 32768;
	shr.u64 	%rd861, %rd932, 52;
	cvt.u32.u64 	%r1319, %rd861;
	and.b32 	%r14, %r1319, 2047;
	setp.eq.b32 	%p649, %r14, 0;
	@%p649 bra 	$L__BB23_50;
	and.b64 	%rd9, %rd932, 4503599627370495;
	setp.eq.b32 	%p648, %r1360, 12;
	selp.b32 	%r15, 11, 8, %p648;
	selp.b32 	%r17, 31744, 32640, %p648;
	setp.ne.b32 	%p650, %r14, 2047;
	@%p650 bra 	$L__BB23_51;
	setp.eq.b64 	%p651, %rd9, 0;
	add.s32 	%r1320, %r15, -2;
	mov.b32 	%r1321, 1;
	shl.b32 	%r1322, %r1321, %r1320;
	selp.b32 	%r1323, 0, %r1322, %p651;
	or.b32 	%r1324, %r1323, %r17;
	or.b32 	%r1325, %r1324, %r13;
	cvt.u16.u32 	%rs2, %r1325;
	bra.uni 	$L__BB23_61;
$L__BB23_50:
	cvt.u16.u32 	%rs2, %r13;
	bra.uni 	$L__BB23_61;
$L__BB23_51:
	selp.b32 	%r1326, -14, -126, %p648;
	add.s32 	%r18, %r14, -1023;
	or.b64 	%rd11, %rd9, 4503599627370496;
	setp.ge.s32 	%p652, %r18, %r1326;
	@%p652 bra 	$L__BB23_57;
	and.b64 	%rd12, %rd10, 32768;
	selp.b32 	%r1336, 28, -81, %p648;
	sub.s32 	%r19, %r1336, %r18;
	setp.gt.s32 	%p660, %r19, 0;
	@%p660 bra 	$L__BB23_54;
	bra.uni 	$L__BB23_53;
$L__BB23_54:
	setp.gt.u32 	%p661, %r19, 63;
	mov.b64 	%rd891, 0;
	@%p661 bra 	$L__BB23_56;
	shr.u64 	%rd875, %rd11, %r19;
	mov.b64 	%rd876, -1;
	shl.b64 	%rd877, %rd876, %r19;
	not.b64 	%rd878, %rd877;
	and.b64 	%rd879, %rd11, %rd878;
	add.s32 	%r1337, %r19, -1;
	mov.b64 	%rd880, 1;
	shl.b64 	%rd881, %rd880, %r1337;
	setp.gt.u64 	%p662, %rd879, %rd881;
	setp.eq.b64 	%p663, %rd879, %rd881;
	and.b64 	%rd882, %rd875, 1;
	setp.ne.b64 	%p664, %rd882, 0;
	and.pred 	%p665, %p663, %p664;
	or.pred 	%p666, %p662, %p665;
	selp.b64 	%rd883, 1, 0, %p666;
	add.s64 	%rd891, %rd875, %rd883;
	bra.uni 	$L__BB23_56;
$L__BB23_57:
	selp.b32 	%r16, 15, 127, %p648;
	sub.s32 	%r1327, 53, %r15;
	shr.u64 	%rd862, %rd11, %r1327;
	mov.b64 	%rd863, -1;
	shl.b64 	%rd864, %rd863, %r1327;
	not.b64 	%rd865, %rd864;
	and.b64 	%rd866, %rd932, %rd865;
	sub.s32 	%r1328, 52, %r15;
	mov.b64 	%rd867, 1;
	shl.b64 	%rd868, %rd867, %r1328;
	setp.gt.u64 	%p653, %rd866, %rd868;
	setp.eq.b64 	%p654, %rd866, %rd868;
	and.b64 	%rd869, %rd862, 1;
	setp.ne.b64 	%p655, %rd869, 0;
	and.pred 	%p656, %p654, %p655;
	or.pred 	%p657, %p653, %p656;
	selp.b64 	%rd870, 1, 0, %p657;
	add.s64 	%rd13, %rd862, %rd870;
	shl.b64 	%rd14, %rd867, %r15;
	setp.eq.b64 	%p658, %rd13, %rd14;
	add.s32 	%r1329, %r14, -1022;
	selp.b32 	%r20, %r1329, %r18, %p658;
	setp.le.s32 	%p659, %r20, %r16;
	@%p659 bra 	$L__BB23_59;
	or.b32 	%r1363, %r13, %r17;
	bra.uni 	$L__BB23_60;
$L__BB23_59:
	selp.b32 	%r1330, 1, 0, %p658;
	shr.u64 	%rd871, %rd13, %r1330;
	add.s32 	%r1331, %r20, %r16;
	add.s32 	%r1332, %r15, -1;
	shl.b32 	%r1333, %r1331, %r1332;
	shl.b64 	%rd872, %rd863, %r1332;
	not.b64 	%rd873, %rd872;
	and.b64 	%rd874, %rd871, %rd873;
	cvt.u32.u64 	%r1334, %rd874;
	or.b32 	%r1335, %r1333, %r1334;
	or.b32 	%r1363, %r1335, %r13;
$L__BB23_60:
	cvt.u16.u32 	%rs2, %r1363;
	bra.uni 	$L__BB23_61;
$L__BB23_53:
	neg.s32 	%r1338, %r19;
	shl.b64 	%rd891, %rd11, %r1338;
$L__BB23_56:
	or.b64 	%rd884, %rd891, %rd12;
	cvt.u16.u64 	%rs2, %rd884;
$L__BB23_61:
	setp.ne.b32 	%p667, %r1360, 13;
	cvt.u32.u16 	%r21, %rs2;
	@%p667 bra 	$L__BB23_63;
	shl.b32 	%r1364, %r21, 16;
	bra.uni 	$L__BB23_69;
$L__BB23_63:
	cvt.s32.s16 	%r1339, %rs2;
	and.b32 	%r1364, %r1339, -2147483648;
	bfe.u32 	%r22, %r21, 10, 5;
	setp.eq.b32 	%p668, %r22, 31;
	@%p668 bra 	$L__BB23_67;
	and.b32 	%r23, %r21, 1023;
	setp.ne.b32 	%p669, %r22, 0;
	@%p669 bra 	$L__BB23_68;
	setp.eq.b32 	%p670, %r23, 0;
	@%p670 bra 	$L__BB23_69;
	clz.b32 	%r1342, %r23;
	xor.b32 	%r1343, %r1342, 31;
	sub.s32 	%r1344, 9, %r1343;
	shl.b32 	%r1345, %r21, %r1344;
	shl.b32 	%r1346, %r1343, 23;
	shl.b32 	%r1347, %r1345, 14;
	and.b32 	%r1348, %r1347, 8372224;
	add.s32 	%r1349, %r1346, %r1364;
	add.s32 	%r1350, %r1349, %r1348;
	add.s32 	%r1364, %r1350, 864026624;
	bra.uni 	$L__BB23_69;
$L__BB23_67:
	shl.b32 	%r1340, %r21, 13;
	or.b32 	%r1341, %r1364, %r1340;
	or.b32 	%r1364, %r1341, 2139095040;
	bra.uni 	$L__BB23_69;
$L__BB23_68:
	shl.b32 	%r1351, %r22, 23;
	shl.b32 	%r1352, %r23, 13;
	or.b32 	%r1353, %r1351, %r1352;
	add.s32 	%r1354, %r1353, %r1364;
	add.s32 	%r1364, %r1354, 939524096;
$L__BB23_69:
	cvt.f64.f32 	%rd932, %r1364;
	bra.uni 	$L__BB23_690;
$L__BB23_483:
	selp.b32 	%r216, 15, 127, %p199;
	sub.s32 	%r620, 53, %r215;
	shr.u64 	%rd374, %rd123, %r620;
	mov.b64 	%rd375, -1;
	shl.b64 	%rd376, %rd375, %r620;
	not.b64 	%rd377, %rd376;
	and.b64 	%rd378, %rd928, %rd377;
	sub.s32 	%r621, 52, %r215;
	mov.b64 	%rd379, 1;
	shl.b64 	%rd380, %rd379, %r621;
	setp.gt.u64 	%p204, %rd378, %rd380;
	setp.eq.b64 	%p205, %rd378, %rd380;
	and.b64 	%rd381, %rd374, 1;
	setp.ne.b64 	%p206, %rd381, 0;
	and.pred 	%p207, %p205, %p206;
	or.pred 	%p208, %p204, %p207;
	selp.b64 	%rd382, 1, 0, %p208;
	add.s64 	%rd125, %rd374, %rd382;
	shl.b64 	%rd126, %rd379, %r215;
	setp.eq.b64 	%p209, %rd125, %rd126;
	add.s32 	%r622, %r214, -1022;
	selp.b32 	%r220, %r622, %r218, %p209;
	setp.le.s32 	%p210, %r220, %r216;
	@%p210 bra 	$L__BB23_485;
	or.b32 	%r1399, %r213, %r217;
	bra.uni 	$L__BB23_486;
$L__BB23_315:
	selp.b32 	%r139, 15, 127, %p38;
	sub.s32 	%r361, 53, %r138;
	shr.u64 	%rd206, %rd79, %r361;
	mov.b64 	%rd207, -1;
	shl.b64 	%rd208, %rd207, %r361;
	not.b64 	%rd209, %rd208;
	and.b64 	%rd210, %rd928, %rd209;
	sub.s32 	%r362, 52, %r138;
	mov.b64 	%rd211, 1;
	shl.b64 	%rd212, %rd211, %r362;
	setp.gt.u64 	%p43, %rd210, %rd212;
	setp.eq.b64 	%p44, %rd210, %rd212;
	and.b64 	%rd213, %rd206, 1;
	setp.ne.b64 	%p45, %rd213, 0;
	and.pred 	%p46, %p44, %p45;
	or.pred 	%p47, %p43, %p46;
	selp.b64 	%rd214, 1, 0, %p47;
	add.s64 	%rd81, %rd206, %rd214;
	shl.b64 	%rd82, %rd211, %r138;
	setp.eq.b64 	%p48, %rd81, %rd82;
	add.s32 	%r363, %r137, -1022;
	selp.b32 	%r143, %r363, %r141, %p48;
	setp.le.s32 	%p49, %r143, %r139;
	@%p49 bra 	$L__BB23_317;
	or.b32 	%r1385, %r136, %r140;
	bra.uni 	$L__BB23_318;
$L__BB23_292:
	selp.b32 	%r327, 1, 0, %p24;
	shr.u64 	%rd189, %rd73, %r327;
	add.s32 	%r328, %r132, %r128;
	add.s32 	%r329, %r127, -1;
	shl.b32 	%r330, %r328, %r329;
	shl.b64 	%rd190, %rd181, %r329;
	not.b64 	%rd191, %rd190;
	and.b64 	%rd192, %rd189, %rd191;
	cvt.u32.u64 	%r331, %rd192;
	or.b32 	%r332, %r330, %r331;
	or.b32 	%r1383, %r332, %r125;
$L__BB23_293:
	cvt.u16.u32 	%rs12, %r1383;
	bra.uni 	$L__BB23_294;
$L__BB23_152:
	selp.b32 	%r997, 1, 0, %p449;
	shr.u64 	%rd644, %rd37, %r997;
	add.s32 	%r998, %r66, %r62;
	add.s32 	%r999, %r61, -1;
	shl.b32 	%r1000, %r998, %r999;
	shl.b64 	%rd645, %rd636, %r999;
	not.b64 	%rd646, %rd645;
	and.b64 	%rd647, %rd644, %rd646;
	cvt.u32.u64 	%r1001, %rd647;
	or.b32 	%r1002, %r1000, %r1001;
	or.b32 	%r1371, %r1002, %r59;
$L__BB23_153:
	cvt.u16.u32 	%rs6, %r1371;
	bra.uni 	$L__BB23_154;
$L__BB23_128:
	selp.b32 	%r960, 1, 0, %p425;
	shr.u64 	%rd605, %rd31, %r960;
	add.s32 	%r961, %r54, %r50;
	add.s32 	%r962, %r49, -1;
	shl.b32 	%r963, %r961, %r962;
	shl.b64 	%rd606, %rd597, %r962;
	not.b64 	%rd607, %rd606;
	and.b64 	%rd608, %rd605, %rd607;
	cvt.u32.u64 	%r964, %rd608;
	or.b32 	%r965, %r963, %r964;
	or.b32 	%r1369, %r965, %r47;
$L__BB23_129:
	cvt.u16.u32 	%rs5, %r1369;
	bra.uni 	$L__BB23_130;
$L__BB23_286:
	neg.s32 	%r335, %r131;
	shl.b64 	%rd905, %rd71, %r335;
$L__BB23_289:
	or.b64 	%rd202, %rd905, %rd72;
	cvt.u16.u64 	%rs12, %rd202;
$L__BB23_294:
	setp.ne.b32 	%p33, %r1360, 13;
	cvt.u32.u16 	%r133, %rs12;
	@%p33 bra 	$L__BB23_296;
	shl.b32 	%r1384, %r133, 16;
	bra.uni 	$L__BB23_302;
$L__BB23_296:
	cvt.s32.s16 	%r336, %rs12;
	and.b32 	%r1384, %r336, -2147483648;
	bfe.u32 	%r134, %r133, 10, 5;
	setp.eq.b32 	%p34, %r134, 31;
	@%p34 bra 	$L__BB23_300;
	and.b32 	%r135, %r133, 1023;
	setp.ne.b32 	%p35, %r134, 0;
	@%p35 bra 	$L__BB23_301;
	setp.eq.b32 	%p36, %r135, 0;
	@%p36 bra 	$L__BB23_302;
	clz.b32 	%r339, %r135;
	xor.b32 	%r340, %r339, 31;
	sub.s32 	%r341, 9, %r340;
	shl.b32 	%r342, %r133, %r341;
	shl.b32 	%r343, %r340, 23;
	shl.b32 	%r344, %r342, 14;
	and.b32 	%r345, %r344, 8372224;
	add.s32 	%r346, %r343, %r1384;
	add.s32 	%r347, %r346, %r345;
	add.s32 	%r1384, %r347, 864026624;
	bra.uni 	$L__BB23_302;
$L__BB23_300:
	shl.b32 	%r337, %r133, 13;
	or.b32 	%r338, %r1384, %r337;
	or.b32 	%r1384, %r338, 2139095040;
	bra.uni 	$L__BB23_302;
$L__BB23_301:
	shl.b32 	%r348, %r134, 23;
	shl.b32 	%r349, %r135, 13;
	or.b32 	%r350, %r348, %r349;
	add.s32 	%r351, %r350, %r1384;
	add.s32 	%r1384, %r351, 939524096;
$L__BB23_302:
	cvt.f64.f32 	%rd933, %r1384;
	bra.uni 	$L__BB23_690;
$L__BB23_146:
	neg.s32 	%r1005, %r65;
	shl.b64 	%rd895, %rd35, %r1005;
$L__BB23_149:
	or.b64 	%rd657, %rd895, %rd36;
	cvt.u16.u64 	%rs6, %rd657;
$L__BB23_154:
	setp.ne.b32 	%p458, %r1360, 13;
	cvt.u32.u16 	%r67, %rs6;
	@%p458 bra 	$L__BB23_156;
	shl.b32 	%r1372, %r67, 16;
	bra.uni 	$L__BB23_162;
$L__BB23_156:
	cvt.s32.s16 	%r1006, %rs6;
	and.b32 	%r1372, %r1006, -2147483648;
	bfe.u32 	%r68, %r67, 10, 5;
	setp.eq.b32 	%p459, %r68, 31;
	@%p459 bra 	$L__BB23_160;
	and.b32 	%r69, %r67, 1023;
	setp.ne.b32 	%p460, %r68, 0;
	@%p460 bra 	$L__BB23_161;
	setp.eq.b32 	%p461, %r69, 0;
	@%p461 bra 	$L__BB23_162;
	clz.b32 	%r1009, %r69;
	xor.b32 	%r1010, %r1009, 31;
	sub.s32 	%r1011, 9, %r1010;
	shl.b32 	%r1012, %r67, %r1011;
	shl.b32 	%r1013, %r1010, 23;
	shl.b32 	%r1014, %r1012, 14;
	and.b32 	%r1015, %r1014, 8372224;
	add.s32 	%r1016, %r1013, %r1372;
	add.s32 	%r1017, %r1016, %r1015;
	add.s32 	%r1372, %r1017, 864026624;
	bra.uni 	$L__BB23_162;
$L__BB23_160:
	shl.b32 	%r1007, %r67, 13;
	or.b32 	%r1008, %r1372, %r1007;
	or.b32 	%r1372, %r1008, 2139095040;
	bra.uni 	$L__BB23_162;
$L__BB23_161:
	shl.b32 	%r1018, %r68, 23;
	shl.b32 	%r1019, %r69, 13;
	or.b32 	%r1020, %r1018, %r1019;
	add.s32 	%r1021, %r1020, %r1372;
	add.s32 	%r1372, %r1021, 939524096;
$L__BB23_162:
	cvt.f64.f32 	%rd896, %r1372;
$L__BB23_163:
	cvta.to.local.u64 	%rd658, %rd626;
	ld.local.b64 	%rd898, [%rd658];
	@%p438 bra 	$L__BB23_187;
	shr.u64 	%rd40, %rd898, 48;
	cvt.u32.u64 	%r1022, %rd40;
	and.b32 	%r70, %r1022, 32768;
	shr.u64 	%rd659, %rd898, 52;
	cvt.u32.u64 	%r1023, %rd659;
	and.b32 	%r71, %r1023, 2047;
	setp.eq.b32 	%p463, %r71, 0;
	@%p463 bra 	$L__BB23_167;
	and.b64 	%rd39, %rd898, 4503599627370495;
	setp.eq.b32 	%p462, %r1360, 12;
	selp.b32 	%r72, 11, 8, %p462;
	selp.b32 	%r74, 31744, 32640, %p462;
	setp.ne.b32 	%p464, %r71, 2047;
	@%p464 bra 	$L__BB23_168;
	setp.eq.b64 	%p465, %rd39, 0;
	add.s32 	%r1024, %r72, -2;
	mov.b32 	%r1025, 1;
	shl.b32 	%r1026, %r1025, %r1024;
	selp.b32 	%r1027, 0, %r1026, %p465;
	or.b32 	%r1028, %r1027, %r74;
	or.b32 	%r1029, %r1028, %r70;
	cvt.u16.u32 	%rs7, %r1029;
	bra.uni 	$L__BB23_178;
$L__BB23_167:
	cvt.u16.u32 	%rs7, %r70;
	bra.uni 	$L__BB23_178;
$L__BB23_168:
	selp.b32 	%r1030, -14, -126, %p462;
	add.s32 	%r75, %r71, -1023;
	or.b64 	%rd41, %rd39, 4503599627370496;
	setp.ge.s32 	%p466, %r75, %r1030;
	@%p466 bra 	$L__BB23_174;
	and.b64 	%rd42, %rd40, 32768;
	selp.b32 	%r1040, 28, -81, %p462;
	sub.s32 	%r76, %r1040, %r75;
	setp.gt.s32 	%p474, %r76, 0;
	@%p474 bra 	$L__BB23_171;
	bra.uni 	$L__BB23_170;
$L__BB23_171:
	setp.gt.u32 	%p475, %r76, 63;
	mov.b64 	%rd897, 0;
	@%p475 bra 	$L__BB23_173;
	shr.u64 	%rd673, %rd41, %r76;
	mov.b64 	%rd674, -1;
	shl.b64 	%rd675, %rd674, %r76;
	not.b64 	%rd676, %rd675;
	and.b64 	%rd677, %rd41, %rd676;
	add.s32 	%r1041, %r76, -1;
	mov.b64 	%rd678, 1;
	shl.b64 	%rd679, %rd678, %r1041;
	setp.gt.u64 	%p476, %rd677, %rd679;
	setp.eq.b64 	%p477, %rd677, %rd679;
	and.b64 	%rd680, %rd673, 1;
	setp.ne.b64 	%p478, %rd680, 0;
	and.pred 	%p479, %p477, %p478;
	or.pred 	%p480, %p476, %p479;
	selp.b64 	%rd681, 1, 0, %p480;
	add.s64 	%rd897, %rd673, %rd681;
	bra.uni 	$L__BB23_173;
$L__BB23_174:
	selp.b32 	%r73, 15, 127, %p462;
	sub.s32 	%r1031, 53, %r72;
	shr.u64 	%rd660, %rd41, %r1031;
	mov.b64 	%rd661, -1;
	shl.b64 	%rd662, %rd661, %r1031;
	not.b64 	%rd663, %rd662;
	and.b64 	%rd664, %rd898, %rd663;
	sub.s32 	%r1032, 52, %r72;
	mov.b64 	%rd665, 1;
	shl.b64 	%rd666, %rd665, %r1032;
	setp.gt.u64 	%p467, %rd664, %rd666;
	setp.eq.b64 	%p468, %rd664, %rd666;
	and.b64 	%rd667, %rd660, 1;
	setp.ne.b64 	%p469, %rd667, 0;
	and.pred 	%p470, %p468, %p469;
	or.pred 	%p471, %p467, %p470;
	selp.b64 	%rd668, 1, 0, %p471;
	add.s64 	%rd43, %rd660, %rd668;
	shl.b64 	%rd44, %rd665, %r72;
	setp.eq.b64 	%p472, %rd43, %rd44;
	add.s32 	%r1033, %r71, -1022;
	selp.b32 	%r77, %r1033, %r75, %p472;
	setp.le.s32 	%p473, %r77, %r73;
	@%p473 bra 	$L__BB23_176;
	or.b32 	%r1373, %r70, %r74;
)QPTX";
        result += R"QPTX(
	bra.uni 	$L__BB23_177;
$L__BB23_176:
	selp.b32 	%r1034, 1, 0, %p472;
	shr.u64 	%rd669, %rd43, %r1034;
	add.s32 	%r1035, %r77, %r73;
	add.s32 	%r1036, %r72, -1;
	shl.b32 	%r1037, %r1035, %r1036;
	shl.b64 	%rd670, %rd661, %r1036;
	not.b64 	%rd671, %rd670;
	and.b64 	%rd672, %rd669, %rd671;
	cvt.u32.u64 	%r1038, %rd672;
	or.b32 	%r1039, %r1037, %r1038;
	or.b32 	%r1373, %r1039, %r70;
$L__BB23_177:
	cvt.u16.u32 	%rs7, %r1373;
	bra.uni 	$L__BB23_178;
$L__BB23_122:
	neg.s32 	%r968, %r53;
	shl.b64 	%rd894, %rd29, %r968;
$L__BB23_125:
	or.b64 	%rd618, %rd894, %rd30;
	cvt.u16.u64 	%rs5, %rd618;
$L__BB23_130:
	setp.ne.b32 	%p434, %r1360, 13;
	cvt.u32.u16 	%r55, %rs5;
	@%p434 bra 	$L__BB23_132;
	shl.b32 	%r1370, %r55, 16;
	bra.uni 	$L__BB23_138;
$L__BB23_132:
	cvt.s32.s16 	%r969, %rs5;
	and.b32 	%r1370, %r969, -2147483648;
	bfe.u32 	%r56, %r55, 10, 5;
	setp.eq.b32 	%p435, %r56, 31;
	@%p435 bra 	$L__BB23_136;
	and.b32 	%r57, %r55, 1023;
	setp.ne.b32 	%p436, %r56, 0;
	@%p436 bra 	$L__BB23_137;
	setp.eq.b32 	%p437, %r57, 0;
	@%p437 bra 	$L__BB23_138;
	clz.b32 	%r972, %r57;
	xor.b32 	%r973, %r972, 31;
	sub.s32 	%r974, 9, %r973;
	shl.b32 	%r975, %r55, %r974;
	shl.b32 	%r976, %r973, 23;
	shl.b32 	%r977, %r975, 14;
	and.b32 	%r978, %r977, 8372224;
	add.s32 	%r979, %r976, %r1370;
	add.s32 	%r980, %r979, %r978;
	add.s32 	%r1370, %r980, 864026624;
	bra.uni 	$L__BB23_138;
$L__BB23_136:
	shl.b32 	%r970, %r55, 13;
	or.b32 	%r971, %r1370, %r970;
	or.b32 	%r1370, %r971, 2139095040;
	bra.uni 	$L__BB23_138;
$L__BB23_137:
	shl.b32 	%r981, %r56, 23;
	shl.b32 	%r982, %r57, 13;
	or.b32 	%r983, %r981, %r982;
	add.s32 	%r984, %r983, %r1370;
	add.s32 	%r1370, %r984, 939524096;
$L__BB23_138:
	cvt.f64.f32 	%rd933, %r1370;
	bra.uni 	$L__BB23_690;
$L__BB23_170:
	neg.s32 	%r1042, %r76;
	shl.b64 	%rd897, %rd41, %r1042;
$L__BB23_173:
	or.b64 	%rd682, %rd897, %rd42;
	cvt.u16.u64 	%rs7, %rd682;
$L__BB23_178:
	setp.ne.b32 	%p481, %r1360, 13;
	cvt.u32.u16 	%r78, %rs7;
	@%p481 bra 	$L__BB23_180;
	shl.b32 	%r1374, %r78, 16;
	bra.uni 	$L__BB23_186;
$L__BB23_180:
	cvt.s32.s16 	%r1043, %rs7;
	and.b32 	%r1374, %r1043, -2147483648;
	bfe.u32 	%r79, %r78, 10, 5;
	setp.eq.b32 	%p482, %r79, 31;
	@%p482 bra 	$L__BB23_184;
	and.b32 	%r80, %r78, 1023;
	setp.ne.b32 	%p483, %r79, 0;
	@%p483 bra 	$L__BB23_185;
	setp.eq.b32 	%p484, %r80, 0;
	@%p484 bra 	$L__BB23_186;
	clz.b32 	%r1046, %r80;
	xor.b32 	%r1047, %r1046, 31;
	sub.s32 	%r1048, 9, %r1047;
	shl.b32 	%r1049, %r78, %r1048;
	shl.b32 	%r1050, %r1047, 23;
	shl.b32 	%r1051, %r1049, 14;
	and.b32 	%r1052, %r1051, 8372224;
	add.s32 	%r1053, %r1050, %r1374;
	add.s32 	%r1054, %r1053, %r1052;
	add.s32 	%r1374, %r1054, 864026624;
	bra.uni 	$L__BB23_186;
$L__BB23_184:
	shl.b32 	%r1044, %r78, 13;
	or.b32 	%r1045, %r1374, %r1044;
	or.b32 	%r1374, %r1045, 2139095040;
	bra.uni 	$L__BB23_186;
$L__BB23_185:
	shl.b32 	%r1055, %r79, 23;
	shl.b32 	%r1056, %r80, 13;
	or.b32 	%r1057, %r1055, %r1056;
	add.s32 	%r1058, %r1057, %r1374;
	add.s32 	%r1374, %r1058, 939524096;
$L__BB23_186:
	cvt.f64.f32 	%rd898, %r1374;
$L__BB23_187:
	sub.rn.f64 	%rd933, %rd896, %rd898;
	@%p438 bra 	$L__BB23_211;
	shr.u64 	%rd46, %rd933, 48;
	cvt.u32.u64 	%r1059, %rd46;
	and.b32 	%r81, %r1059, 32768;
	shr.u64 	%rd683, %rd933, 52;
	cvt.u32.u64 	%r1060, %rd683;
	and.b32 	%r82, %r1060, 2047;
	setp.eq.b32 	%p486, %r82, 0;
	@%p486 bra 	$L__BB23_191;
	and.b64 	%rd45, %rd933, 4503599627370495;
	setp.eq.b32 	%p485, %r1360, 12;
	selp.b32 	%r83, 11, 8, %p485;
	selp.b32 	%r85, 31744, 32640, %p485;
	setp.ne.b32 	%p487, %r82, 2047;
	@%p487 bra 	$L__BB23_192;
	setp.eq.b64 	%p488, %rd45, 0;
	add.s32 	%r1061, %r83, -2;
	mov.b32 	%r1062, 1;
	shl.b32 	%r1063, %r1062, %r1061;
	selp.b32 	%r1064, 0, %r1063, %p488;
	or.b32 	%r1065, %r1064, %r85;
	or.b32 	%r1066, %r1065, %r81;
	cvt.u16.u32 	%rs8, %r1066;
	bra.uni 	$L__BB23_202;
$L__BB23_191:
	cvt.u16.u32 	%rs8, %r81;
	bra.uni 	$L__BB23_202;
$L__BB23_192:
	selp.b32 	%r1067, -14, -126, %p485;
	add.s32 	%r86, %r82, -1023;
	or.b64 	%rd47, %rd45, 4503599627370496;
	setp.ge.s32 	%p489, %r86, %r1067;
	@%p489 bra 	$L__BB23_198;
	and.b64 	%rd48, %rd46, 32768;
	selp.b32 	%r1077, 28, -81, %p485;
	sub.s32 	%r87, %r1077, %r86;
	setp.gt.s32 	%p497, %r87, 0;
	@%p497 bra 	$L__BB23_195;
	bra.uni 	$L__BB23_194;
$L__BB23_195:
	setp.gt.u32 	%p498, %r87, 63;
	mov.b64 	%rd899, 0;
	@%p498 bra 	$L__BB23_197;
	shr.u64 	%rd697, %rd47, %r87;
	mov.b64 	%rd698, -1;
	shl.b64 	%rd699, %rd698, %r87;
	not.b64 	%rd700, %rd699;
	and.b64 	%rd701, %rd47, %rd700;
	add.s32 	%r1078, %r87, -1;
	mov.b64 	%rd702, 1;
	shl.b64 	%rd703, %rd702, %r1078;
	setp.gt.u64 	%p499, %rd701, %rd703;
	setp.eq.b64 	%p500, %rd701, %rd703;
	and.b64 	%rd704, %rd697, 1;
	setp.ne.b64 	%p501, %rd704, 0;
	and.pred 	%p502, %p500, %p501;
	or.pred 	%p503, %p499, %p502;
	selp.b64 	%rd705, 1, 0, %p503;
	add.s64 	%rd899, %rd697, %rd705;
	bra.uni 	$L__BB23_197;
$L__BB23_198:
	selp.b32 	%r84, 15, 127, %p485;
	sub.s32 	%r1068, 53, %r83;
	shr.u64 	%rd684, %rd47, %r1068;
	mov.b64 	%rd685, -1;
	shl.b64 	%rd686, %rd685, %r1068;
	not.b64 	%rd687, %rd686;
	and.b64 	%rd688, %rd933, %rd687;
	sub.s32 	%r1069, 52, %r83;
	mov.b64 	%rd689, 1;
	shl.b64 	%rd690, %rd689, %r1069;
	setp.gt.u64 	%p490, %rd688, %rd690;
	setp.eq.b64 	%p491, %rd688, %rd690;
	and.b64 	%rd691, %rd684, 1;
	setp.ne.b64 	%p492, %rd691, 0;
	and.pred 	%p493, %p491, %p492;
	or.pred 	%p494, %p490, %p493;
	selp.b64 	%rd692, 1, 0, %p494;
	add.s64 	%rd49, %rd684, %rd692;
	shl.b64 	%rd50, %rd689, %r83;
	setp.eq.b64 	%p495, %rd49, %rd50;
	add.s32 	%r1070, %r82, -1022;
	selp.b32 	%r88, %r1070, %r86, %p495;
	setp.le.s32 	%p496, %r88, %r84;
	@%p496 bra 	$L__BB23_200;
	or.b32 	%r1375, %r81, %r85;
	bra.uni 	$L__BB23_201;
$L__BB23_200:
	selp.b32 	%r1071, 1, 0, %p495;
	shr.u64 	%rd693, %rd49, %r1071;
	add.s32 	%r1072, %r88, %r84;
	add.s32 	%r1073, %r83, -1;
	shl.b32 	%r1074, %r1072, %r1073;
	shl.b64 	%rd694, %rd685, %r1073;
	not.b64 	%rd695, %rd694;
	and.b64 	%rd696, %rd693, %rd695;
	cvt.u32.u64 	%r1075, %rd696;
	or.b32 	%r1076, %r1074, %r1075;
	or.b32 	%r1375, %r1076, %r81;
$L__BB23_201:
	cvt.u16.u32 	%rs8, %r1375;
	bra.uni 	$L__BB23_202;
$L__BB23_194:
	neg.s32 	%r1079, %r87;
	shl.b64 	%rd899, %rd47, %r1079;
$L__BB23_197:
	or.b64 	%rd706, %rd899, %rd48;
	cvt.u16.u64 	%rs8, %rd706;
$L__BB23_202:
	setp.ne.b32 	%p504, %r1360, 13;
	cvt.u32.u16 	%r89, %rs8;
	@%p504 bra 	$L__BB23_204;
	shl.b32 	%r1376, %r89, 16;
	bra.uni 	$L__BB23_210;
$L__BB23_204:
	cvt.s32.s16 	%r1080, %rs8;
	and.b32 	%r1376, %r1080, -2147483648;
	bfe.u32 	%r90, %r89, 10, 5;
	setp.eq.b32 	%p505, %r90, 31;
	@%p505 bra 	$L__BB23_208;
	and.b32 	%r91, %r89, 1023;
	setp.ne.b32 	%p506, %r90, 0;
	@%p506 bra 	$L__BB23_209;
	setp.eq.b32 	%p507, %r91, 0;
	@%p507 bra 	$L__BB23_210;
	clz.b32 	%r1083, %r91;
	xor.b32 	%r1084, %r1083, 31;
	sub.s32 	%r1085, 9, %r1084;
	shl.b32 	%r1086, %r89, %r1085;
	shl.b32 	%r1087, %r1084, 23;
	shl.b32 	%r1088, %r1086, 14;
	and.b32 	%r1089, %r1088, 8372224;
	add.s32 	%r1090, %r1087, %r1376;
	add.s32 	%r1091, %r1090, %r1089;
	add.s32 	%r1376, %r1091, 864026624;
	bra.uni 	$L__BB23_210;
$L__BB23_208:
	shl.b32 	%r1081, %r89, 13;
	or.b32 	%r1082, %r1376, %r1081;
	or.b32 	%r1376, %r1082, 2139095040;
	bra.uni 	$L__BB23_210;
$L__BB23_209:
	shl.b32 	%r1092, %r90, 23;
	shl.b32 	%r1093, %r91, 13;
	or.b32 	%r1094, %r1092, %r1093;
	add.s32 	%r1095, %r1094, %r1376;
	add.s32 	%r1376, %r1095, 939524096;
$L__BB23_210:
	cvt.f64.f32 	%rd933, %r1376;
$L__BB23_211:
	cvta.to.local.u64 	%rd707, %rd629;
	ld.local.b64 	%rd901, [%rd707];
	@%p438 bra 	$L__BB23_235;
	shr.u64 	%rd52, %rd901, 48;
	cvt.u32.u64 	%r1096, %rd52;
	and.b32 	%r92, %r1096, 32768;
	shr.u64 	%rd708, %rd901, 52;
	cvt.u32.u64 	%r1097, %rd708;
	and.b32 	%r93, %r1097, 2047;
	setp.eq.b32 	%p509, %r93, 0;
	@%p509 bra 	$L__BB23_215;
	and.b64 	%rd51, %rd901, 4503599627370495;
	setp.eq.b32 	%p508, %r1360, 12;
	selp.b32 	%r94, 11, 8, %p508;
	selp.b32 	%r96, 31744, 32640, %p508;
	setp.ne.b32 	%p510, %r93, 2047;
	@%p510 bra 	$L__BB23_216;
	setp.eq.b64 	%p511, %rd51, 0;
	add.s32 	%r1098, %r94, -2;
	mov.b32 	%r1099, 1;
	shl.b32 	%r1100, %r1099, %r1098;
	selp.b32 	%r1101, 0, %r1100, %p511;
	or.b32 	%r1102, %r1101, %r96;
	or.b32 	%r1103, %r1102, %r92;
	cvt.u16.u32 	%rs9, %r1103;
	bra.uni 	$L__BB23_226;
$L__BB23_215:
	cvt.u16.u32 	%rs9, %r92;
	bra.uni 	$L__BB23_226;
$L__BB23_216:
	selp.b32 	%r1104, -14, -126, %p508;
	add.s32 	%r97, %r93, -1023;
	or.b64 	%rd53, %rd51, 4503599627370496;
	setp.ge.s32 	%p512, %r97, %r1104;
	@%p512 bra 	$L__BB23_222;
	and.b64 	%rd54, %rd52, 32768;
	selp.b32 	%r1114, 28, -81, %p508;
	sub.s32 	%r98, %r1114, %r97;
	setp.gt.s32 	%p520, %r98, 0;
	@%p520 bra 	$L__BB23_219;
	bra.uni 	$L__BB23_218;
$L__BB23_219:
	setp.gt.u32 	%p521, %r98, 63;
	mov.b64 	%rd900, 0;
	@%p521 bra 	$L__BB23_221;
	shr.u64 	%rd722, %rd53, %r98;
	mov.b64 	%rd723, -1;
	shl.b64 	%rd724, %rd723, %r98;
	not.b64 	%rd725, %rd724;
	and.b64 	%rd726, %rd53, %rd725;
	add.s32 	%r1115, %r98, -1;
	mov.b64 	%rd727, 1;
	shl.b64 	%rd728, %rd727, %r1115;
	setp.gt.u64 	%p522, %rd726, %rd728;
	setp.eq.b64 	%p523, %rd726, %rd728;
	and.b64 	%rd729, %rd722, 1;
	setp.ne.b64 	%p524, %rd729, 0;
	and.pred 	%p525, %p523, %p524;
	or.pred 	%p526, %p522, %p525;
	selp.b64 	%rd730, 1, 0, %p526;
	add.s64 	%rd900, %rd722, %rd730;
	bra.uni 	$L__BB23_221;
$L__BB23_222:
	selp.b32 	%r95, 15, 127, %p508;
	sub.s32 	%r1105, 53, %r94;
	shr.u64 	%rd709, %rd53, %r1105;
	mov.b64 	%rd710, -1;
	shl.b64 	%rd711, %rd710, %r1105;
	not.b64 	%rd712, %rd711;
	and.b64 	%rd713, %rd901, %rd712;
	sub.s32 	%r1106, 52, %r94;
	mov.b64 	%rd714, 1;
	shl.b64 	%rd715, %rd714, %r1106;
	setp.gt.u64 	%p513, %rd713, %rd715;
	setp.eq.b64 	%p514, %rd713, %rd715;
	and.b64 	%rd716, %rd709, 1;
	setp.ne.b64 	%p515, %rd716, 0;
	and.pred 	%p516, %p514, %p515;
	or.pred 	%p517, %p513, %p516;
	selp.b64 	%rd717, 1, 0, %p517;
	add.s64 	%rd55, %rd709, %rd717;
	shl.b64 	%rd56, %rd714, %r94;
	setp.eq.b64 	%p518, %rd55, %rd56;
	add.s32 	%r1107, %r93, -1022;
	selp.b32 	%r99, %r1107, %r97, %p518;
	setp.le.s32 	%p519, %r99, %r95;
	@%p519 bra 	$L__BB23_224;
	or.b32 	%r1377, %r92, %r96;
	bra.uni 	$L__BB23_225;
$L__BB23_224:
	selp.b32 	%r1108, 1, 0, %p518;
	shr.u64 	%rd718, %rd55, %r1108;
	add.s32 	%r1109, %r99, %r95;
	add.s32 	%r1110, %r94, -1;
	shl.b32 	%r1111, %r1109, %r1110;
	shl.b64 	%rd719, %rd710, %r1110;
	not.b64 	%rd720, %rd719;
	and.b64 	%rd721, %rd718, %rd720;
	cvt.u32.u64 	%r1112, %rd721;
	or.b32 	%r1113, %r1111, %r1112;
	or.b32 	%r1377, %r1113, %r92;
$L__BB23_225:
	cvt.u16.u32 	%rs9, %r1377;
	bra.uni 	$L__BB23_226;
$L__BB23_218:
	neg.s32 	%r1116, %r98;
	shl.b64 	%rd900, %rd53, %r1116;
$L__BB23_221:
	or.b64 	%rd731, %rd900, %rd54;
	cvt.u16.u64 	%rs9, %rd731;
$L__BB23_226:
	setp.ne.b32 	%p527, %r1360, 13;
	cvt.u32.u16 	%r100, %rs9;
	@%p527 bra 	$L__BB23_228;
	shl.b32 	%r1378, %r100, 16;
	bra.uni 	$L__BB23_234;
$L__BB23_228:
	cvt.s32.s16 	%r1117, %rs9;
	and.b32 	%r1378, %r1117, -2147483648;
	bfe.u32 	%r101, %r100, 10, 5;
	setp.eq.b32 	%p528, %r101, 31;
	@%p528 bra 	$L__BB23_232;
	and.b32 	%r102, %r100, 1023;
	setp.ne.b32 	%p529, %r101, 0;
	@%p529 bra 	$L__BB23_233;
	setp.eq.b32 	%p530, %r102, 0;
	@%p530 bra 	$L__BB23_234;
	clz.b32 	%r1120, %r102;
	xor.b32 	%r1121, %r1120, 31;
	sub.s32 	%r1122, 9, %r1121;
	shl.b32 	%r1123, %r100, %r1122;
	shl.b32 	%r1124, %r1121, 23;
	shl.b32 	%r1125, %r1123, 14;
	and.b32 	%r1126, %r1125, 8372224;
	add.s32 	%r1127, %r1124, %r1378;
	add.s32 	%r1128, %r1127, %r1126;
	add.s32 	%r1378, %r1128, 864026624;
	bra.uni 	$L__BB23_234;
$L__BB23_232:
	shl.b32 	%r1118, %r100, 13;
	or.b32 	%r1119, %r1378, %r1118;
	or.b32 	%r1378, %r1119, 2139095040;
	bra.uni 	$L__BB23_234;
$L__BB23_233:
	shl.b32 	%r1129, %r101, 23;
	shl.b32 	%r1130, %r102, 13;
	or.b32 	%r1131, %r1129, %r1130;
	add.s32 	%r1132, %r1131, %r1378;
	add.s32 	%r1378, %r1132, 939524096;
$L__BB23_234:
	cvt.f64.f32 	%rd901, %r1378;
$L__BB23_235:
	cvta.to.local.u64 	%rd732, %rd632;
	ld.local.b64 	%rd903, [%rd732];
	@%p438 bra 	$L__BB23_259;
	shr.u64 	%rd58, %rd903, 48;
	cvt.u32.u64 	%r1133, %rd58;
	and.b32 	%r103, %r1133, 32768;
	shr.u64 	%rd733, %rd903, 52;
	cvt.u32.u64 	%r1134, %rd733;
	and.b32 	%r104, %r1134, 2047;
	setp.eq.b32 	%p532, %r104, 0;
	@%p532 bra 	$L__BB23_239;
	and.b64 	%rd57, %rd903, 4503599627370495;
	setp.eq.b32 	%p531, %r1360, 12;
	selp.b32 	%r105, 11, 8, %p531;
	selp.b32 	%r107, 31744, 32640, %p531;
	setp.ne.b32 	%p533, %r104, 2047;
	@%p533 bra 	$L__BB23_240;
	setp.eq.b64 	%p534, %rd57, 0;
	add.s32 	%r1135, %r105, -2;
	mov.b32 	%r1136, 1;
	shl.b32 	%r1137, %r1136, %r1135;
	selp.b32 	%r1138, 0, %r1137, %p534;
	or.b32 	%r1139, %r1138, %r107;
	or.b32 	%r1140, %r1139, %r103;
	cvt.u16.u32 	%rs10, %r1140;
	bra.uni 	$L__BB23_250;
$L__BB23_239:
	cvt.u16.u32 	%rs10, %r103;
	bra.uni 	$L__BB23_250;
$L__BB23_240:
	selp.b32 	%r1141, -14, -126, %p531;
	add.s32 	%r108, %r104, -1023;
	or.b64 	%rd59, %rd57, 4503599627370496;
	setp.ge.s32 	%p535, %r108, %r1141;
	@%p535 bra 	$L__BB23_246;
	and.b64 	%rd60, %rd58, 32768;
	selp.b32 	%r1151, 28, -81, %p531;
	sub.s32 	%r109, %r1151, %r108;
	setp.gt.s32 	%p543, %r109, 0;
	@%p543 bra 	$L__BB23_243;
	bra.uni 	$L__BB23_242;
$L__BB23_243:
	setp.gt.u32 	%p544, %r109, 63;
	mov.b64 	%rd902, 0;
	@%p544 bra 	$L__BB23_245;
	shr.u64 	%rd747, %rd59, %r109;
	mov.b64 	%rd748, -1;
	shl.b64 	%rd749, %rd748, %r109;
	not.b64 	%rd750, %rd749;
	and.b64 	%rd751, %rd59, %rd750;
	add.s32 	%r1152, %r109, -1;
	mov.b64 	%rd752, 1;
	shl.b64 	%rd753, %rd752, %r1152;
	setp.gt.u64 	%p545, %rd751, %rd753;
	setp.eq.b64 	%p546, %rd751, %rd753;
	and.b64 	%rd754, %rd747, 1;
	setp.ne.b64 	%p547, %rd754, 0;
	and.pred 	%p548, %p546, %p547;
	or.pred 	%p549, %p545, %p548;
	selp.b64 	%rd755, 1, 0, %p549;
	add.s64 	%rd902, %rd747, %rd755;
	bra.uni 	$L__BB23_245;
$L__BB23_246:
	selp.b32 	%r106, 15, 127, %p531;
	sub.s32 	%r1142, 53, %r105;
	shr.u64 	%rd734, %rd59, %r1142;
	mov.b64 	%rd735, -1;
	shl.b64 	%rd736, %rd735, %r1142;
	not.b64 	%rd737, %rd736;
	and.b64 	%rd738, %rd903, %rd737;
	sub.s32 	%r1143, 52, %r105;
	mov.b64 	%rd739, 1;
	shl.b64 	%rd740, %rd739, %r1143;
	setp.gt.u64 	%p536, %rd738, %rd740;
	setp.eq.b64 	%p537, %rd738, %rd740;
	and.b64 	%rd741, %rd734, 1;
	setp.ne.b64 	%p538, %rd741, 0;
	and.pred 	%p539, %p537, %p538;
	or.pred 	%p540, %p536, %p539;
	selp.b64 	%rd742, 1, 0, %p540;
	add.s64 	%rd61, %rd734, %rd742;
	shl.b64 	%rd62, %rd739, %r105;
	setp.eq.b64 	%p541, %rd61, %rd62;
	add.s32 	%r1144, %r104, -1022;
	selp.b32 	%r110, %r1144, %r108, %p541;
	setp.le.s32 	%p542, %r110, %r106;
	@%p542 bra 	$L__BB23_248;
	or.b32 	%r1379, %r103, %r107;
	bra.uni 	$L__BB23_249;
$L__BB23_248:
	selp.b32 	%r1145, 1, 0, %p541;
	shr.u64 	%rd743, %rd61, %r1145;
	add.s32 	%r1146, %r110, %r106;
	add.s32 	%r1147, %r105, -1;
	shl.b32 	%r1148, %r1146, %r1147;
	shl.b64 	%rd744, %rd735, %r1147;
	not.b64 	%rd745, %rd744;
	and.b64 	%rd746, %rd743, %rd745;
	cvt.u32.u64 	%r1149, %rd746;
	or.b32 	%r1150, %r1148, %r1149;
	or.b32 	%r1379, %r1150, %r103;
$L__BB23_249:
	cvt.u16.u32 	%rs10, %r1379;
	bra.uni 	$L__BB23_250;
$L__BB23_242:
	neg.s32 	%r1153, %r109;
	shl.b64 	%rd902, %rd59, %r1153;
$L__BB23_245:
	or.b64 	%rd756, %rd902, %rd60;
	cvt.u16.u64 	%rs10, %rd756;
$L__BB23_250:
	setp.ne.b32 	%p550, %r1360, 13;
	cvt.u32.u16 	%r111, %rs10;
	@%p550 bra 	$L__BB23_252;
	shl.b32 	%r1380, %r111, 16;
	bra.uni 	$L__BB23_258;
$L__BB23_252:
	cvt.s32.s16 	%r1154, %rs10;
	and.b32 	%r1380, %r1154, -2147483648;
	bfe.u32 	%r112, %r111, 10, 5;
	setp.eq.b32 	%p551, %r112, 31;
	@%p551 bra 	$L__BB23_256;
	and.b32 	%r113, %r111, 1023;
	setp.ne.b32 	%p552, %r112, 0;
	@%p552 bra 	$L__BB23_257;
	setp.eq.b32 	%p553, %r113, 0;
	@%p553 bra 	$L__BB23_258;
	clz.b32 	%r1157, %r113;
	xor.b32 	%r1158, %r1157, 31;
	sub.s32 	%r1159, 9, %r1158;
	shl.b32 	%r1160, %r111, %r1159;
	shl.b32 	%r1161, %r1158, 23;
	shl.b32 	%r1162, %r1160, 14;
	and.b32 	%r1163, %r1162, 8372224;
	add.s32 	%r1164, %r1161, %r1380;
	add.s32 	%r1165, %r1164, %r1163;
	add.s32 	%r1380, %r1165, 864026624;
	bra.uni 	$L__BB23_258;
$L__BB23_256:
	shl.b32 	%r1155, %r111, 13;
	or.b32 	%r1156, %r1380, %r1155;
	or.b32 	%r1380, %r1156, 2139095040;
	bra.uni 	$L__BB23_258;
$L__BB23_257:
	shl.b32 	%r1166, %r112, 23;
	shl.b32 	%r1167, %r113, 13;
	or.b32 	%r1168, %r1166, %r1167;
	add.s32 	%r1169, %r1168, %r1380;
	add.s32 	%r1380, %r1169, 939524096;
$L__BB23_258:
	cvt.f64.f32 	%rd903, %r1380;
$L__BB23_259:
	add.rn.f64 	%rd932, %rd901, %rd903;
	@%p438 bra 	$L__BB23_690;
	shr.u64 	%rd64, %rd932, 48;
	cvt.u32.u64 	%r1170, %rd64;
	and.b32 	%r114, %r1170, 32768;
	shr.u64 	%rd757, %rd932, 52;
	cvt.u32.u64 	%r1171, %rd757;
	and.b32 	%r115, %r1171, 2047;
	setp.eq.b32 	%p555, %r115, 0;
	@%p555 bra 	$L__BB23_263;
	and.b64 	%rd63, %rd932, 4503599627370495;
	setp.eq.b32 	%p554, %r1360, 12;
	selp.b32 	%r116, 11, 8, %p554;
	selp.b32 	%r118, 31744, 32640, %p554;
	setp.ne.b32 	%p556, %r115, 2047;
	@%p556 bra 	$L__BB23_264;
	setp.eq.b64 	%p557, %rd63, 0;
	add.s32 	%r1172, %r116, -2;
	mov.b32 	%r1173, 1;
	shl.b32 	%r1174, %r1173, %r1172;
	selp.b32 	%r1175, 0, %r1174, %p557;
	or.b32 	%r1176, %r1175, %r118;
	or.b32 	%r1177, %r1176, %r114;
	cvt.u16.u32 	%rs11, %r1177;
	bra.uni 	$L__BB23_274;
$L__BB23_263:
	cvt.u16.u32 	%rs11, %r114;
	bra.uni 	$L__BB23_274;
$L__BB23_264:
	selp.b32 	%r1178, -14, -126, %p554;
	add.s32 	%r119, %r115, -1023;
	or.b64 	%rd65, %rd63, 4503599627370496;
	setp.ge.s32 	%p558, %r119, %r1178;
	@%p558 bra 	$L__BB23_270;
	and.b64 	%rd66, %rd64, 32768;
	selp.b32 	%r1188, 28, -81, %p554;
	sub.s32 	%r120, %r1188, %r119;
	setp.gt.s32 	%p566, %r120, 0;
	@%p566 bra 	$L__BB23_267;
	bra.uni 	$L__BB23_266;
$L__BB23_267:
	setp.gt.u32 	%p567, %r120, 63;
	mov.b64 	%rd904, 0;
	@%p567 bra 	$L__BB23_269;
	shr.u64 	%rd771, %rd65, %r120;
	mov.b64 	%rd772, -1;
	shl.b64 	%rd773, %rd772, %r120;
	not.b64 	%rd774, %rd773;
	and.b64 	%rd775, %rd65, %rd774;
	add.s32 	%r1189, %r120, -1;
	mov.b64 	%rd776, 1;
	shl.b64 	%rd777, %rd776, %r1189;
	setp.gt.u64 	%p568, %rd775, %rd777;
	setp.eq.b64 	%p569, %rd775, %rd777;
	and.b64 	%rd778, %rd771, 1;
	setp.ne.b64 	%p570, %rd778, 0;
	and.pred 	%p571, %p569, %p570;
	or.pred 	%p572, %p568, %p571;
	selp.b64 	%rd779, 1, 0, %p572;
	add.s64 	%rd904, %rd771, %rd779;
	bra.uni 	$L__BB23_269;
$L__BB23_270:
	selp.b32 	%r117, 15, 127, %p554;
	sub.s32 	%r1179, 53, %r116;
	shr.u64 	%rd758, %rd65, %r1179;
	mov.b64 	%rd759, -1;
	shl.b64 	%rd760, %rd759, %r1179;
	not.b64 	%rd761, %rd760;
	and.b64 	%rd762, %rd932, %rd761;
	sub.s32 	%r1180, 52, %r116;
	mov.b64 	%rd763, 1;
	shl.b64 	%rd764, %rd763, %r1180;
	setp.gt.u64 	%p559, %rd762, %rd764;
	setp.eq.b64 	%p560, %rd762, %rd764;
	and.b64 	%rd765, %rd758, 1;
	setp.ne.b64 	%p561, %rd765, 0;
	and.pred 	%p562, %p560, %p561;
	or.pred 	%p563, %p559, %p562;
	selp.b64 	%rd766, 1, 0, %p563;
	add.s64 	%rd67, %rd758, %rd766;
	shl.b64 	%rd68, %rd763, %r116;
	setp.eq.b64 	%p564, %rd67, %rd68;
	add.s32 	%r1181, %r115, -1022;
	selp.b32 	%r121, %r1181, %r119, %p564;
	setp.le.s32 	%p565, %r121, %r117;
	@%p565 bra 	$L__BB23_272;
	or.b32 	%r1381, %r114, %r118;
	bra.uni 	$L__BB23_273;
$L__BB23_272:
	selp.b32 	%r1182, 1, 0, %p564;
	shr.u64 	%rd767, %rd67, %r1182;
	add.s32 	%r1183, %r121, %r117;
	add.s32 	%r1184, %r116, -1;
	shl.b32 	%r1185, %r1183, %r1184;
	shl.b64 	%rd768, %rd759, %r1184;
	not.b64 	%rd769, %rd768;
	and.b64 	%rd770, %rd767, %rd769;
	cvt.u32.u64 	%r1186, %rd770;
	or.b32 	%r1187, %r1185, %r1186;
	or.b32 	%r1381, %r1187, %r114;
$L__BB23_273:
	cvt.u16.u32 	%rs11, %r1381;
	bra.uni 	$L__BB23_274;
$L__BB23_266:
	neg.s32 	%r1190, %r120;
	shl.b64 	%rd904, %rd65, %r1190;
$L__BB23_269:
	or.b64 	%rd780, %rd904, %rd66;
	cvt.u16.u64 	%rs11, %rd780;
$L__BB23_274:
	setp.ne.b32 	%p573, %r1360, 13;
	cvt.u32.u16 	%r122, %rs11;
	@%p573 bra 	$L__BB23_276;
	shl.b32 	%r1382, %r122, 16;
	bra.uni 	$L__BB23_282;
$L__BB23_276:
	cvt.s32.s16 	%r1191, %rs11;
	and.b32 	%r1382, %r1191, -2147483648;
	bfe.u32 	%r123, %r122, 10, 5;
	setp.eq.b32 	%p574, %r123, 31;
	@%p574 bra 	$L__BB23_280;
	and.b32 	%r124, %r122, 1023;
	setp.ne.b32 	%p575, %r123, 0;
	@%p575 bra 	$L__BB23_281;
	setp.eq.b32 	%p576, %r124, 0;
	@%p576 bra 	$L__BB23_282;
	clz.b32 	%r1194, %r124;
	xor.b32 	%r1195, %r1194, 31;
	sub.s32 	%r1196, 9, %r1195;
	shl.b32 	%r1197, %r122, %r1196;
	shl.b32 	%r1198, %r1195, 23;
	shl.b32 	%r1199, %r1197, 14;
	and.b32 	%r1200, %r1199, 8372224;
	add.s32 	%r1201, %r1198, %r1382;
	add.s32 	%r1202, %r1201, %r1200;
	add.s32 	%r1382, %r1202, 864026624;
	bra.uni 	$L__BB23_282;
$L__BB23_280:
	shl.b32 	%r1192, %r122, 13;
	or.b32 	%r1193, %r1382, %r1192;
	or.b32 	%r1382, %r1193, 2139095040;
	bra.uni 	$L__BB23_282;
$L__BB23_281:
	shl.b32 	%r1203, %r123, 23;
	shl.b32 	%r1204, %r124, 13;
	or.b32 	%r1205, %r1203, %r1204;
	add.s32 	%r1206, %r1205, %r1382;
	add.s32 	%r1382, %r1206, 939524096;
$L__BB23_282:
	cvt.f64.f32 	%rd932, %r1382;
	bra.uni 	$L__BB23_690;
$L__BB23_485:
	selp.b32 	%r623, 1, 0, %p209;
	shr.u64 	%rd383, %rd125, %r623;
	add.s32 	%r624, %r220, %r216;
	add.s32 	%r625, %r215, -1;
	shl.b32 	%r626, %r624, %r625;
	shl.b64 	%rd384, %rd375, %r625;
	not.b64 	%rd385, %rd384;
	and.b64 	%rd386, %rd383, %rd385;
	cvt.u32.u64 	%r627, %rd386;
	or.b32 	%r628, %r626, %r627;
	or.b32 	%r1399, %r628, %r213;
$L__BB23_486:
	cvt.u16.u32 	%rs20, %r1399;
	bra.uni 	$L__BB23_487;
$L__BB23_317:
	selp.b32 	%r364, 1, 0, %p48;
	shr.u64 	%rd215, %rd81, %r364;
	add.s32 	%r365, %r143, %r139;
	add.s32 	%r366, %r138, -1;
	shl.b32 	%r367, %r365, %r366;
	shl.b64 	%rd216, %rd207, %r366;
	not.b64 	%rd217, %rd216;
	and.b64 	%rd218, %rd215, %rd217;
	cvt.u32.u64 	%r368, %rd218;
	or.b32 	%r369, %r367, %r368;
	or.b32 	%r1385, %r369, %r136;
$L__BB23_318:
	cvt.u16.u32 	%rs13, %r1385;
	bra.uni 	$L__BB23_319;
$L__BB23_479:
	neg.s32 	%r631, %r219;
	shl.b64 	%rd918, %rd123, %r631;
$L__BB23_482:
	or.b64 	%rd396, %rd918, %rd124;
	cvt.u16.u64 	%rs20, %rd396;
$L__BB23_487:
	setp.ne.b32 	%p218, %r1360, 13;
	cvt.u32.u16 	%r221, %rs20;
	@%p218 bra 	$L__BB23_489;
	shl.b32 	%r1400, %r221, 16;
	bra.uni 	$L__BB23_495;
$L__BB23_489:
	cvt.s32.s16 	%r632, %rs20;
	and.b32 	%r1400, %r632, -2147483648;
	bfe.u32 	%r222, %r221, 10, 5;
	setp.eq.b32 	%p219, %r222, 31;
	@%p219 bra 	$L__BB23_493;
	and.b32 	%r223, %r221, 1023;
	setp.ne.b32 	%p220, %r222, 0;
	@%p220 bra 	$L__BB23_494;
	setp.eq.b32 	%p221, %r223, 0;
	@%p221 bra 	$L__BB23_495;
	clz.b32 	%r635, %r223;
	xor.b32 	%r636, %r635, 31;
	sub.s32 	%r637, 9, %r636;
	shl.b32 	%r638, %r221, %r637;
	shl.b32 	%r639, %r636, 23;
	shl.b32 	%r640, %r638, 14;
	and.b32 	%r641, %r640, 8372224;
	add.s32 	%r642, %r639, %r1400;
	add.s32 	%r643, %r642, %r641;
	add.s32 	%r1400, %r643, 864026624;
	bra.uni 	$L__BB23_495;
$L__BB23_493:
	shl.b32 	%r633, %r221, 13;
	or.b32 	%r634, %r1400, %r633;
	or.b32 	%r1400, %r634, 2139095040;
	bra.uni 	$L__BB23_495;
$L__BB23_494:
	shl.b32 	%r644, %r222, 23;
	shl.b32 	%r645, %r223, 13;
	or.b32 	%r646, %r644, %r645;
	add.s32 	%r647, %r646, %r1400;
	add.s32 	%r1400, %r647, 939524096;
$L__BB23_495:
	cvt.f64.f32 	%rd928, %r1400;
$L__BB23_496:
	mul.rn.f64 	%rd920, %rd75, %rd928;
	@%p677 bra 	$L__BB23_520;
	shr.u64 	%rd128, %rd920, 48;
	cvt.u32.u64 	%r648, %rd128;
	and.b32 	%r224, %r648, 32768;
	shr.u64 	%rd397, %rd920, 52;
	cvt.u32.u64 	%r649, %rd397;
	and.b32 	%r225, %r649, 2047;
	setp.eq.b32 	%p223, %r225, 0;
	@%p223 bra 	$L__BB23_500;
	and.b64 	%rd127, %rd920, 4503599627370495;
	setp.eq.b32 	%p222, %r1360, 12;
	selp.b32 	%r226, 11, 8, %p222;
	selp.b32 	%r228, 31744, 32640, %p222;
	setp.ne.b32 	%p224, %r225, 2047;
	@%p224 bra 	$L__BB23_501;
	setp.eq.b64 	%p225, %rd127, 0;
	add.s32 	%r650, %r226, -2;
	mov.b32 	%r651, 1;
	shl.b32 	%r652, %r651, %r650;
	selp.b32 	%r653, 0, %r652, %p225;
	or.b32 	%r654, %r653, %r228;
	or.b32 	%r655, %r654, %r224;
	cvt.u16.u32 	%rs21, %r655;
	bra.uni 	$L__BB23_511;
$L__BB23_500:
	cvt.u16.u32 	%rs21, %r224;
	bra.uni 	$L__BB23_511;
$L__BB23_501:
	selp.b32 	%r656, -14, -126, %p222;
	add.s32 	%r229, %r225, -1023;
	or.b64 	%rd129, %rd127, 4503599627370496;
	setp.ge.s32 	%p226, %r229, %r656;
	@%p226 bra 	$L__BB23_507;
	and.b64 	%rd130, %rd128, 32768;
	selp.b32 	%r666, 28, -81, %p222;
	sub.s32 	%r230, %r666, %r229;
	setp.gt.s32 	%p234, %r230, 0;
	@%p234 bra 	$L__BB23_504;
	bra.uni 	$L__BB23_503;
$L__BB23_504:
	setp.gt.u32 	%p235, %r230, 63;
	mov.b64 	%rd919, 0;
	@%p235 bra 	$L__BB23_506;
	shr.u64 	%rd411, %rd129, %r230;
	mov.b64 	%rd412, -1;
	shl.b64 	%rd413, %rd412, %r230;
	not.b64 	%rd414, %rd413;
	and.b64 	%rd415, %rd129, %rd414;
	add.s32 	%r667, %r230, -1;
	mov.b64 	%rd416, 1;
	shl.b64 	%rd417, %rd416, %r667;
	setp.gt.u64 	%p236, %rd415, %rd417;
	setp.eq.b64 	%p237, %rd415, %rd417;
	and.b64 	%rd418, %rd411, 1;
	setp.ne.b64 	%p238, %rd418, 0;
	and.pred 	%p239, %p237, %p238;
	or.pred 	%p240, %p236, %p239;
	selp.b64 	%rd419, 1, 0, %p240;
	add.s64 	%rd919, %rd411, %rd419;
	bra.uni 	$L__BB23_506;
$L__BB23_507:
	selp.b32 	%r227, 15, 127, %p222;
	sub.s32 	%r657, 53, %r226;
	shr.u64 	%rd398, %rd129, %r657;
	mov.b64 	%rd399, -1;
	shl.b64 	%rd400, %rd399, %r657;
	not.b64 	%rd401, %rd400;
	and.b64 	%rd402, %rd920, %rd401;
	sub.s32 	%r658, 52, %r226;
	mov.b64 	%rd403, 1;
	shl.b64 	%rd404, %rd403, %r658;
	setp.gt.u64 	%p227, %rd402, %rd404;
	setp.eq.b64 	%p228, %rd402, %rd404;
	and.b64 	%rd405, %rd398, 1;
	setp.ne.b64 	%p229, %rd405, 0;
	and.pred 	%p230, %p228, %p229;
	or.pred 	%p231, %p227, %p230;
	selp.b64 	%rd406, 1, 0, %p231;
	add.s64 	%rd131, %rd398, %rd406;
	shl.b64 	%rd132, %rd403, %r226;
	setp.eq.b64 	%p232, %rd131, %rd132;
	add.s32 	%r659, %r225, -1022;
	selp.b32 	%r231, %r659, %r229, %p232;
	setp.le.s32 	%p233, %r231, %r227;
	@%p233 bra 	$L__BB23_509;
	or.b32 	%r1401, %r224, %r228;
	bra.uni 	$L__BB23_510;
$L__BB23_509:
	selp.b32 	%r660, 1, 0, %p232;
	shr.u64 	%rd407, %rd131, %r660;
	add.s32 	%r661, %r231, %r227;
	add.s32 	%r662, %r226, -1;
	shl.b32 	%r663, %r661, %r662;
	shl.b64 	%rd408, %rd399, %r662;
	not.b64 	%rd409, %rd408;
	and.b64 	%rd410, %rd407, %rd409;
	cvt.u32.u64 	%r664, %rd410;
	or.b32 	%r665, %r663, %r664;
	or.b32 	%r1401, %r665, %r224;
$L__BB23_510:
	cvt.u16.u32 	%rs21, %r1401;
	bra.uni 	$L__BB23_511;
$L__BB23_311:
	neg.s32 	%r372, %r142;
	shl.b64 	%rd906, %rd79, %r372;
$L__BB23_314:
	or.b64 	%rd228, %rd906, %rd80;
	cvt.u16.u64 	%rs13, %rd228;
$L__BB23_319:
	setp.ne.b32 	%p57, %r1360, 13;
	cvt.u32.u16 	%r144, %rs13;
	@%p57 bra 	$L__BB23_321;
	shl.b32 	%r1386, %r144, 16;
	bra.uni 	$L__BB23_327;
$L__BB23_321:
	cvt.s32.s16 	%r373, %rs13;
	and.b32 	%r1386, %r373, -2147483648;
	bfe.u32 	%r145, %r144, 10, 5;
	setp.eq.b32 	%p58, %r145, 31;
	@%p58 bra 	$L__BB23_325;
	and.b32 	%r146, %r144, 1023;
	setp.ne.b32 	%p59, %r145, 0;
	@%p59 bra 	$L__BB23_326;
	setp.eq.b32 	%p60, %r146, 0;
	@%p60 bra 	$L__BB23_327;
	clz.b32 	%r376, %r146;
	xor.b32 	%r377, %r376, 31;
	sub.s32 	%r378, 9, %r377;
	shl.b32 	%r379, %r144, %r378;
	shl.b32 	%r380, %r377, 23;
	shl.b32 	%r381, %r379, 14;
	and.b32 	%r382, %r381, 8372224;
	add.s32 	%r383, %r380, %r1386;
	add.s32 	%r384, %r383, %r382;
	add.s32 	%r1386, %r384, 864026624;
	bra.uni 	$L__BB23_327;
$L__BB23_325:
	shl.b32 	%r374, %r144, 13;
	or.b32 	%r375, %r1386, %r374;
	or.b32 	%r1386, %r375, 2139095040;
	bra.uni 	$L__BB23_327;
$L__BB23_326:
	shl.b32 	%r385, %r145, 23;
	shl.b32 	%r386, %r146, 13;
	or.b32 	%r387, %r385, %r386;
	add.s32 	%r388, %r387, %r1386;
	add.s32 	%r1386, %r388, 939524096;
$L__BB23_327:
	cvt.f64.f32 	%rd928, %r1386;
$L__BB23_328:
	mul.rn.f64 	%rd908, %rd76, %rd928;
	@%p677 bra 	$L__BB23_352;
	shr.u64 	%rd84, %rd908, 48;
	cvt.u32.u64 	%r389, %rd84;
	and.b32 	%r147, %r389, 32768;
	shr.u64 	%rd229, %rd908, 52;
	cvt.u32.u64 	%r390, %rd229;
	and.b32 	%r148, %r390, 2047;
	setp.eq.b32 	%p62, %r148, 0;
	@%p62 bra 	$L__BB23_332;
	and.b64 	%rd83, %rd908, 4503599627370495;
	setp.eq.b32 	%p61, %r1360, 12;
	selp.b32 	%r149, 11, 8, %p61;
	selp.b32 	%r151, 31744, 32640, %p61;
	setp.ne.b32 	%p63, %r148, 2047;
	@%p63 bra 	$L__BB23_333;
	setp.eq.b64 	%p64, %rd83, 0;
	add.s32 	%r391, %r149, -2;
	mov.b32 	%r392, 1;
	shl.b32 	%r393, %r392, %r391;
	selp.b32 	%r394, 0, %r393, %p64;
	or.b32 	%r395, %r394, %r151;
	or.b32 	%r396, %r395, %r147;
	cvt.u16.u32 	%rs14, %r396;
	bra.uni 	$L__BB23_343;
$L__BB23_332:
	cvt.u16.u32 	%rs14, %r147;
	bra.uni 	$L__BB23_343;
$L__BB23_333:
	selp.b32 	%r397, -14, -126, %p61;
	add.s32 	%r152, %r148, -1023;
	or.b64 	%rd85, %rd83, 4503599627370496;
	setp.ge.s32 	%p65, %r152, %r397;
	@%p65 bra 	$L__BB23_339;
	and.b64 	%rd86, %rd84, 32768;
	selp.b32 	%r407, 28, -81, %p61;
	sub.s32 	%r153, %r407, %r152;
	setp.gt.s32 	%p73, %r153, 0;
	@%p73 bra 	$L__BB23_336;
	bra.uni 	$L__BB23_335;
$L__BB23_336:
	setp.gt.u32 	%p74, %r153, 63;
	mov.b64 	%rd907, 0;
	@%p74 bra 	$L__BB23_338;
	shr.u64 	%rd243, %rd85, %r153;
	mov.b64 	%rd244, -1;
	shl.b64 	%rd245, %rd244, %r153;
	not.b64 	%rd246, %rd245;
	and.b64 	%rd247, %rd85, %rd246;
	add.s32 	%r408, %r153, -1;
	mov.b64 	%rd248, 1;
	shl.b64 	%rd249, %rd248, %r408;
	setp.gt.u64 	%p75, %rd247, %rd249;
	setp.eq.b64 	%p76, %rd247, %rd249;
	and.b64 	%rd250, %rd243, 1;
	setp.ne.b64 	%p77, %rd250, 0;
	and.pred 	%p78, %p76, %p77;
	or.pred 	%p79, %p75, %p78;
	selp.b64 	%rd251, 1, 0, %p79;
	add.s64 	%rd907, %rd243, %rd251;
	bra.uni 	$L__BB23_338;
$L__BB23_339:
	selp.b32 	%r150, 15, 127, %p61;
	sub.s32 	%r398, 53, %r149;
	shr.u64 	%rd230, %rd85, %r398;
	mov.b64 	%rd231, -1;
	shl.b64 	%rd232, %rd231, %r398;
	not.b64 	%rd233, %rd232;
	and.b64 	%rd234, %rd908, %rd233;
	sub.s32 	%r399, 52, %r149;
	mov.b64 	%rd235, 1;
	shl.b64 	%rd236, %rd235, %r399;
	setp.gt.u64 	%p66, %rd234, %rd236;
	setp.eq.b64 	%p67, %rd234, %rd236;
	and.b64 	%rd237, %rd230, 1;
	setp.ne.b64 	%p68, %rd237, 0;
	and.pred 	%p69, %p67, %p68;
	or.pred 	%p70, %p66, %p69;
	selp.b64 	%rd238, 1, 0, %p70;
	add.s64 	%rd87, %rd230, %rd238;
	shl.b64 	%rd88, %rd235, %r149;
	setp.eq.b64 	%p71, %rd87, %rd88;
	add.s32 	%r400, %r148, -1022;
	selp.b32 	%r154, %r400, %r152, %p71;
	setp.le.s32 	%p72, %r154, %r150;
	@%p72 bra 	$L__BB23_341;
	or.b32 	%r1387, %r147, %r151;
	bra.uni 	$L__BB23_342;
$L__BB23_341:
	selp.b32 	%r401, 1, 0, %p71;
	shr.u64 	%rd239, %rd87, %r401;
	add.s32 	%r402, %r154, %r150;
	add.s32 	%r403, %r149, -1;
	shl.b32 	%r404, %r402, %r403;
	shl.b64 	%rd240, %rd231, %r403;
	not.b64 	%rd241, %rd240;
)QPTX";
        result += R"QPTX(
	and.b64 	%rd242, %rd239, %rd241;
	cvt.u32.u64 	%r405, %rd242;
	or.b32 	%r406, %r404, %r405;
	or.b32 	%r1387, %r406, %r147;
$L__BB23_342:
	cvt.u16.u32 	%rs14, %r1387;
	bra.uni 	$L__BB23_343;
$L__BB23_503:
	neg.s32 	%r668, %r230;
	shl.b64 	%rd919, %rd129, %r668;
$L__BB23_506:
	or.b64 	%rd420, %rd919, %rd130;
	cvt.u16.u64 	%rs21, %rd420;
$L__BB23_511:
	setp.ne.b32 	%p241, %r1360, 13;
	cvt.u32.u16 	%r232, %rs21;
	@%p241 bra 	$L__BB23_513;
	shl.b32 	%r1402, %r232, 16;
	bra.uni 	$L__BB23_519;
$L__BB23_513:
	cvt.s32.s16 	%r669, %rs21;
	and.b32 	%r1402, %r669, -2147483648;
	bfe.u32 	%r233, %r232, 10, 5;
	setp.eq.b32 	%p242, %r233, 31;
	@%p242 bra 	$L__BB23_517;
	and.b32 	%r234, %r232, 1023;
	setp.ne.b32 	%p243, %r233, 0;
	@%p243 bra 	$L__BB23_518;
	setp.eq.b32 	%p244, %r234, 0;
	@%p244 bra 	$L__BB23_519;
	clz.b32 	%r672, %r234;
	xor.b32 	%r673, %r672, 31;
	sub.s32 	%r674, 9, %r673;
	shl.b32 	%r675, %r232, %r674;
	shl.b32 	%r676, %r673, 23;
	shl.b32 	%r677, %r675, 14;
	and.b32 	%r678, %r677, 8372224;
	add.s32 	%r679, %r676, %r1402;
	add.s32 	%r680, %r679, %r678;
	add.s32 	%r1402, %r680, 864026624;
	bra.uni 	$L__BB23_519;
$L__BB23_517:
	shl.b32 	%r670, %r232, 13;
	or.b32 	%r671, %r1402, %r670;
	or.b32 	%r1402, %r671, 2139095040;
	bra.uni 	$L__BB23_519;
$L__BB23_518:
	shl.b32 	%r681, %r233, 23;
	shl.b32 	%r682, %r234, 13;
	or.b32 	%r683, %r681, %r682;
	add.s32 	%r684, %r683, %r1402;
	add.s32 	%r1402, %r684, 939524096;
$L__BB23_519:
	cvt.f64.f32 	%rd920, %r1402;
$L__BB23_520:
	add.rn.f64 	%rd910, %rd76, %rd920;
	@%p677 bra 	$L__BB23_544;
	shr.u64 	%rd134, %rd910, 48;
	cvt.u32.u64 	%r685, %rd134;
	and.b32 	%r235, %r685, 32768;
	shr.u64 	%rd421, %rd910, 52;
	cvt.u32.u64 	%r686, %rd421;
	and.b32 	%r236, %r686, 2047;
	setp.eq.b32 	%p246, %r236, 0;
	@%p246 bra 	$L__BB23_524;
	and.b64 	%rd133, %rd910, 4503599627370495;
	setp.eq.b32 	%p245, %r1360, 12;
	selp.b32 	%r237, 11, 8, %p245;
	selp.b32 	%r239, 31744, 32640, %p245;
	setp.ne.b32 	%p247, %r236, 2047;
	@%p247 bra 	$L__BB23_525;
	setp.eq.b64 	%p248, %rd133, 0;
	add.s32 	%r687, %r237, -2;
	mov.b32 	%r688, 1;
	shl.b32 	%r689, %r688, %r687;
	selp.b32 	%r690, 0, %r689, %p248;
	or.b32 	%r691, %r690, %r239;
	or.b32 	%r692, %r691, %r235;
	cvt.u16.u32 	%rs22, %r692;
	bra.uni 	$L__BB23_535;
$L__BB23_524:
	cvt.u16.u32 	%rs22, %r235;
	bra.uni 	$L__BB23_535;
$L__BB23_525:
	selp.b32 	%r693, -14, -126, %p245;
	add.s32 	%r240, %r236, -1023;
	or.b64 	%rd135, %rd133, 4503599627370496;
	setp.ge.s32 	%p249, %r240, %r693;
	@%p249 bra 	$L__BB23_531;
	and.b64 	%rd136, %rd134, 32768;
	selp.b32 	%r703, 28, -81, %p245;
	sub.s32 	%r241, %r703, %r240;
	setp.gt.s32 	%p257, %r241, 0;
	@%p257 bra 	$L__BB23_528;
	bra.uni 	$L__BB23_527;
$L__BB23_528:
	setp.gt.u32 	%p258, %r241, 63;
	mov.b64 	%rd921, 0;
	@%p258 bra 	$L__BB23_530;
	shr.u64 	%rd435, %rd135, %r241;
	mov.b64 	%rd436, -1;
	shl.b64 	%rd437, %rd436, %r241;
	not.b64 	%rd438, %rd437;
	and.b64 	%rd439, %rd135, %rd438;
	add.s32 	%r704, %r241, -1;
	mov.b64 	%rd440, 1;
	shl.b64 	%rd441, %rd440, %r704;
	setp.gt.u64 	%p259, %rd439, %rd441;
	setp.eq.b64 	%p260, %rd439, %rd441;
	and.b64 	%rd442, %rd435, 1;
	setp.ne.b64 	%p261, %rd442, 0;
	and.pred 	%p262, %p260, %p261;
	or.pred 	%p263, %p259, %p262;
	selp.b64 	%rd443, 1, 0, %p263;
	add.s64 	%rd921, %rd435, %rd443;
	bra.uni 	$L__BB23_530;
$L__BB23_531:
	selp.b32 	%r238, 15, 127, %p245;
	sub.s32 	%r694, 53, %r237;
	shr.u64 	%rd422, %rd135, %r694;
	mov.b64 	%rd423, -1;
	shl.b64 	%rd424, %rd423, %r694;
	not.b64 	%rd425, %rd424;
	and.b64 	%rd426, %rd910, %rd425;
	sub.s32 	%r695, 52, %r237;
	mov.b64 	%rd427, 1;
	shl.b64 	%rd428, %rd427, %r695;
	setp.gt.u64 	%p250, %rd426, %rd428;
	setp.eq.b64 	%p251, %rd426, %rd428;
	and.b64 	%rd429, %rd422, 1;
	setp.ne.b64 	%p252, %rd429, 0;
	and.pred 	%p253, %p251, %p252;
	or.pred 	%p254, %p250, %p253;
	selp.b64 	%rd430, 1, 0, %p254;
	add.s64 	%rd137, %rd422, %rd430;
	shl.b64 	%rd138, %rd427, %r237;
	setp.eq.b64 	%p255, %rd137, %rd138;
	add.s32 	%r696, %r236, -1022;
	selp.b32 	%r242, %r696, %r240, %p255;
	setp.le.s32 	%p256, %r242, %r238;
	@%p256 bra 	$L__BB23_533;
	or.b32 	%r1403, %r235, %r239;
	bra.uni 	$L__BB23_534;
$L__BB23_533:
	selp.b32 	%r697, 1, 0, %p255;
	shr.u64 	%rd431, %rd137, %r697;
	add.s32 	%r698, %r242, %r238;
	add.s32 	%r699, %r237, -1;
	shl.b32 	%r700, %r698, %r699;
	shl.b64 	%rd432, %rd423, %r699;
	not.b64 	%rd433, %rd432;
	and.b64 	%rd434, %rd431, %rd433;
	cvt.u32.u64 	%r701, %rd434;
	or.b32 	%r702, %r700, %r701;
	or.b32 	%r1403, %r702, %r235;
$L__BB23_534:
	cvt.u16.u32 	%rs22, %r1403;
	bra.uni 	$L__BB23_535;
$L__BB23_335:
	neg.s32 	%r409, %r153;
	shl.b64 	%rd907, %rd85, %r409;
$L__BB23_338:
	or.b64 	%rd252, %rd907, %rd86;
	cvt.u16.u64 	%rs14, %rd252;
$L__BB23_343:
	setp.ne.b32 	%p80, %r1360, 13;
	cvt.u32.u16 	%r155, %rs14;
	@%p80 bra 	$L__BB23_345;
	shl.b32 	%r1388, %r155, 16;
	bra.uni 	$L__BB23_351;
$L__BB23_345:
	cvt.s32.s16 	%r410, %rs14;
	and.b32 	%r1388, %r410, -2147483648;
	bfe.u32 	%r156, %r155, 10, 5;
	setp.eq.b32 	%p81, %r156, 31;
	@%p81 bra 	$L__BB23_349;
	and.b32 	%r157, %r155, 1023;
	setp.ne.b32 	%p82, %r156, 0;
	@%p82 bra 	$L__BB23_350;
	setp.eq.b32 	%p83, %r157, 0;
	@%p83 bra 	$L__BB23_351;
	clz.b32 	%r413, %r157;
	xor.b32 	%r414, %r413, 31;
	sub.s32 	%r415, 9, %r414;
	shl.b32 	%r416, %r155, %r415;
	shl.b32 	%r417, %r414, 23;
	shl.b32 	%r418, %r416, 14;
	and.b32 	%r419, %r418, 8372224;
	add.s32 	%r420, %r417, %r1388;
	add.s32 	%r421, %r420, %r419;
	add.s32 	%r1388, %r421, 864026624;
	bra.uni 	$L__BB23_351;
$L__BB23_349:
	shl.b32 	%r411, %r155, 13;
	or.b32 	%r412, %r1388, %r411;
	or.b32 	%r1388, %r412, 2139095040;
	bra.uni 	$L__BB23_351;
$L__BB23_350:
	shl.b32 	%r422, %r156, 23;
	shl.b32 	%r423, %r157, 13;
	or.b32 	%r424, %r422, %r423;
	add.s32 	%r425, %r424, %r1388;
	add.s32 	%r1388, %r425, 939524096;
$L__BB23_351:
	cvt.f64.f32 	%rd908, %r1388;
$L__BB23_352:
	add.rn.f64 	%rd910, %rd75, %rd908;
	@%p677 bra 	$L__BB23_376;
	shr.u64 	%rd90, %rd910, 48;
	cvt.u32.u64 	%r426, %rd90;
	and.b32 	%r158, %r426, 32768;
	shr.u64 	%rd253, %rd910, 52;
	cvt.u32.u64 	%r427, %rd253;
	and.b32 	%r159, %r427, 2047;
	setp.eq.b32 	%p85, %r159, 0;
	@%p85 bra 	$L__BB23_356;
	and.b64 	%rd89, %rd910, 4503599627370495;
	setp.eq.b32 	%p84, %r1360, 12;
	selp.b32 	%r160, 11, 8, %p84;
	selp.b32 	%r162, 31744, 32640, %p84;
	setp.ne.b32 	%p86, %r159, 2047;
	@%p86 bra 	$L__BB23_357;
	setp.eq.b64 	%p87, %rd89, 0;
	add.s32 	%r428, %r160, -2;
	mov.b32 	%r429, 1;
	shl.b32 	%r430, %r429, %r428;
	selp.b32 	%r431, 0, %r430, %p87;
	or.b32 	%r432, %r431, %r162;
	or.b32 	%r433, %r432, %r158;
	cvt.u16.u32 	%rs15, %r433;
	bra.uni 	$L__BB23_367;
$L__BB23_356:
	cvt.u16.u32 	%rs15, %r158;
	bra.uni 	$L__BB23_367;
$L__BB23_357:
	selp.b32 	%r434, -14, -126, %p84;
	add.s32 	%r163, %r159, -1023;
	or.b64 	%rd91, %rd89, 4503599627370496;
	setp.ge.s32 	%p88, %r163, %r434;
	@%p88 bra 	$L__BB23_363;
	and.b64 	%rd92, %rd90, 32768;
	selp.b32 	%r444, 28, -81, %p84;
	sub.s32 	%r164, %r444, %r163;
	setp.gt.s32 	%p96, %r164, 0;
	@%p96 bra 	$L__BB23_360;
	bra.uni 	$L__BB23_359;
$L__BB23_360:
	setp.gt.u32 	%p97, %r164, 63;
	mov.b64 	%rd909, 0;
	@%p97 bra 	$L__BB23_362;
	shr.u64 	%rd267, %rd91, %r164;
	mov.b64 	%rd268, -1;
	shl.b64 	%rd269, %rd268, %r164;
	not.b64 	%rd270, %rd269;
	and.b64 	%rd271, %rd91, %rd270;
	add.s32 	%r445, %r164, -1;
	mov.b64 	%rd272, 1;
	shl.b64 	%rd273, %rd272, %r445;
	setp.gt.u64 	%p98, %rd271, %rd273;
	setp.eq.b64 	%p99, %rd271, %rd273;
	and.b64 	%rd274, %rd267, 1;
	setp.ne.b64 	%p100, %rd274, 0;
	and.pred 	%p101, %p99, %p100;
	or.pred 	%p102, %p98, %p101;
	selp.b64 	%rd275, 1, 0, %p102;
	add.s64 	%rd909, %rd267, %rd275;
	bra.uni 	$L__BB23_362;
$L__BB23_363:
	selp.b32 	%r161, 15, 127, %p84;
	sub.s32 	%r435, 53, %r160;
	shr.u64 	%rd254, %rd91, %r435;
	mov.b64 	%rd255, -1;
	shl.b64 	%rd256, %rd255, %r435;
	not.b64 	%rd257, %rd256;
	and.b64 	%rd258, %rd910, %rd257;
	sub.s32 	%r436, 52, %r160;
	mov.b64 	%rd259, 1;
	shl.b64 	%rd260, %rd259, %r436;
	setp.gt.u64 	%p89, %rd258, %rd260;
	setp.eq.b64 	%p90, %rd258, %rd260;
	and.b64 	%rd261, %rd254, 1;
	setp.ne.b64 	%p91, %rd261, 0;
	and.pred 	%p92, %p90, %p91;
	or.pred 	%p93, %p89, %p92;
	selp.b64 	%rd262, 1, 0, %p93;
	add.s64 	%rd93, %rd254, %rd262;
	shl.b64 	%rd94, %rd259, %r160;
	setp.eq.b64 	%p94, %rd93, %rd94;
	add.s32 	%r437, %r159, -1022;
	selp.b32 	%r165, %r437, %r163, %p94;
	setp.le.s32 	%p95, %r165, %r161;
	@%p95 bra 	$L__BB23_365;
	or.b32 	%r1389, %r158, %r162;
	bra.uni 	$L__BB23_366;
$L__BB23_365:
	selp.b32 	%r438, 1, 0, %p94;
	shr.u64 	%rd263, %rd93, %r438;
	add.s32 	%r439, %r165, %r161;
	add.s32 	%r440, %r160, -1;
	shl.b32 	%r441, %r439, %r440;
	shl.b64 	%rd264, %rd255, %r440;
	not.b64 	%rd265, %rd264;
	and.b64 	%rd266, %rd263, %rd265;
	cvt.u32.u64 	%r442, %rd266;
	or.b32 	%r443, %r441, %r442;
	or.b32 	%r1389, %r443, %r158;
$L__BB23_366:
	cvt.u16.u32 	%rs15, %r1389;
	bra.uni 	$L__BB23_367;
$L__BB23_527:
	neg.s32 	%r705, %r241;
	shl.b64 	%rd921, %rd135, %r705;
$L__BB23_530:
	or.b64 	%rd444, %rd921, %rd136;
	cvt.u16.u64 	%rs22, %rd444;
$L__BB23_535:
	setp.ne.b32 	%p264, %r1360, 13;
	cvt.u32.u16 	%r243, %rs22;
	@%p264 bra 	$L__BB23_537;
	shl.b32 	%r1404, %r243, 16;
	bra.uni 	$L__BB23_543;
$L__BB23_537:
	cvt.s32.s16 	%r706, %rs22;
	and.b32 	%r1404, %r706, -2147483648;
	bfe.u32 	%r244, %r243, 10, 5;
	setp.eq.b32 	%p265, %r244, 31;
	@%p265 bra 	$L__BB23_541;
	and.b32 	%r245, %r243, 1023;
	setp.ne.b32 	%p266, %r244, 0;
	@%p266 bra 	$L__BB23_542;
	setp.eq.b32 	%p267, %r245, 0;
	@%p267 bra 	$L__BB23_543;
	clz.b32 	%r709, %r245;
	xor.b32 	%r710, %r709, 31;
	sub.s32 	%r711, 9, %r710;
	shl.b32 	%r712, %r243, %r711;
	shl.b32 	%r713, %r710, 23;
	shl.b32 	%r714, %r712, 14;
	and.b32 	%r715, %r714, 8372224;
	add.s32 	%r716, %r713, %r1404;
	add.s32 	%r717, %r716, %r715;
	add.s32 	%r1404, %r717, 864026624;
	bra.uni 	$L__BB23_543;
$L__BB23_541:
	shl.b32 	%r707, %r243, 13;
	or.b32 	%r708, %r1404, %r707;
	or.b32 	%r1404, %r708, 2139095040;
	bra.uni 	$L__BB23_543;
$L__BB23_542:
	shl.b32 	%r718, %r244, 23;
	shl.b32 	%r719, %r245, 13;
	or.b32 	%r720, %r718, %r719;
	add.s32 	%r721, %r720, %r1404;
	add.s32 	%r1404, %r721, 939524096;
$L__BB23_543:
	cvt.f64.f32 	%rd910, %r1404;
$L__BB23_544:
	ld.local.b64 	%rd139, [%rd1];
	mul.rn.f64 	%rd923, %rd928, %rd139;
	@%p677 bra 	$L__BB23_568;
	shr.u64 	%rd141, %rd923, 48;
	cvt.u32.u64 	%r722, %rd141;
	and.b32 	%r246, %r722, 32768;
	shr.u64 	%rd445, %rd923, 52;
	cvt.u32.u64 	%r723, %rd445;
	and.b32 	%r247, %r723, 2047;
	setp.eq.b32 	%p269, %r247, 0;
	@%p269 bra 	$L__BB23_548;
	and.b64 	%rd140, %rd923, 4503599627370495;
	setp.eq.b32 	%p268, %r1360, 12;
	selp.b32 	%r248, 11, 8, %p268;
	selp.b32 	%r250, 31744, 32640, %p268;
	setp.ne.b32 	%p270, %r247, 2047;
	@%p270 bra 	$L__BB23_549;
	setp.eq.b64 	%p271, %rd140, 0;
	add.s32 	%r724, %r248, -2;
	mov.b32 	%r725, 1;
	shl.b32 	%r726, %r725, %r724;
	selp.b32 	%r727, 0, %r726, %p271;
	or.b32 	%r728, %r727, %r250;
	or.b32 	%r729, %r728, %r246;
	cvt.u16.u32 	%rs23, %r729;
	bra.uni 	$L__BB23_559;
$L__BB23_548:
	cvt.u16.u32 	%rs23, %r246;
	bra.uni 	$L__BB23_559;
$L__BB23_549:
	selp.b32 	%r730, -14, -126, %p268;
	add.s32 	%r251, %r247, -1023;
	or.b64 	%rd142, %rd140, 4503599627370496;
	setp.ge.s32 	%p272, %r251, %r730;
	@%p272 bra 	$L__BB23_555;
	and.b64 	%rd143, %rd141, 32768;
	selp.b32 	%r740, 28, -81, %p268;
	sub.s32 	%r252, %r740, %r251;
	setp.gt.s32 	%p280, %r252, 0;
	@%p280 bra 	$L__BB23_552;
	bra.uni 	$L__BB23_551;
$L__BB23_552:
	setp.gt.u32 	%p281, %r252, 63;
	mov.b64 	%rd922, 0;
	@%p281 bra 	$L__BB23_554;
	shr.u64 	%rd459, %rd142, %r252;
	mov.b64 	%rd460, -1;
	shl.b64 	%rd461, %rd460, %r252;
	not.b64 	%rd462, %rd461;
	and.b64 	%rd463, %rd142, %rd462;
	add.s32 	%r741, %r252, -1;
	mov.b64 	%rd464, 1;
	shl.b64 	%rd465, %rd464, %r741;
	setp.gt.u64 	%p282, %rd463, %rd465;
	setp.eq.b64 	%p283, %rd463, %rd465;
	and.b64 	%rd466, %rd459, 1;
	setp.ne.b64 	%p284, %rd466, 0;
	and.pred 	%p285, %p283, %p284;
	or.pred 	%p286, %p282, %p285;
	selp.b64 	%rd467, 1, 0, %p286;
	add.s64 	%rd922, %rd459, %rd467;
	bra.uni 	$L__BB23_554;
$L__BB23_555:
	selp.b32 	%r249, 15, 127, %p268;
	sub.s32 	%r731, 53, %r248;
	shr.u64 	%rd446, %rd142, %r731;
	mov.b64 	%rd447, -1;
	shl.b64 	%rd448, %rd447, %r731;
	not.b64 	%rd449, %rd448;
	and.b64 	%rd450, %rd923, %rd449;
	sub.s32 	%r732, 52, %r248;
	mov.b64 	%rd451, 1;
	shl.b64 	%rd452, %rd451, %r732;
	setp.gt.u64 	%p273, %rd450, %rd452;
	setp.eq.b64 	%p274, %rd450, %rd452;
	and.b64 	%rd453, %rd446, 1;
	setp.ne.b64 	%p275, %rd453, 0;
	and.pred 	%p276, %p274, %p275;
	or.pred 	%p277, %p273, %p276;
	selp.b64 	%rd454, 1, 0, %p277;
	add.s64 	%rd144, %rd446, %rd454;
	shl.b64 	%rd145, %rd451, %r248;
	setp.eq.b64 	%p278, %rd144, %rd145;
	add.s32 	%r733, %r247, -1022;
	selp.b32 	%r253, %r733, %r251, %p278;
	setp.le.s32 	%p279, %r253, %r249;
	@%p279 bra 	$L__BB23_557;
	or.b32 	%r1405, %r246, %r250;
	bra.uni 	$L__BB23_558;
$L__BB23_557:
	selp.b32 	%r734, 1, 0, %p278;
	shr.u64 	%rd455, %rd144, %r734;
	add.s32 	%r735, %r253, %r249;
	add.s32 	%r736, %r248, -1;
	shl.b32 	%r737, %r735, %r736;
	shl.b64 	%rd456, %rd447, %r736;
	not.b64 	%rd457, %rd456;
	and.b64 	%rd458, %rd455, %rd457;
	cvt.u32.u64 	%r738, %rd458;
	or.b32 	%r739, %r737, %r738;
	or.b32 	%r1405, %r739, %r246;
$L__BB23_558:
	cvt.u16.u32 	%rs23, %r1405;
	bra.uni 	$L__BB23_559;
$L__BB23_359:
	neg.s32 	%r446, %r164;
	shl.b64 	%rd909, %rd91, %r446;
$L__BB23_362:
	or.b64 	%rd276, %rd909, %rd92;
	cvt.u16.u64 	%rs15, %rd276;
$L__BB23_367:
	setp.ne.b32 	%p103, %r1360, 13;
	cvt.u32.u16 	%r166, %rs15;
	@%p103 bra 	$L__BB23_369;
	shl.b32 	%r1390, %r166, 16;
	bra.uni 	$L__BB23_375;
$L__BB23_369:
	cvt.s32.s16 	%r447, %rs15;
	and.b32 	%r1390, %r447, -2147483648;
	bfe.u32 	%r167, %r166, 10, 5;
	setp.eq.b32 	%p104, %r167, 31;
	@%p104 bra 	$L__BB23_373;
	and.b32 	%r168, %r166, 1023;
	setp.ne.b32 	%p105, %r167, 0;
	@%p105 bra 	$L__BB23_374;
	setp.eq.b32 	%p106, %r168, 0;
	@%p106 bra 	$L__BB23_375;
	clz.b32 	%r450, %r168;
	xor.b32 	%r451, %r450, 31;
	sub.s32 	%r452, 9, %r451;
	shl.b32 	%r453, %r166, %r452;
	shl.b32 	%r454, %r451, 23;
	shl.b32 	%r455, %r453, 14;
	and.b32 	%r456, %r455, 8372224;
	add.s32 	%r457, %r454, %r1390;
	add.s32 	%r458, %r457, %r456;
	add.s32 	%r1390, %r458, 864026624;
	bra.uni 	$L__BB23_375;
$L__BB23_373:
	shl.b32 	%r448, %r166, 13;
	or.b32 	%r449, %r1390, %r448;
	or.b32 	%r1390, %r449, 2139095040;
	bra.uni 	$L__BB23_375;
$L__BB23_374:
	shl.b32 	%r459, %r167, 23;
	shl.b32 	%r460, %r168, 13;
	or.b32 	%r461, %r459, %r460;
	add.s32 	%r462, %r461, %r1390;
	add.s32 	%r1390, %r462, 939524096;
$L__BB23_375:
	cvt.f64.f32 	%rd910, %r1390;
$L__BB23_376:
	ld.local.b64 	%rd95, [%rd1];
	ld.local.b64 	%rd96, [%rd1+8];
	mul.rn.f64 	%rd912, %rd928, %rd96;
	@%p677 bra 	$L__BB23_400;
	shr.u64 	%rd98, %rd912, 48;
	cvt.u32.u64 	%r463, %rd98;
	and.b32 	%r169, %r463, 32768;
	shr.u64 	%rd277, %rd912, 52;
	cvt.u32.u64 	%r464, %rd277;
	and.b32 	%r170, %r464, 2047;
	setp.eq.b32 	%p108, %r170, 0;
	@%p108 bra 	$L__BB23_380;
	and.b64 	%rd97, %rd912, 4503599627370495;
	setp.eq.b32 	%p107, %r1360, 12;
	selp.b32 	%r171, 11, 8, %p107;
	selp.b32 	%r173, 31744, 32640, %p107;
	setp.ne.b32 	%p109, %r170, 2047;
	@%p109 bra 	$L__BB23_381;
	setp.eq.b64 	%p110, %rd97, 0;
	add.s32 	%r465, %r171, -2;
	mov.b32 	%r466, 1;
	shl.b32 	%r467, %r466, %r465;
	selp.b32 	%r468, 0, %r467, %p110;
	or.b32 	%r469, %r468, %r173;
	or.b32 	%r470, %r469, %r169;
	cvt.u16.u32 	%rs16, %r470;
	bra.uni 	$L__BB23_391;
$L__BB23_380:
	cvt.u16.u32 	%rs16, %r169;
	bra.uni 	$L__BB23_391;
$L__BB23_381:
	selp.b32 	%r471, -14, -126, %p107;
	add.s32 	%r174, %r170, -1023;
	or.b64 	%rd99, %rd97, 4503599627370496;
	setp.ge.s32 	%p111, %r174, %r471;
	@%p111 bra 	$L__BB23_387;
	and.b64 	%rd100, %rd98, 32768;
	selp.b32 	%r481, 28, -81, %p107;
	sub.s32 	%r175, %r481, %r174;
	setp.gt.s32 	%p119, %r175, 0;
	@%p119 bra 	$L__BB23_384;
	bra.uni 	$L__BB23_383;
$L__BB23_384:
	setp.gt.u32 	%p120, %r175, 63;
	mov.b64 	%rd911, 0;
	@%p120 bra 	$L__BB23_386;
	shr.u64 	%rd291, %rd99, %r175;
	mov.b64 	%rd292, -1;
	shl.b64 	%rd293, %rd292, %r175;
	not.b64 	%rd294, %rd293;
	and.b64 	%rd295, %rd99, %rd294;
	add.s32 	%r482, %r175, -1;
	mov.b64 	%rd296, 1;
	shl.b64 	%rd297, %rd296, %r482;
	setp.gt.u64 	%p121, %rd295, %rd297;
	setp.eq.b64 	%p122, %rd295, %rd297;
	and.b64 	%rd298, %rd291, 1;
	setp.ne.b64 	%p123, %rd298, 0;
	and.pred 	%p124, %p122, %p123;
	or.pred 	%p125, %p121, %p124;
	selp.b64 	%rd299, 1, 0, %p125;
	add.s64 	%rd911, %rd291, %rd299;
	bra.uni 	$L__BB23_386;
$L__BB23_387:
	selp.b32 	%r172, 15, 127, %p107;
	sub.s32 	%r472, 53, %r171;
	shr.u64 	%rd278, %rd99, %r472;
	mov.b64 	%rd279, -1;
	shl.b64 	%rd280, %rd279, %r472;
	not.b64 	%rd281, %rd280;
	and.b64 	%rd282, %rd912, %rd281;
	sub.s32 	%r473, 52, %r171;
	mov.b64 	%rd283, 1;
	shl.b64 	%rd284, %rd283, %r473;
	setp.gt.u64 	%p112, %rd282, %rd284;
	setp.eq.b64 	%p113, %rd282, %rd284;
	and.b64 	%rd285, %rd278, 1;
	setp.ne.b64 	%p114, %rd285, 0;
	and.pred 	%p115, %p113, %p114;
	or.pred 	%p116, %p112, %p115;
	selp.b64 	%rd286, 1, 0, %p116;
	add.s64 	%rd101, %rd278, %rd286;
	shl.b64 	%rd102, %rd283, %r171;
	setp.eq.b64 	%p117, %rd101, %rd102;
	add.s32 	%r474, %r170, -1022;
	selp.b32 	%r176, %r474, %r174, %p117;
	setp.le.s32 	%p118, %r176, %r172;
	@%p118 bra 	$L__BB23_389;
	or.b32 	%r1391, %r169, %r173;
	bra.uni 	$L__BB23_390;
$L__BB23_389:
	selp.b32 	%r475, 1, 0, %p117;
	shr.u64 	%rd287, %rd101, %r475;
	add.s32 	%r476, %r176, %r172;
	add.s32 	%r477, %r171, -1;
	shl.b32 	%r478, %r476, %r477;
	shl.b64 	%rd288, %rd279, %r477;
	not.b64 	%rd289, %rd288;
	and.b64 	%rd290, %rd287, %rd289;
	cvt.u32.u64 	%r479, %rd290;
	or.b32 	%r480, %r478, %r479;
	or.b32 	%r1391, %r480, %r169;
$L__BB23_390:
	cvt.u16.u32 	%rs16, %r1391;
	bra.uni 	$L__BB23_391;
$L__BB23_551:
	neg.s32 	%r742, %r252;
	shl.b64 	%rd922, %rd142, %r742;
$L__BB23_554:
	or.b64 	%rd468, %rd922, %rd143;
	cvt.u16.u64 	%rs23, %rd468;
$L__BB23_559:
	setp.ne.b32 	%p287, %r1360, 13;
	cvt.u32.u16 	%r254, %rs23;
	@%p287 bra 	$L__BB23_561;
	shl.b32 	%r1406, %r254, 16;
	bra.uni 	$L__BB23_567;
$L__BB23_561:
	cvt.s32.s16 	%r743, %rs23;
	and.b32 	%r1406, %r743, -2147483648;
	bfe.u32 	%r255, %r254, 10, 5;
	setp.eq.b32 	%p288, %r255, 31;
	@%p288 bra 	$L__BB23_565;
	and.b32 	%r256, %r254, 1023;
	setp.ne.b32 	%p289, %r255, 0;
	@%p289 bra 	$L__BB23_566;
	setp.eq.b32 	%p290, %r256, 0;
	@%p290 bra 	$L__BB23_567;
	clz.b32 	%r746, %r256;
	xor.b32 	%r747, %r746, 31;
	sub.s32 	%r748, 9, %r747;
	shl.b32 	%r749, %r254, %r748;
	shl.b32 	%r750, %r747, 23;
	shl.b32 	%r751, %r749, 14;
	and.b32 	%r752, %r751, 8372224;
	add.s32 	%r753, %r750, %r1406;
	add.s32 	%r754, %r753, %r752;
	add.s32 	%r1406, %r754, 864026624;
	bra.uni 	$L__BB23_567;
$L__BB23_565:
	shl.b32 	%r744, %r254, 13;
	or.b32 	%r745, %r1406, %r744;
	or.b32 	%r1406, %r745, 2139095040;
	bra.uni 	$L__BB23_567;
$L__BB23_566:
	shl.b32 	%r755, %r255, 23;
	shl.b32 	%r756, %r256, 13;
	or.b32 	%r757, %r755, %r756;
	add.s32 	%r758, %r757, %r1406;
	add.s32 	%r1406, %r758, 939524096;
$L__BB23_567:
	cvt.f64.f32 	%rd923, %r1406;
$L__BB23_568:
	ld.local.b64 	%rd146, [%rd1+8];
	add.rn.f64 	%rd914, %rd923, %rd146;
	@%p677 bra 	$L__BB23_592;
	shr.u64 	%rd148, %rd914, 48;
	cvt.u32.u64 	%r759, %rd148;
	and.b32 	%r257, %r759, 32768;
	shr.u64 	%rd469, %rd914, 52;
	cvt.u32.u64 	%r760, %rd469;
	and.b32 	%r258, %r760, 2047;
	setp.eq.b32 	%p292, %r258, 0;
	@%p292 bra 	$L__BB23_572;
	and.b64 	%rd147, %rd914, 4503599627370495;
	setp.eq.b32 	%p291, %r1360, 12;
	selp.b32 	%r259, 11, 8, %p291;
	selp.b32 	%r261, 31744, 32640, %p291;
	setp.ne.b32 	%p293, %r258, 2047;
	@%p293 bra 	$L__BB23_573;
	setp.eq.b64 	%p294, %rd147, 0;
	add.s32 	%r761, %r259, -2;
	mov.b32 	%r762, 1;
	shl.b32 	%r763, %r762, %r761;
	selp.b32 	%r764, 0, %r763, %p294;
	or.b32 	%r765, %r764, %r261;
	or.b32 	%r766, %r765, %r257;
	cvt.u16.u32 	%rs24, %r766;
	bra.uni 	$L__BB23_583;
$L__BB23_572:
	cvt.u16.u32 	%rs24, %r257;
	bra.uni 	$L__BB23_583;
$L__BB23_573:
	selp.b32 	%r767, -14, -126, %p291;
	add.s32 	%r262, %r258, -1023;
	or.b64 	%rd149, %rd147, 4503599627370496;
	setp.ge.s32 	%p295, %r262, %r767;
	@%p295 bra 	$L__BB23_579;
	and.b64 	%rd150, %rd148, 32768;
	selp.b32 	%r777, 28, -81, %p291;
	sub.s32 	%r263, %r777, %r262;
	setp.gt.s32 	%p303, %r263, 0;
	@%p303 bra 	$L__BB23_576;
	bra.uni 	$L__BB23_575;
$L__BB23_576:
	setp.gt.u32 	%p304, %r263, 63;
	mov.b64 	%rd924, 0;
	@%p304 bra 	$L__BB23_578;
	shr.u64 	%rd483, %rd149, %r263;
	mov.b64 	%rd484, -1;
	shl.b64 	%rd485, %rd484, %r263;
	not.b64 	%rd486, %rd485;
	and.b64 	%rd487, %rd149, %rd486;
	add.s32 	%r778, %r263, -1;
	mov.b64 	%rd488, 1;
	shl.b64 	%rd489, %rd488, %r778;
	setp.gt.u64 	%p305, %rd487, %rd489;
	setp.eq.b64 	%p306, %rd487, %rd489;
	and.b64 	%rd490, %rd483, 1;
	setp.ne.b64 	%p307, %rd490, 0;
	and.pred 	%p308, %p306, %p307;
	or.pred 	%p309, %p305, %p308;
	selp.b64 	%rd491, 1, 0, %p309;
	add.s64 	%rd924, %rd483, %rd491;
	bra.uni 	$L__BB23_578;
$L__BB23_579:
	selp.b32 	%r260, 15, 127, %p291;
	sub.s32 	%r768, 53, %r259;
	shr.u64 	%rd470, %rd149, %r768;
	mov.b64 	%rd471, -1;
	shl.b64 	%rd472, %rd471, %r768;
	not.b64 	%rd473, %rd472;
	and.b64 	%rd474, %rd914, %rd473;
	sub.s32 	%r769, 52, %r259;
	mov.b64 	%rd475, 1;
	shl.b64 	%rd476, %rd475, %r769;
	setp.gt.u64 	%p296, %rd474, %rd476;
	setp.eq.b64 	%p297, %rd474, %rd476;
	and.b64 	%rd477, %rd470, 1;
	setp.ne.b64 	%p298, %rd477, 0;
	and.pred 	%p299, %p297, %p298;
	or.pred 	%p300, %p296, %p299;
	selp.b64 	%rd478, 1, 0, %p300;
	add.s64 	%rd151, %rd470, %rd478;
	shl.b64 	%rd152, %rd475, %r259;
	setp.eq.b64 	%p301, %rd151, %rd152;
	add.s32 	%r770, %r258, -1022;
	selp.b32 	%r264, %r770, %r262, %p301;
	setp.le.s32 	%p302, %r264, %r260;
	@%p302 bra 	$L__BB23_581;
	or.b32 	%r1407, %r257, %r261;
	bra.uni 	$L__BB23_582;
$L__BB23_581:
	selp.b32 	%r771, 1, 0, %p301;
	shr.u64 	%rd479, %rd151, %r771;
	add.s32 	%r772, %r264, %r260;
	add.s32 	%r773, %r259, -1;
	shl.b32 	%r774, %r772, %r773;
	shl.b64 	%rd480, %rd471, %r773;
	not.b64 	%rd481, %rd480;
	and.b64 	%rd482, %rd479, %rd481;
	cvt.u32.u64 	%r775, %rd482;
	or.b32 	%r776, %r774, %r775;
	or.b32 	%r1407, %r776, %r257;
$L__BB23_582:
	cvt.u16.u32 	%rs24, %r1407;
	bra.uni 	$L__BB23_583;
$L__BB23_383:
	neg.s32 	%r483, %r175;
	shl.b64 	%rd911, %rd99, %r483;
$L__BB23_386:
	or.b64 	%rd300, %rd911, %rd100;
	cvt.u16.u64 	%rs16, %rd300;
$L__BB23_391:
	setp.ne.b32 	%p126, %r1360, 13;
	cvt.u32.u16 	%r177, %rs16;
	@%p126 bra 	$L__BB23_393;
	shl.b32 	%r1392, %r177, 16;
	bra.uni 	$L__BB23_399;
$L__BB23_393:
	cvt.s32.s16 	%r484, %rs16;
	and.b32 	%r1392, %r484, -2147483648;
	bfe.u32 	%r178, %r177, 10, 5;
	setp.eq.b32 	%p127, %r178, 31;
	@%p127 bra 	$L__BB23_397;
	and.b32 	%r179, %r177, 1023;
	setp.ne.b32 	%p128, %r178, 0;
	@%p128 bra 	$L__BB23_398;
	setp.eq.b32 	%p129, %r179, 0;
	@%p129 bra 	$L__BB23_399;
	clz.b32 	%r487, %r179;
	xor.b32 	%r488, %r487, 31;
	sub.s32 	%r489, 9, %r488;
	shl.b32 	%r490, %r177, %r489;
	shl.b32 	%r491, %r488, 23;
	shl.b32 	%r492, %r490, 14;
	and.b32 	%r493, %r492, 8372224;
	add.s32 	%r494, %r491, %r1392;
	add.s32 	%r495, %r494, %r493;
	add.s32 	%r1392, %r495, 864026624;
	bra.uni 	$L__BB23_399;
$L__BB23_397:
	shl.b32 	%r485, %r177, 13;
	or.b32 	%r486, %r1392, %r485;
	or.b32 	%r1392, %r486, 2139095040;
	bra.uni 	$L__BB23_399;
$L__BB23_398:
	shl.b32 	%r496, %r178, 23;
	shl.b32 	%r497, %r179, 13;
	or.b32 	%r498, %r496, %r497;
	add.s32 	%r499, %r498, %r1392;
	add.s32 	%r1392, %r499, 939524096;
$L__BB23_399:
	cvt.f64.f32 	%rd912, %r1392;
$L__BB23_400:
	add.rn.f64 	%rd914, %rd95, %rd912;
	@%p677 bra 	$L__BB23_424;
	shr.u64 	%rd104, %rd914, 48;
	cvt.u32.u64 	%r500, %rd104;
	and.b32 	%r180, %r500, 32768;
	shr.u64 	%rd301, %rd914, 52;
	cvt.u32.u64 	%r501, %rd301;
	and.b32 	%r181, %r501, 2047;
	setp.eq.b32 	%p131, %r181, 0;
	@%p131 bra 	$L__BB23_404;
	and.b64 	%rd103, %rd914, 4503599627370495;
	setp.eq.b32 	%p130, %r1360, 12;
	selp.b32 	%r182, 11, 8, %p130;
	selp.b32 	%r184, 31744, 32640, %p130;
	setp.ne.b32 	%p132, %r181, 2047;
	@%p132 bra 	$L__BB23_405;
	setp.eq.b64 	%p133, %rd103, 0;
	add.s32 	%r502, %r182, -2;
	mov.b32 	%r503, 1;
	shl.b32 	%r504, %r503, %r502;
	selp.b32 	%r505, 0, %r504, %p133;
	or.b32 	%r506, %r505, %r184;
	or.b32 	%r507, %r506, %r180;
	cvt.u16.u32 	%rs17, %r507;
	bra.uni 	$L__BB23_415;
$L__BB23_404:
	cvt.u16.u32 	%rs17, %r180;
	bra.uni 	$L__BB23_415;
$L__BB23_405:
	selp.b32 	%r508, -14, -126, %p130;
	add.s32 	%r185, %r181, -1023;
	or.b64 	%rd105, %rd103, 4503599627370496;
	setp.ge.s32 	%p134, %r185, %r508;
	@%p134 bra 	$L__BB23_411;
	and.b64 	%rd106, %rd104, 32768;
	selp.b32 	%r518, 28, -81, %p130;
	sub.s32 	%r186, %r518, %r185;
	setp.gt.s32 	%p142, %r186, 0;
	@%p142 bra 	$L__BB23_408;
	bra.uni 	$L__BB23_407;
$L__BB23_408:
	setp.gt.u32 	%p143, %r186, 63;
	mov.b64 	%rd913, 0;
	@%p143 bra 	$L__BB23_410;
	shr.u64 	%rd315, %rd105, %r186;
	mov.b64 	%rd316, -1;
	shl.b64 	%rd317, %rd316, %r186;
	not.b64 	%rd318, %rd317;
	and.b64 	%rd319, %rd105, %rd318;
	add.s32 	%r519, %r186, -1;
	mov.b64 	%rd320, 1;
	shl.b64 	%rd321, %rd320, %r519;
	setp.gt.u64 	%p144, %rd319, %rd321;
	setp.eq.b64 	%p145, %rd319, %rd321;
	and.b64 	%rd322, %rd315, 1;
	setp.ne.b64 	%p146, %rd322, 0;
	and.pred 	%p147, %p145, %p146;
	or.pred 	%p148, %p144, %p147;
	selp.b64 	%rd323, 1, 0, %p148;
	add.s64 	%rd913, %rd315, %rd323;
	bra.uni 	$L__BB23_410;
$L__BB23_411:
	selp.b32 	%r183, 15, 127, %p130;
	sub.s32 	%r509, 53, %r182;
	shr.u64 	%rd302, %rd105, %r509;
	mov.b64 	%rd303, -1;
	shl.b64 	%rd304, %rd303, %r509;
	not.b64 	%rd305, %rd304;
	and.b64 	%rd306, %rd914, %rd305;
	sub.s32 	%r510, 52, %r182;
	mov.b64 	%rd307, 1;
	shl.b64 	%rd308, %rd307, %r510;
	setp.gt.u64 	%p135, %rd306, %rd308;
	setp.eq.b64 	%p136, %rd306, %rd308;
	and.b64 	%rd309, %rd302, 1;
	setp.ne.b64 	%p137, %rd309, 0;
	and.pred 	%p138, %p136, %p137;
	or.pred 	%p139, %p135, %p138;
	selp.b64 	%rd310, 1, 0, %p139;
	add.s64 	%rd107, %rd302, %rd310;
	shl.b64 	%rd108, %rd307, %r182;
	setp.eq.b64 	%p140, %rd107, %rd108;
	add.s32 	%r511, %r181, -1022;
	selp.b32 	%r187, %r511, %r185, %p140;
	setp.le.s32 	%p141, %r187, %r183;
	@%p141 bra 	$L__BB23_413;
	or.b32 	%r1393, %r180, %r184;
	bra.uni 	$L__BB23_414;
$L__BB23_413:
	selp.b32 	%r512, 1, 0, %p140;
	shr.u64 	%rd311, %rd107, %r512;
	add.s32 	%r513, %r187, %r183;
	add.s32 	%r514, %r182, -1;
	shl.b32 	%r515, %r513, %r514;
	shl.b64 	%rd312, %rd303, %r514;
	not.b64 	%rd313, %rd312;
	and.b64 	%rd314, %rd311, %rd313;
	cvt.u32.u64 	%r516, %rd314;
	or.b32 	%r517, %r515, %r516;
	or.b32 	%r1393, %r517, %r180;
$L__BB23_414:
	cvt.u16.u32 	%rs17, %r1393;
	bra.uni 	$L__BB23_415;
$L__BB23_575:
	neg.s32 	%r779, %r263;
	shl.b64 	%rd924, %rd149, %r779;
$L__BB23_578:
	or.b64 	%rd492, %rd924, %rd150;
	cvt.u16.u64 	%rs24, %rd492;
$L__BB23_583:
	setp.ne.b32 	%p310, %r1360, 13;
	cvt.u32.u16 	%r265, %rs24;
	@%p310 bra 	$L__BB23_585;
	shl.b32 	%r1408, %r265, 16;
	bra.uni 	$L__BB23_591;
$L__BB23_585:
	cvt.s32.s16 	%r780, %rs24;
	and.b32 	%r1408, %r780, -2147483648;
	bfe.u32 	%r266, %r265, 10, 5;
	setp.eq.b32 	%p311, %r266, 31;
	@%p311 bra 	$L__BB23_589;
	and.b32 	%r267, %r265, 1023;
	setp.ne.b32 	%p312, %r266, 0;
	@%p312 bra 	$L__BB23_590;
	setp.eq.b32 	%p313, %r267, 0;
	@%p313 bra 	$L__BB23_591;
	clz.b32 	%r783, %r267;
	xor.b32 	%r784, %r783, 31;
	sub.s32 	%r785, 9, %r784;
	shl.b32 	%r786, %r265, %r785;
	shl.b32 	%r787, %r784, 23;
	shl.b32 	%r788, %r786, 14;
	and.b32 	%r789, %r788, 8372224;
	add.s32 	%r790, %r787, %r1408;
	add.s32 	%r791, %r790, %r789;
	add.s32 	%r1408, %r791, 864026624;
	bra.uni 	$L__BB23_591;
$L__BB23_589:
	shl.b32 	%r781, %r265, 13;
	or.b32 	%r782, %r1408, %r781;
	or.b32 	%r1408, %r782, 2139095040;
	bra.uni 	$L__BB23_591;
$L__BB23_590:
	shl.b32 	%r792, %r266, 23;
	shl.b32 	%r793, %r267, 13;
	or.b32 	%r794, %r792, %r793;
	add.s32 	%r795, %r794, %r1408;
	add.s32 	%r1408, %r795, 939524096;
$L__BB23_591:
	cvt.f64.f32 	%rd914, %r1408;
$L__BB23_592:
	mul.rn.f64 	%rd926, %rd928, %rd146;
	@%p677 bra 	$L__BB23_616;
	shr.u64 	%rd154, %rd926, 48;
	cvt.u32.u64 	%r796, %rd154;
	and.b32 	%r268, %r796, 32768;
	shr.u64 	%rd493, %rd926, 52;
	cvt.u32.u64 	%r797, %rd493;
	and.b32 	%r269, %r797, 2047;
	setp.eq.b32 	%p315, %r269, 0;
	@%p315 bra 	$L__BB23_596;
	and.b64 	%rd153, %rd926, 4503599627370495;
	setp.eq.b32 	%p314, %r1360, 12;
	selp.b32 	%r270, 11, 8, %p314;
	selp.b32 	%r272, 31744, 32640, %p314;
	setp.ne.b32 	%p316, %r269, 2047;
	@%p316 bra 	$L__BB23_597;
	setp.eq.b64 	%p317, %rd153, 0;
	add.s32 	%r798, %r270, -2;
	mov.b32 	%r799, 1;
	shl.b32 	%r800, %r799, %r798;
	selp.b32 	%r801, 0, %r800, %p317;
	or.b32 	%r802, %r801, %r272;
	or.b32 	%r803, %r802, %r268;
	cvt.u16.u32 	%rs25, %r803;
	bra.uni 	$L__BB23_607;
$L__BB23_596:
	cvt.u16.u32 	%rs25, %r268;
	bra.uni 	$L__BB23_607;
$L__BB23_597:
	selp.b32 	%r804, -14, -126, %p314;
	add.s32 	%r273, %r269, -1023;
	or.b64 	%rd155, %rd153, 4503599627370496;
	setp.ge.s32 	%p318, %r273, %r804;
	@%p318 bra 	$L__BB23_603;
	and.b64 	%rd156, %rd154, 32768;
	selp.b32 	%r814, 28, -81, %p314;
	sub.s32 	%r274, %r814, %r273;
	setp.gt.s32 	%p326, %r274, 0;
	@%p326 bra 	$L__BB23_600;
	bra.uni 	$L__BB23_599;
$L__BB23_600:
	setp.gt.u32 	%p327, %r274, 63;
	mov.b64 	%rd925, 0;
	@%p327 bra 	$L__BB23_602;
	shr.u64 	%rd507, %rd155, %r274;
	mov.b64 	%rd508, -1;
	shl.b64 	%rd509, %rd508, %r274;
	not.b64 	%rd510, %rd509;
	and.b64 	%rd511, %rd155, %rd510;
	add.s32 	%r815, %r274, -1;
	mov.b64 	%rd512, 1;
	shl.b64 	%rd513, %rd512, %r815;
	setp.gt.u64 	%p328, %rd511, %rd513;
	setp.eq.b64 	%p329, %rd511, %rd513;
	and.b64 	%rd514, %rd507, 1;
	setp.ne.b64 	%p330, %rd514, 0;
	and.pred 	%p331, %p329, %p330;
	or.pred 	%p332, %p328, %p331;
	selp.b64 	%rd515, 1, 0, %p332;
	add.s64 	%rd925, %rd507, %rd515;
	bra.uni 	$L__BB23_602;
$L__BB23_603:
	selp.b32 	%r271, 15, 127, %p314;
	sub.s32 	%r805, 53, %r270;
	shr.u64 	%rd494, %rd155, %r805;
	mov.b64 	%rd495, -1;
	shl.b64 	%rd496, %rd495, %r805;
	not.b64 	%rd497, %rd496;
	and.b64 	%rd498, %rd926, %rd497;
	sub.s32 	%r806, 52, %r270;
	mov.b64 	%rd499, 1;
	shl.b64 	%rd500, %rd499, %r806;
	setp.gt.u64 	%p319, %rd498, %rd500;
	setp.eq.b64 	%p320, %rd498, %rd500;
	and.b64 	%rd501, %rd494, 1;
	setp.ne.b64 	%p321, %rd501, 0;
	and.pred 	%p322, %p320, %p321;
	or.pred 	%p323, %p319, %p322;
)QPTX";
        result += R"QPTX(
	selp.b64 	%rd502, 1, 0, %p323;
	add.s64 	%rd157, %rd494, %rd502;
	shl.b64 	%rd158, %rd499, %r270;
	setp.eq.b64 	%p324, %rd157, %rd158;
	add.s32 	%r807, %r269, -1022;
	selp.b32 	%r275, %r807, %r273, %p324;
	setp.le.s32 	%p325, %r275, %r271;
	@%p325 bra 	$L__BB23_605;
	or.b32 	%r1409, %r268, %r272;
	bra.uni 	$L__BB23_606;
$L__BB23_605:
	selp.b32 	%r808, 1, 0, %p324;
	shr.u64 	%rd503, %rd157, %r808;
	add.s32 	%r809, %r275, %r271;
	add.s32 	%r810, %r270, -1;
	shl.b32 	%r811, %r809, %r810;
	shl.b64 	%rd504, %rd495, %r810;
	not.b64 	%rd505, %rd504;
	and.b64 	%rd506, %rd503, %rd505;
	cvt.u32.u64 	%r812, %rd506;
	or.b32 	%r813, %r811, %r812;
	or.b32 	%r1409, %r813, %r268;
$L__BB23_606:
	cvt.u16.u32 	%rs25, %r1409;
	bra.uni 	$L__BB23_607;
$L__BB23_407:
	neg.s32 	%r520, %r186;
	shl.b64 	%rd913, %rd105, %r520;
$L__BB23_410:
	or.b64 	%rd324, %rd913, %rd106;
	cvt.u16.u64 	%rs17, %rd324;
$L__BB23_415:
	setp.ne.b32 	%p149, %r1360, 13;
	cvt.u32.u16 	%r188, %rs17;
	@%p149 bra 	$L__BB23_417;
	shl.b32 	%r1394, %r188, 16;
	bra.uni 	$L__BB23_423;
$L__BB23_417:
	cvt.s32.s16 	%r521, %rs17;
	and.b32 	%r1394, %r521, -2147483648;
	bfe.u32 	%r189, %r188, 10, 5;
	setp.eq.b32 	%p150, %r189, 31;
	@%p150 bra 	$L__BB23_421;
	and.b32 	%r190, %r188, 1023;
	setp.ne.b32 	%p151, %r189, 0;
	@%p151 bra 	$L__BB23_422;
	setp.eq.b32 	%p152, %r190, 0;
	@%p152 bra 	$L__BB23_423;
	clz.b32 	%r524, %r190;
	xor.b32 	%r525, %r524, 31;
	sub.s32 	%r526, 9, %r525;
	shl.b32 	%r527, %r188, %r526;
	shl.b32 	%r528, %r525, 23;
	shl.b32 	%r529, %r527, 14;
	and.b32 	%r530, %r529, 8372224;
	add.s32 	%r531, %r528, %r1394;
	add.s32 	%r532, %r531, %r530;
	add.s32 	%r1394, %r532, 864026624;
	bra.uni 	$L__BB23_423;
$L__BB23_421:
	shl.b32 	%r522, %r188, 13;
	or.b32 	%r523, %r1394, %r522;
	or.b32 	%r1394, %r523, 2139095040;
	bra.uni 	$L__BB23_423;
$L__BB23_422:
	shl.b32 	%r533, %r189, 23;
	shl.b32 	%r534, %r190, 13;
	or.b32 	%r535, %r533, %r534;
	add.s32 	%r536, %r535, %r1394;
	add.s32 	%r1394, %r536, 939524096;
$L__BB23_423:
	cvt.f64.f32 	%rd914, %r1394;
$L__BB23_424:
	mul.rn.f64 	%rd916, %rd928, %rd95;
	@%p677 bra 	$L__BB23_448;
	shr.u64 	%rd110, %rd916, 48;
	cvt.u32.u64 	%r537, %rd110;
	and.b32 	%r191, %r537, 32768;
	shr.u64 	%rd325, %rd916, 52;
	cvt.u32.u64 	%r538, %rd325;
	and.b32 	%r192, %r538, 2047;
	setp.eq.b32 	%p154, %r192, 0;
	@%p154 bra 	$L__BB23_428;
	and.b64 	%rd109, %rd916, 4503599627370495;
	setp.eq.b32 	%p153, %r1360, 12;
	selp.b32 	%r193, 11, 8, %p153;
	selp.b32 	%r195, 31744, 32640, %p153;
	setp.ne.b32 	%p155, %r192, 2047;
	@%p155 bra 	$L__BB23_429;
	setp.eq.b64 	%p156, %rd109, 0;
	add.s32 	%r539, %r193, -2;
	mov.b32 	%r540, 1;
	shl.b32 	%r541, %r540, %r539;
	selp.b32 	%r542, 0, %r541, %p156;
	or.b32 	%r543, %r542, %r195;
	or.b32 	%r544, %r543, %r191;
	cvt.u16.u32 	%rs18, %r544;
	bra.uni 	$L__BB23_439;
$L__BB23_428:
	cvt.u16.u32 	%rs18, %r191;
	bra.uni 	$L__BB23_439;
$L__BB23_429:
	selp.b32 	%r545, -14, -126, %p153;
	add.s32 	%r196, %r192, -1023;
	or.b64 	%rd111, %rd109, 4503599627370496;
	setp.ge.s32 	%p157, %r196, %r545;
	@%p157 bra 	$L__BB23_435;
	and.b64 	%rd112, %rd110, 32768;
	selp.b32 	%r555, 28, -81, %p153;
	sub.s32 	%r197, %r555, %r196;
	setp.gt.s32 	%p165, %r197, 0;
	@%p165 bra 	$L__BB23_432;
	bra.uni 	$L__BB23_431;
$L__BB23_432:
	setp.gt.u32 	%p166, %r197, 63;
	mov.b64 	%rd915, 0;
	@%p166 bra 	$L__BB23_434;
	shr.u64 	%rd339, %rd111, %r197;
	mov.b64 	%rd340, -1;
	shl.b64 	%rd341, %rd340, %r197;
	not.b64 	%rd342, %rd341;
	and.b64 	%rd343, %rd111, %rd342;
	add.s32 	%r556, %r197, -1;
	mov.b64 	%rd344, 1;
	shl.b64 	%rd345, %rd344, %r556;
	setp.gt.u64 	%p167, %rd343, %rd345;
	setp.eq.b64 	%p168, %rd343, %rd345;
	and.b64 	%rd346, %rd339, 1;
	setp.ne.b64 	%p169, %rd346, 0;
	and.pred 	%p170, %p168, %p169;
	or.pred 	%p171, %p167, %p170;
	selp.b64 	%rd347, 1, 0, %p171;
	add.s64 	%rd915, %rd339, %rd347;
	bra.uni 	$L__BB23_434;
$L__BB23_435:
	selp.b32 	%r194, 15, 127, %p153;
	sub.s32 	%r546, 53, %r193;
	shr.u64 	%rd326, %rd111, %r546;
	mov.b64 	%rd327, -1;
	shl.b64 	%rd328, %rd327, %r546;
	not.b64 	%rd329, %rd328;
	and.b64 	%rd330, %rd916, %rd329;
	sub.s32 	%r547, 52, %r193;
	mov.b64 	%rd331, 1;
	shl.b64 	%rd332, %rd331, %r547;
	setp.gt.u64 	%p158, %rd330, %rd332;
	setp.eq.b64 	%p159, %rd330, %rd332;
	and.b64 	%rd333, %rd326, 1;
	setp.ne.b64 	%p160, %rd333, 0;
	and.pred 	%p161, %p159, %p160;
	or.pred 	%p162, %p158, %p161;
	selp.b64 	%rd334, 1, 0, %p162;
	add.s64 	%rd113, %rd326, %rd334;
	shl.b64 	%rd114, %rd331, %r193;
	setp.eq.b64 	%p163, %rd113, %rd114;
	add.s32 	%r548, %r192, -1022;
	selp.b32 	%r198, %r548, %r196, %p163;
	setp.le.s32 	%p164, %r198, %r194;
	@%p164 bra 	$L__BB23_437;
	or.b32 	%r1395, %r191, %r195;
	bra.uni 	$L__BB23_438;
$L__BB23_437:
	selp.b32 	%r549, 1, 0, %p163;
	shr.u64 	%rd335, %rd113, %r549;
	add.s32 	%r550, %r198, %r194;
	add.s32 	%r551, %r193, -1;
	shl.b32 	%r552, %r550, %r551;
	shl.b64 	%rd336, %rd327, %r551;
	not.b64 	%rd337, %rd336;
	and.b64 	%rd338, %rd335, %rd337;
	cvt.u32.u64 	%r553, %rd338;
	or.b32 	%r554, %r552, %r553;
	or.b32 	%r1395, %r554, %r191;
$L__BB23_438:
	cvt.u16.u32 	%rs18, %r1395;
	bra.uni 	$L__BB23_439;
$L__BB23_599:
	neg.s32 	%r816, %r274;
	shl.b64 	%rd925, %rd155, %r816;
$L__BB23_602:
	or.b64 	%rd516, %rd925, %rd156;
	cvt.u16.u64 	%rs25, %rd516;
$L__BB23_607:
	setp.ne.b32 	%p333, %r1360, 13;
	cvt.u32.u16 	%r276, %rs25;
	@%p333 bra 	$L__BB23_609;
	shl.b32 	%r1410, %r276, 16;
	bra.uni 	$L__BB23_615;
$L__BB23_609:
	cvt.s32.s16 	%r817, %rs25;
	and.b32 	%r1410, %r817, -2147483648;
	bfe.u32 	%r277, %r276, 10, 5;
	setp.eq.b32 	%p334, %r277, 31;
	@%p334 bra 	$L__BB23_613;
	and.b32 	%r278, %r276, 1023;
	setp.ne.b32 	%p335, %r277, 0;
	@%p335 bra 	$L__BB23_614;
	setp.eq.b32 	%p336, %r278, 0;
	@%p336 bra 	$L__BB23_615;
	clz.b32 	%r820, %r278;
	xor.b32 	%r821, %r820, 31;
	sub.s32 	%r822, 9, %r821;
	shl.b32 	%r823, %r276, %r822;
	shl.b32 	%r824, %r821, 23;
	shl.b32 	%r825, %r823, 14;
	and.b32 	%r826, %r825, 8372224;
	add.s32 	%r827, %r824, %r1410;
	add.s32 	%r828, %r827, %r826;
	add.s32 	%r1410, %r828, 864026624;
	bra.uni 	$L__BB23_615;
$L__BB23_613:
	shl.b32 	%r818, %r276, 13;
	or.b32 	%r819, %r1410, %r818;
	or.b32 	%r1410, %r819, 2139095040;
	bra.uni 	$L__BB23_615;
$L__BB23_614:
	shl.b32 	%r829, %r277, 23;
	shl.b32 	%r830, %r278, 13;
	or.b32 	%r831, %r829, %r830;
	add.s32 	%r832, %r831, %r1410;
	add.s32 	%r1410, %r832, 939524096;
$L__BB23_615:
	cvt.f64.f32 	%rd926, %r1410;
$L__BB23_616:
	sub.rn.f64 	%rd929, %rd926, %rd139;
	mov.pred 	%p678, 0;
	@%p677 bra 	$L__BB23_640;
	shr.u64 	%rd160, %rd929, 48;
	cvt.u32.u64 	%r833, %rd160;
	and.b32 	%r279, %r833, 32768;
	shr.u64 	%rd517, %rd929, 52;
	cvt.u32.u64 	%r834, %rd517;
	and.b32 	%r280, %r834, 2047;
	setp.eq.b32 	%p338, %r280, 0;
	@%p338 bra 	$L__BB23_620;
	and.b64 	%rd159, %rd929, 4503599627370495;
	setp.eq.b32 	%p337, %r1360, 12;
	selp.b32 	%r281, 11, 8, %p337;
	selp.b32 	%r283, 31744, 32640, %p337;
	setp.ne.b32 	%p339, %r280, 2047;
	@%p339 bra 	$L__BB23_621;
	setp.eq.b64 	%p340, %rd159, 0;
	add.s32 	%r835, %r281, -2;
	mov.b32 	%r836, 1;
	shl.b32 	%r837, %r836, %r835;
	selp.b32 	%r838, 0, %r837, %p340;
	or.b32 	%r839, %r838, %r283;
	or.b32 	%r840, %r839, %r279;
	cvt.u16.u32 	%rs26, %r840;
	bra.uni 	$L__BB23_631;
$L__BB23_620:
	cvt.u16.u32 	%rs26, %r279;
	bra.uni 	$L__BB23_631;
$L__BB23_621:
	selp.b32 	%r841, -14, -126, %p337;
	add.s32 	%r284, %r280, -1023;
	or.b64 	%rd161, %rd159, 4503599627370496;
	setp.ge.s32 	%p341, %r284, %r841;
	@%p341 bra 	$L__BB23_627;
	and.b64 	%rd162, %rd160, 32768;
	selp.b32 	%r851, 28, -81, %p337;
	sub.s32 	%r285, %r851, %r284;
	setp.gt.s32 	%p349, %r285, 0;
	@%p349 bra 	$L__BB23_624;
	bra.uni 	$L__BB23_623;
$L__BB23_624:
	setp.gt.u32 	%p350, %r285, 63;
	mov.b64 	%rd927, 0;
	@%p350 bra 	$L__BB23_626;
	shr.u64 	%rd531, %rd161, %r285;
	mov.b64 	%rd532, -1;
	shl.b64 	%rd533, %rd532, %r285;
	not.b64 	%rd534, %rd533;
	and.b64 	%rd535, %rd161, %rd534;
	add.s32 	%r852, %r285, -1;
	mov.b64 	%rd536, 1;
	shl.b64 	%rd537, %rd536, %r852;
	setp.gt.u64 	%p351, %rd535, %rd537;
	setp.eq.b64 	%p352, %rd535, %rd537;
	and.b64 	%rd538, %rd531, 1;
	setp.ne.b64 	%p353, %rd538, 0;
	and.pred 	%p354, %p352, %p353;
	or.pred 	%p355, %p351, %p354;
	selp.b64 	%rd539, 1, 0, %p355;
	add.s64 	%rd927, %rd531, %rd539;
	bra.uni 	$L__BB23_626;
$L__BB23_627:
	selp.b32 	%r282, 15, 127, %p337;
	sub.s32 	%r842, 53, %r281;
	shr.u64 	%rd518, %rd161, %r842;
	mov.b64 	%rd519, -1;
	shl.b64 	%rd520, %rd519, %r842;
	not.b64 	%rd521, %rd520;
	and.b64 	%rd522, %rd929, %rd521;
	sub.s32 	%r843, 52, %r281;
	mov.b64 	%rd523, 1;
	shl.b64 	%rd524, %rd523, %r843;
	setp.gt.u64 	%p342, %rd522, %rd524;
	setp.eq.b64 	%p343, %rd522, %rd524;
	and.b64 	%rd525, %rd518, 1;
	setp.ne.b64 	%p344, %rd525, 0;
	and.pred 	%p345, %p343, %p344;
	or.pred 	%p346, %p342, %p345;
	selp.b64 	%rd526, 1, 0, %p346;
	add.s64 	%rd163, %rd518, %rd526;
	shl.b64 	%rd164, %rd523, %r281;
	setp.eq.b64 	%p347, %rd163, %rd164;
	add.s32 	%r844, %r280, -1022;
	selp.b32 	%r286, %r844, %r284, %p347;
	setp.le.s32 	%p348, %r286, %r282;
	@%p348 bra 	$L__BB23_629;
	or.b32 	%r1411, %r279, %r283;
	bra.uni 	$L__BB23_630;
$L__BB23_629:
	selp.b32 	%r845, 1, 0, %p347;
	shr.u64 	%rd527, %rd163, %r845;
	add.s32 	%r846, %r286, %r282;
	add.s32 	%r847, %r281, -1;
	shl.b32 	%r848, %r846, %r847;
	shl.b64 	%rd528, %rd519, %r847;
	not.b64 	%rd529, %rd528;
	and.b64 	%rd530, %rd527, %rd529;
	cvt.u32.u64 	%r849, %rd530;
	or.b32 	%r850, %r848, %r849;
	or.b32 	%r1411, %r850, %r279;
$L__BB23_630:
	cvt.u16.u32 	%rs26, %r1411;
	bra.uni 	$L__BB23_631;
$L__BB23_431:
	neg.s32 	%r557, %r197;
	shl.b64 	%rd915, %rd111, %r557;
$L__BB23_434:
	or.b64 	%rd348, %rd915, %rd112;
	cvt.u16.u64 	%rs18, %rd348;
$L__BB23_439:
	setp.ne.b32 	%p172, %r1360, 13;
	cvt.u32.u16 	%r199, %rs18;
	@%p172 bra 	$L__BB23_441;
	shl.b32 	%r1396, %r199, 16;
	bra.uni 	$L__BB23_447;
$L__BB23_441:
	cvt.s32.s16 	%r558, %rs18;
	and.b32 	%r1396, %r558, -2147483648;
	bfe.u32 	%r200, %r199, 10, 5;
	setp.eq.b32 	%p173, %r200, 31;
	@%p173 bra 	$L__BB23_445;
	and.b32 	%r201, %r199, 1023;
	setp.ne.b32 	%p174, %r200, 0;
	@%p174 bra 	$L__BB23_446;
	setp.eq.b32 	%p175, %r201, 0;
	@%p175 bra 	$L__BB23_447;
	clz.b32 	%r561, %r201;
	xor.b32 	%r562, %r561, 31;
	sub.s32 	%r563, 9, %r562;
	shl.b32 	%r564, %r199, %r563;
	shl.b32 	%r565, %r562, 23;
	shl.b32 	%r566, %r564, 14;
	and.b32 	%r567, %r566, 8372224;
	add.s32 	%r568, %r565, %r1396;
	add.s32 	%r569, %r568, %r567;
	add.s32 	%r1396, %r569, 864026624;
	bra.uni 	$L__BB23_447;
$L__BB23_445:
	shl.b32 	%r559, %r199, 13;
	or.b32 	%r560, %r1396, %r559;
	or.b32 	%r1396, %r560, 2139095040;
	bra.uni 	$L__BB23_447;
$L__BB23_446:
	shl.b32 	%r570, %r200, 23;
	shl.b32 	%r571, %r201, 13;
	or.b32 	%r572, %r570, %r571;
	add.s32 	%r573, %r572, %r1396;
	add.s32 	%r1396, %r573, 939524096;
$L__BB23_447:
	cvt.f64.f32 	%rd916, %r1396;
$L__BB23_448:
	sub.rn.f64 	%rd929, %rd96, %rd916;
	mov.pred 	%p678, 0;
	@%p677 bra 	$L__BB23_640;
	shr.u64 	%rd116, %rd929, 48;
	cvt.u32.u64 	%r574, %rd116;
	and.b32 	%r202, %r574, 32768;
	shr.u64 	%rd349, %rd929, 52;
	cvt.u32.u64 	%r575, %rd349;
	and.b32 	%r203, %r575, 2047;
	setp.eq.b32 	%p177, %r203, 0;
	@%p177 bra 	$L__BB23_452;
	and.b64 	%rd115, %rd929, 4503599627370495;
	setp.eq.b32 	%p176, %r1360, 12;
	selp.b32 	%r204, 11, 8, %p176;
	selp.b32 	%r206, 31744, 32640, %p176;
	setp.ne.b32 	%p178, %r203, 2047;
	@%p178 bra 	$L__BB23_453;
	setp.eq.b64 	%p179, %rd115, 0;
	add.s32 	%r576, %r204, -2;
	mov.b32 	%r577, 1;
	shl.b32 	%r578, %r577, %r576;
	selp.b32 	%r579, 0, %r578, %p179;
	or.b32 	%r580, %r579, %r206;
	or.b32 	%r581, %r580, %r202;
	cvt.u16.u32 	%rs19, %r581;
	bra.uni 	$L__BB23_463;
$L__BB23_452:
	cvt.u16.u32 	%rs19, %r202;
	bra.uni 	$L__BB23_463;
$L__BB23_453:
	selp.b32 	%r582, -14, -126, %p176;
	add.s32 	%r207, %r203, -1023;
	or.b64 	%rd117, %rd115, 4503599627370496;
	setp.ge.s32 	%p180, %r207, %r582;
	@%p180 bra 	$L__BB23_459;
	and.b64 	%rd118, %rd116, 32768;
	selp.b32 	%r592, 28, -81, %p176;
	sub.s32 	%r208, %r592, %r207;
	setp.gt.s32 	%p188, %r208, 0;
	@%p188 bra 	$L__BB23_456;
	bra.uni 	$L__BB23_455;
$L__BB23_456:
	setp.gt.u32 	%p189, %r208, 63;
	mov.b64 	%rd917, 0;
	@%p189 bra 	$L__BB23_458;
	shr.u64 	%rd363, %rd117, %r208;
	mov.b64 	%rd364, -1;
	shl.b64 	%rd365, %rd364, %r208;
	not.b64 	%rd366, %rd365;
	and.b64 	%rd367, %rd117, %rd366;
	add.s32 	%r593, %r208, -1;
	mov.b64 	%rd368, 1;
	shl.b64 	%rd369, %rd368, %r593;
	setp.gt.u64 	%p190, %rd367, %rd369;
	setp.eq.b64 	%p191, %rd367, %rd369;
	and.b64 	%rd370, %rd363, 1;
	setp.ne.b64 	%p192, %rd370, 0;
	and.pred 	%p193, %p191, %p192;
	or.pred 	%p194, %p190, %p193;
	selp.b64 	%rd371, 1, 0, %p194;
	add.s64 	%rd917, %rd363, %rd371;
	bra.uni 	$L__BB23_458;
$L__BB23_459:
	selp.b32 	%r205, 15, 127, %p176;
	sub.s32 	%r583, 53, %r204;
	shr.u64 	%rd350, %rd117, %r583;
	mov.b64 	%rd351, -1;
	shl.b64 	%rd352, %rd351, %r583;
	not.b64 	%rd353, %rd352;
	and.b64 	%rd354, %rd929, %rd353;
	sub.s32 	%r584, 52, %r204;
	mov.b64 	%rd355, 1;
	shl.b64 	%rd356, %rd355, %r584;
	setp.gt.u64 	%p181, %rd354, %rd356;
	setp.eq.b64 	%p182, %rd354, %rd356;
	and.b64 	%rd357, %rd350, 1;
	setp.ne.b64 	%p183, %rd357, 0;
	and.pred 	%p184, %p182, %p183;
	or.pred 	%p185, %p181, %p184;
	selp.b64 	%rd358, 1, 0, %p185;
	add.s64 	%rd119, %rd350, %rd358;
	shl.b64 	%rd120, %rd355, %r204;
	setp.eq.b64 	%p186, %rd119, %rd120;
	add.s32 	%r585, %r203, -1022;
	selp.b32 	%r209, %r585, %r207, %p186;
	setp.le.s32 	%p187, %r209, %r205;
	@%p187 bra 	$L__BB23_461;
	or.b32 	%r1397, %r202, %r206;
	bra.uni 	$L__BB23_462;
$L__BB23_461:
	selp.b32 	%r586, 1, 0, %p186;
	shr.u64 	%rd359, %rd119, %r586;
	add.s32 	%r587, %r209, %r205;
	add.s32 	%r588, %r204, -1;
	shl.b32 	%r589, %r587, %r588;
	shl.b64 	%rd360, %rd351, %r588;
	not.b64 	%rd361, %rd360;
	and.b64 	%rd362, %rd359, %rd361;
	cvt.u32.u64 	%r590, %rd362;
	or.b32 	%r591, %r589, %r590;
	or.b32 	%r1397, %r591, %r202;
$L__BB23_462:
	cvt.u16.u32 	%rs19, %r1397;
	bra.uni 	$L__BB23_463;
$L__BB23_623:
	neg.s32 	%r853, %r285;
	shl.b64 	%rd927, %rd161, %r853;
$L__BB23_626:
	or.b64 	%rd540, %rd927, %rd162;
	cvt.u16.u64 	%rs26, %rd540;
$L__BB23_631:
	setp.ne.b32 	%p356, %r1360, 13;
	cvt.u32.u16 	%r287, %rs26;
	@%p356 bra 	$L__BB23_633;
	shl.b32 	%r1412, %r287, 16;
	bra.uni 	$L__BB23_639;
$L__BB23_633:
	cvt.s32.s16 	%r854, %rs26;
	and.b32 	%r1412, %r854, -2147483648;
	bfe.u32 	%r288, %r287, 10, 5;
	setp.eq.b32 	%p357, %r288, 31;
	@%p357 bra 	$L__BB23_637;
	and.b32 	%r289, %r287, 1023;
	setp.ne.b32 	%p358, %r288, 0;
	@%p358 bra 	$L__BB23_638;
	setp.eq.b32 	%p359, %r289, 0;
	@%p359 bra 	$L__BB23_639;
	clz.b32 	%r857, %r289;
	xor.b32 	%r858, %r857, 31;
	sub.s32 	%r859, 9, %r858;
	shl.b32 	%r860, %r287, %r859;
	shl.b32 	%r861, %r858, 23;
	shl.b32 	%r862, %r860, 14;
	and.b32 	%r863, %r862, 8372224;
	add.s32 	%r864, %r861, %r1412;
	add.s32 	%r865, %r864, %r863;
	add.s32 	%r1412, %r865, 864026624;
	bra.uni 	$L__BB23_639;
$L__BB23_637:
	shl.b32 	%r855, %r287, 13;
	or.b32 	%r856, %r1412, %r855;
	or.b32 	%r1412, %r856, 2139095040;
	bra.uni 	$L__BB23_639;
$L__BB23_638:
	shl.b32 	%r866, %r288, 23;
	shl.b32 	%r867, %r289, 13;
	or.b32 	%r868, %r866, %r867;
	add.s32 	%r869, %r868, %r1412;
	add.s32 	%r1412, %r869, 939524096;
$L__BB23_639:
	cvt.f64.f32 	%rd929, %r1412;
	mov.pred 	%p678, -1;
	bra.uni 	$L__BB23_640;
$L__BB23_455:
	neg.s32 	%r594, %r208;
	shl.b64 	%rd917, %rd117, %r594;
$L__BB23_458:
	or.b64 	%rd372, %rd917, %rd118;
	cvt.u16.u64 	%rs19, %rd372;
$L__BB23_463:
	setp.ne.b32 	%p195, %r1360, 13;
	cvt.u32.u16 	%r210, %rs19;
	@%p195 bra 	$L__BB23_465;
	shl.b32 	%r1398, %r210, 16;
	bra.uni 	$L__BB23_471;
$L__BB23_465:
	cvt.s32.s16 	%r595, %rs19;
	and.b32 	%r1398, %r595, -2147483648;
	bfe.u32 	%r211, %r210, 10, 5;
	setp.eq.b32 	%p196, %r211, 31;
	@%p196 bra 	$L__BB23_469;
	and.b32 	%r212, %r210, 1023;
	setp.ne.b32 	%p197, %r211, 0;
	@%p197 bra 	$L__BB23_470;
	setp.eq.b32 	%p198, %r212, 0;
	@%p198 bra 	$L__BB23_471;
	clz.b32 	%r598, %r212;
	xor.b32 	%r599, %r598, 31;
	sub.s32 	%r600, 9, %r599;
	shl.b32 	%r601, %r210, %r600;
	shl.b32 	%r602, %r599, 23;
	shl.b32 	%r603, %r601, 14;
	and.b32 	%r604, %r603, 8372224;
	add.s32 	%r605, %r602, %r1398;
	add.s32 	%r606, %r605, %r604;
	add.s32 	%r1398, %r606, 864026624;
	bra.uni 	$L__BB23_471;
$L__BB23_469:
	shl.b32 	%r596, %r210, 13;
	or.b32 	%r597, %r1398, %r596;
	or.b32 	%r1398, %r597, 2139095040;
	bra.uni 	$L__BB23_471;
$L__BB23_470:
	shl.b32 	%r607, %r211, 23;
	shl.b32 	%r608, %r212, 13;
	or.b32 	%r609, %r607, %r608;
	add.s32 	%r610, %r609, %r1398;
	add.s32 	%r1398, %r610, 939524096;
$L__BB23_471:
	cvt.f64.f32 	%rd929, %r1398;
	mov.pred 	%p678, -1;
$L__BB23_640:
	abs.f64 	%rd541, %rd928;
	setp.ne.f64 	%p360, %rd541, 0d7FF0000000000000;
	abs.f64 	%rd542, %rd910;
	setp.ne.f64 	%p361, %rd542, 0d7FF0000000000000;
	and.pred 	%p362, %p360, %p361;
	abs.f64 	%rd543, %rd914;
	setp.ne.f64 	%p363, %rd543, 0d7FF0000000000000;
	and.pred 	%p364, %p362, %p363;
	abs.f64 	%rd544, %rd929;
	setp.ne.f64 	%p365, %rd544, 0d7FF0000000000000;
	div.rn.f64 	%rd933, %rd914, %rd910;
	not.pred 	%p366, %p678;
	@%p366 bra 	$L__BB23_664;
	shr.u64 	%rd166, %rd933, 48;
	cvt.u32.u64 	%r870, %rd166;
	and.b32 	%r290, %r870, 32768;
	shr.u64 	%rd545, %rd933, 52;
	cvt.u32.u64 	%r871, %rd545;
	and.b32 	%r291, %r871, 2047;
	setp.eq.b32 	%p368, %r291, 0;
	@%p368 bra 	$L__BB23_644;
	and.b64 	%rd165, %rd933, 4503599627370495;
	setp.eq.b32 	%p367, %r1360, 12;
	selp.b32 	%r292, 11, 8, %p367;
	selp.b32 	%r294, 31744, 32640, %p367;
	setp.ne.b32 	%p369, %r291, 2047;
	@%p369 bra 	$L__BB23_645;
	setp.eq.b64 	%p370, %rd165, 0;
	add.s32 	%r872, %r292, -2;
	mov.b32 	%r873, 1;
	shl.b32 	%r874, %r873, %r872;
	selp.b32 	%r875, 0, %r874, %p370;
	or.b32 	%r876, %r875, %r294;
	or.b32 	%r877, %r876, %r290;
	cvt.u16.u32 	%rs27, %r877;
	bra.uni 	$L__BB23_655;
$L__BB23_644:
	cvt.u16.u32 	%rs27, %r290;
	bra.uni 	$L__BB23_655;
$L__BB23_645:
	selp.b32 	%r878, -14, -126, %p367;
	add.s32 	%r295, %r291, -1023;
	or.b64 	%rd167, %rd165, 4503599627370496;
	setp.ge.s32 	%p371, %r295, %r878;
	@%p371 bra 	$L__BB23_651;
	and.b64 	%rd168, %rd166, 32768;
	selp.b32 	%r888, 28, -81, %p367;
	sub.s32 	%r296, %r888, %r295;
	setp.gt.s32 	%p379, %r296, 0;
	@%p379 bra 	$L__BB23_648;
	bra.uni 	$L__BB23_647;
$L__BB23_648:
	setp.gt.u32 	%p380, %r296, 63;
	mov.b64 	%rd930, 0;
	@%p380 bra 	$L__BB23_650;
	shr.u64 	%rd559, %rd167, %r296;
	mov.b64 	%rd560, -1;
	shl.b64 	%rd561, %rd560, %r296;
	not.b64 	%rd562, %rd561;
	and.b64 	%rd563, %rd167, %rd562;
	add.s32 	%r889, %r296, -1;
	mov.b64 	%rd564, 1;
	shl.b64 	%rd565, %rd564, %r889;
	setp.gt.u64 	%p381, %rd563, %rd565;
	setp.eq.b64 	%p382, %rd563, %rd565;
	and.b64 	%rd566, %rd559, 1;
	setp.ne.b64 	%p383, %rd566, 0;
	and.pred 	%p384, %p382, %p383;
	or.pred 	%p385, %p381, %p384;
	selp.b64 	%rd567, 1, 0, %p385;
	add.s64 	%rd930, %rd559, %rd567;
	bra.uni 	$L__BB23_650;
$L__BB23_651:
	selp.b32 	%r293, 15, 127, %p367;
	sub.s32 	%r879, 53, %r292;
	shr.u64 	%rd546, %rd167, %r879;
	mov.b64 	%rd547, -1;
	shl.b64 	%rd548, %rd547, %r879;
	not.b64 	%rd549, %rd548;
	and.b64 	%rd550, %rd933, %rd549;
	sub.s32 	%r880, 52, %r292;
	mov.b64 	%rd551, 1;
	shl.b64 	%rd552, %rd551, %r880;
	setp.gt.u64 	%p372, %rd550, %rd552;
	setp.eq.b64 	%p373, %rd550, %rd552;
	and.b64 	%rd553, %rd546, 1;
	setp.ne.b64 	%p374, %rd553, 0;
	and.pred 	%p375, %p373, %p374;
	or.pred 	%p376, %p372, %p375;
	selp.b64 	%rd554, 1, 0, %p376;
	add.s64 	%rd169, %rd546, %rd554;
	shl.b64 	%rd170, %rd551, %r292;
	setp.eq.b64 	%p377, %rd169, %rd170;
	add.s32 	%r881, %r291, -1022;
	selp.b32 	%r297, %r881, %r295, %p377;
	setp.le.s32 	%p378, %r297, %r293;
	@%p378 bra 	$L__BB23_653;
	or.b32 	%r1413, %r290, %r294;
	bra.uni 	$L__BB23_654;
$L__BB23_653:
	selp.b32 	%r882, 1, 0, %p377;
	shr.u64 	%rd555, %rd169, %r882;
	add.s32 	%r883, %r297, %r293;
	add.s32 	%r884, %r292, -1;
	shl.b32 	%r885, %r883, %r884;
	shl.b64 	%rd556, %rd547, %r884;
	not.b64 	%rd557, %rd556;
	and.b64 	%rd558, %rd555, %rd557;
	cvt.u32.u64 	%r886, %rd558;
	or.b32 	%r887, %r885, %r886;
	or.b32 	%r1413, %r887, %r290;
$L__BB23_654:
	cvt.u16.u32 	%rs27, %r1413;
	bra.uni 	$L__BB23_655;
$L__BB23_647:
	neg.s32 	%r890, %r296;
	shl.b64 	%rd930, %rd167, %r890;
$L__BB23_650:
	or.b64 	%rd568, %rd930, %rd168;
	cvt.u16.u64 	%rs27, %rd568;
$L__BB23_655:
	setp.ne.b32 	%p386, %r1360, 13;
	cvt.u32.u16 	%r298, %rs27;
	@%p386 bra 	$L__BB23_657;
	shl.b32 	%r1414, %r298, 16;
	bra.uni 	$L__BB23_663;
$L__BB23_657:
	cvt.s32.s16 	%r891, %rs27;
	and.b32 	%r1414, %r891, -2147483648;
	bfe.u32 	%r299, %r298, 10, 5;
	setp.eq.b32 	%p387, %r299, 31;
	@%p387 bra 	$L__BB23_661;
	and.b32 	%r300, %r298, 1023;
	setp.ne.b32 	%p388, %r299, 0;
	@%p388 bra 	$L__BB23_662;
	setp.eq.b32 	%p389, %r300, 0;
	@%p389 bra 	$L__BB23_663;
	clz.b32 	%r894, %r300;
	xor.b32 	%r895, %r894, 31;
	sub.s32 	%r896, 9, %r895;
	shl.b32 	%r897, %r298, %r896;
	shl.b32 	%r898, %r895, 23;
	shl.b32 	%r899, %r897, 14;
	and.b32 	%r900, %r899, 8372224;
	add.s32 	%r901, %r898, %r1414;
	add.s32 	%r902, %r901, %r900;
	add.s32 	%r1414, %r902, 864026624;
	bra.uni 	$L__BB23_663;
$L__BB23_661:
	shl.b32 	%r892, %r298, 13;
	or.b32 	%r893, %r1414, %r892;
	or.b32 	%r1414, %r893, 2139095040;
	bra.uni 	$L__BB23_663;
$L__BB23_662:
	shl.b32 	%r903, %r299, 23;
	shl.b32 	%r904, %r300, 13;
	or.b32 	%r905, %r903, %r904;
	add.s32 	%r906, %r905, %r1414;
	add.s32 	%r1414, %r906, 939524096;
$L__BB23_663:
	cvt.f64.f32 	%rd933, %r1414;
$L__BB23_664:
	and.pred 	%p1, %p364, %p365;
	div.rn.f64 	%rd932, %rd929, %rd910;
	@%p366 bra 	$L__BB23_688;
	shr.u64 	%rd172, %rd932, 48;
	cvt.u32.u64 	%r907, %rd172;
	and.b32 	%r301, %r907, 32768;
	shr.u64 	%rd569, %rd932, 52;
	cvt.u32.u64 	%r908, %rd569;
	and.b32 	%r302, %r908, 2047;
	setp.eq.b32 	%p391, %r302, 0;
	@%p391 bra 	$L__BB23_668;
	and.b64 	%rd171, %rd932, 4503599627370495;
	setp.eq.b32 	%p390, %r1360, 12;
	selp.b32 	%r303, 11, 8, %p390;
	selp.b32 	%r305, 31744, 32640, %p390;
	setp.ne.b32 	%p392, %r302, 2047;
	@%p392 bra 	$L__BB23_669;
	setp.eq.b64 	%p393, %rd171, 0;
	add.s32 	%r909, %r303, -2;
	mov.b32 	%r910, 1;
	shl.b32 	%r911, %r910, %r909;
	selp.b32 	%r912, 0, %r911, %p393;
	or.b32 	%r913, %r912, %r305;
	or.b32 	%r914, %r913, %r301;
	cvt.u16.u32 	%rs28, %r914;
	bra.uni 	$L__BB23_679;
$L__BB23_668:
	cvt.u16.u32 	%rs28, %r301;
	bra.uni 	$L__BB23_679;
$L__BB23_669:
	selp.b32 	%r915, -14, -126, %p390;
	add.s32 	%r306, %r302, -1023;
	or.b64 	%rd173, %rd171, 4503599627370496;
	setp.ge.s32 	%p394, %r306, %r915;
	@%p394 bra 	$L__BB23_675;
	and.b64 	%rd174, %rd172, 32768;
	selp.b32 	%r925, 28, -81, %p390;
	sub.s32 	%r307, %r925, %r306;
	setp.gt.s32 	%p402, %r307, 0;
	@%p402 bra 	$L__BB23_672;
	bra.uni 	$L__BB23_671;
$L__BB23_672:
	setp.gt.u32 	%p403, %r307, 63;
	mov.b64 	%rd931, 0;
	@%p403 bra 	$L__BB23_674;
	shr.u64 	%rd583, %rd173, %r307;
	mov.b64 	%rd584, -1;
	shl.b64 	%rd585, %rd584, %r307;
	not.b64 	%rd586, %rd585;
	and.b64 	%rd587, %rd173, %rd586;
	add.s32 	%r926, %r307, -1;
	mov.b64 	%rd588, 1;
	shl.b64 	%rd589, %rd588, %r926;
	setp.gt.u64 	%p404, %rd587, %rd589;
	setp.eq.b64 	%p405, %rd587, %rd589;
	and.b64 	%rd590, %rd583, 1;
	setp.ne.b64 	%p406, %rd590, 0;
	and.pred 	%p407, %p405, %p406;
	or.pred 	%p408, %p404, %p407;
	selp.b64 	%rd591, 1, 0, %p408;
	add.s64 	%rd931, %rd583, %rd591;
	bra.uni 	$L__BB23_674;
$L__BB23_675:
	selp.b32 	%r304, 15, 127, %p390;
	sub.s32 	%r916, 53, %r303;
	shr.u64 	%rd570, %rd173, %r916;
	mov.b64 	%rd571, -1;
	shl.b64 	%rd572, %rd571, %r916;
	not.b64 	%rd573, %rd572;
	and.b64 	%rd574, %rd932, %rd573;
	sub.s32 	%r917, 52, %r303;
	mov.b64 	%rd575, 1;
	shl.b64 	%rd576, %rd575, %r917;
	setp.gt.u64 	%p395, %rd574, %rd576;
	setp.eq.b64 	%p396, %rd574, %rd576;
	and.b64 	%rd577, %rd570, 1;
	setp.ne.b64 	%p397, %rd577, 0;
	and.pred 	%p398, %p396, %p397;
	or.pred 	%p399, %p395, %p398;
	selp.b64 	%rd578, 1, 0, %p399;
	add.s64 	%rd175, %rd570, %rd578;
	shl.b64 	%rd176, %rd575, %r303;
	setp.eq.b64 	%p400, %rd175, %rd176;
	add.s32 	%r918, %r302, -1022;
	selp.b32 	%r308, %r918, %r306, %p400;
	setp.le.s32 	%p401, %r308, %r304;
	@%p401 bra 	$L__BB23_677;
	or.b32 	%r1415, %r301, %r305;
	bra.uni 	$L__BB23_678;
$L__BB23_677:
	selp.b32 	%r919, 1, 0, %p400;
	shr.u64 	%rd579, %rd175, %r919;
	add.s32 	%r920, %r308, %r304;
	add.s32 	%r921, %r303, -1;
	shl.b32 	%r922, %r920, %r921;
	shl.b64 	%rd580, %rd571, %r921;
	not.b64 	%rd581, %rd580;
	and.b64 	%rd582, %rd579, %rd581;
	cvt.u32.u64 	%r923, %rd582;
	or.b32 	%r924, %r922, %r923;
	or.b32 	%r1415, %r924, %r301;
$L__BB23_678:
	cvt.u16.u32 	%rs28, %r1415;
	bra.uni 	$L__BB23_679;
$L__BB23_671:
	neg.s32 	%r927, %r307;
	shl.b64 	%rd931, %rd173, %r927;
$L__BB23_674:
	or.b64 	%rd592, %rd931, %rd174;
	cvt.u16.u64 	%rs28, %rd592;
$L__BB23_679:
	setp.ne.b32 	%p409, %r1360, 13;
	cvt.u32.u16 	%r309, %rs28;
	@%p409 bra 	$L__BB23_681;
	shl.b32 	%r1416, %r309, 16;
	bra.uni 	$L__BB23_687;
$L__BB23_681:
	cvt.s32.s16 	%r928, %rs28;
	and.b32 	%r1416, %r928, -2147483648;
	bfe.u32 	%r310, %r309, 10, 5;
	setp.eq.b32 	%p410, %r310, 31;
	@%p410 bra 	$L__BB23_685;
	and.b32 	%r311, %r309, 1023;
	setp.ne.b32 	%p411, %r310, 0;
	@%p411 bra 	$L__BB23_686;
	setp.eq.b32 	%p412, %r311, 0;
	@%p412 bra 	$L__BB23_687;
	clz.b32 	%r931, %r311;
	xor.b32 	%r932, %r931, 31;
	sub.s32 	%r933, 9, %r932;
	shl.b32 	%r934, %r309, %r933;
	shl.b32 	%r935, %r932, 23;
	shl.b32 	%r936, %r934, 14;
	and.b32 	%r937, %r936, 8372224;
	add.s32 	%r938, %r935, %r1416;
	add.s32 	%r939, %r938, %r937;
	add.s32 	%r1416, %r939, 864026624;
	bra.uni 	$L__BB23_687;
$L__BB23_685:
	shl.b32 	%r929, %r309, 13;
	or.b32 	%r930, %r1416, %r929;
	or.b32 	%r1416, %r930, 2139095040;
	bra.uni 	$L__BB23_687;
$L__BB23_686:
	shl.b32 	%r940, %r310, 23;
	shl.b32 	%r941, %r311, 13;
	or.b32 	%r942, %r940, %r941;
	add.s32 	%r943, %r942, %r1416;
	add.s32 	%r1416, %r943, 939524096;
$L__BB23_687:
	cvt.f64.f32 	%rd932, %r1416;
$L__BB23_688:
	@%p1 bra 	$L__BB23_690;
	mov.b32 	%r945, 16;
	atom.global.or.b32 %r944, [%rd887], %r945;
$L__BB23_690:
	abs.f64 	%rd885, %rd933;
	setp.ne.f64 	%p671, %rd885, 0d7FF0000000000000;
	abs.f64 	%rd886, %rd932;
	setp.ne.f64 	%p672, %rd886, 0d7FF0000000000000;
	and.pred 	%p673, %p671, %p672;
	@%p673 bra 	$L__BB23_692;
	setp.eq.b32 	%p674, %r313, 4;
	ld.local.b64 	%rd888, [%rd2];
	setp.eq.f64 	%p675, %rd888, 0d0000000000000000;
	ld.local.b64 	%rd889, [%rd2+8];
	setp.eq.f64 	%p676, %rd889, 0d0000000000000000;
	selp.b32 	%r1357, 8, 16, %p676;
	selp.b32 	%r1358, %r1357, 16, %p675;
	selp.b32 	%r1356, %r1358, 16, %p674;
	atom.global.or.b32 %r1355, [%rd887], %r1356;
$L__BB23_692:
	st.param.b64 	[func_retval0+8], %rd932;
	st.param.b64 	[func_retval0], %rd933;
	ret;
}
.weak .func  (.param .align 4 .b8 func_retval0[8]) _Z6q_readIfE5QPairIT_EPKvyi(
	.param .b64 _Z6q_readIfE5QPairIT_EPKvyi_param_0,
	.param .b64 _Z6q_readIfE5QPairIT_EPKvyi_param_1,
	.param .b32 _Z6q_readIfE5QPairIT_EPKvyi_param_2
)
{
	.reg .pred 	%p<43>;
	.reg .b16 	%rs<3>;
	.reg .b32 	%r<50>;
	.reg .b64 	%rd<52>;
	ld.param.b32 	%r9, [_Z6q_readIfE5QPairIT_EPKvyi_param_2];
	ld.param.b64 	%rd3, [_Z6q_readIfE5QPairIT_EPKvyi_param_1];
	setp.gt.s32 	%p1, %r9, 15;
	@%p1 bra 	$L__BB24_4;
	mov.b32 	%r46, 12;
	setp.eq.b32 	%p4, %r9, 14;
	@%p4 bra 	$L__BB24_8;
	setp.eq.b32 	%p5, %r9, 15;
	mov.b32 	%r46, %r9;
	@%p5 bra 	$L__BB24_3;
	bra.uni 	$L__BB24_8;
$L__BB24_3:
	mov.b32 	%r46, 13;
	bra.uni 	$L__BB24_8;
$L__BB24_4:
	setp.eq.b32 	%p2, %r9, 16;
	@%p2 bra 	$L__BB24_7;
	setp.ne.b32 	%p3, %r9, 17;
	mov.b32 	%r46, %r9;
	@%p3 bra 	$L__BB24_8;
	mov.b32 	%r46, 9;
	bra.uni 	$L__BB24_8;
$L__BB24_7:
	mov.b32 	%r46, 10;
$L__BB24_8:
	ld.param.b64 	%rd2, [_Z6q_readIfE5QPairIT_EPKvyi_param_0];
	add.s32 	%r1, %r9, -14;
	setp.lt.u32 	%p6, %r1, 4;
	selp.b32 	%r10, 1, 0, %p6;
	shl.b64 	%rd1, %rd3, %r10;
	and.b32 	%r2, %r46, -2;
	setp.ne.b32 	%p7, %r2, 12;
	@%p7 bra 	$L__BB24_18;
	shl.b64 	%rd24, %rd1, 1;
	add.s64 	%rd25, %rd2, %rd24;
	ld.b16 	%rs1, [%rd25];
	setp.ne.b32 	%p21, %r46, 13;
	cvt.u32.u16 	%r3, %rs1;
	@%p21 bra 	$L__BB24_11;
	shl.b32 	%r47, %r3, 16;
	bra.uni 	$L__BB24_17;
$L__BB24_18:
	setp.gt.s32 	%p8, %r46, 4;
	@%p8 bra 	$L__BB24_26;
	bra.uni 	$L__BB24_19;
$L__BB24_26:
	setp.gt.s32 	%p9, %r46, 6;
	@%p9 bra 	$L__BB24_30;
	bra.uni 	$L__BB24_27;
$L__BB24_30:
	setp.eq.b32 	%p10, %r46, 7;
	@%p10 bra 	$L__BB24_38;
	setp.eq.b32 	%p11, %r46, 9;
	@%p11 bra 	$L__BB24_34;
	setp.ne.b32 	%p12, %r46, 10;
	@%p12 bra 	$L__BB24_39;
	shl.b64 	%rd18, %rd1, 2;
	add.s64 	%rd19, %rd2, %rd18;
	ld.b32 	%r11, [%rd19];
	cvt.f64.f32 	%rd49, %r11;
	bra.uni 	$L__BB24_41;
$L__BB24_11:
	cvt.s32.s16 	%r12, %rs1;
	and.b32 	%r47, %r12, -2147483648;
	bfe.u32 	%r4, %r3, 10, 5;
	setp.eq.b32 	%p22, %r4, 31;
	@%p22 bra 	$L__BB24_15;
	and.b32 	%r5, %r3, 1023;
	setp.ne.b32 	%p23, %r4, 0;
	@%p23 bra 	$L__BB24_16;
	setp.eq.b32 	%p24, %r5, 0;
	@%p24 bra 	$L__BB24_17;
	clz.b32 	%r15, %r5;
	xor.b32 	%r16, %r15, 31;
	sub.s32 	%r17, 9, %r16;
	shl.b32 	%r18, %r3, %r17;
	shl.b32 	%r19, %r16, 23;
	shl.b32 	%r20, %r18, 14;
	and.b32 	%r21, %r20, 8372224;
	add.s32 	%r22, %r19, %r47;
	add.s32 	%r23, %r22, %r21;
	add.s32 	%r47, %r23, 864026624;
	bra.uni 	$L__BB24_17;
$L__BB24_19:
	setp.gt.s32 	%p15, %r46, 2;
	@%p15 bra 	$L__BB24_23;
	setp.eq.b32 	%p18, %r46, 1;
	@%p18 bra 	$L__BB24_35;
	setp.eq.b32 	%p19, %r46, 2;
	@%p19 bra 	$L__BB24_22;
	bra.uni 	$L__BB24_39;
$L__BB24_22:
	add.s64 	%rd13, %rd2, %rd1;
	ld.s8 	%rd48, [%rd13];
	bra.uni 	$L__BB24_40;
$L__BB24_23:
	setp.eq.b32 	%p16, %r46, 3;
	@%p16 bra 	$L__BB24_36;
	setp.eq.b32 	%p17, %r46, 4;
	@%p17 bra 	$L__BB24_25;
	bra.uni 	$L__BB24_39;
$L__BB24_25:
	shl.b64 	%rd9, %rd1, 2;
	add.s64 	%rd10, %rd2, %rd9;
	ld.s32 	%rd48, [%rd10];
	bra.uni 	$L__BB24_40;
$L__BB24_27:
	setp.eq.b32 	%p13, %r46, 5;
	@%p13 bra 	$L__BB24_37;
	setp.eq.b32 	%p14, %r46, 6;
	@%p14 bra 	$L__BB24_29;
	bra.uni 	$L__BB24_39;
$L__BB24_29:
	shl.b64 	%rd6, %rd1, 1;
	add.s64 	%rd7, %rd2, %rd6;
	ld.b16 	%rd48, [%rd7];
	bra.uni 	$L__BB24_40;
$L__BB24_15:
	shl.b32 	%r13, %r3, 13;
	or.b32 	%r14, %r47, %r13;
	or.b32 	%r47, %r14, 2139095040;
	bra.uni 	$L__BB24_17;
$L__BB24_16:
	shl.b32 	%r24, %r4, 23;
	shl.b32 	%r25, %r5, 13;
	or.b32 	%r26, %r24, %r25;
	add.s32 	%r27, %r26, %r47;
	add.s32 	%r47, %r27, 939524096;
$L__BB24_17:
	cvt.f64.f32 	%rd49, %r47;
	bra.uni 	$L__BB24_41;
$L__BB24_35:
)QPTX";
        result += R"QPTX(
	shl.b64 	%rd14, %rd1, 3;
	add.s64 	%rd15, %rd2, %rd14;
	ld.b64 	%rd48, [%rd15];
	bra.uni 	$L__BB24_40;
$L__BB24_36:
	shl.b64 	%rd11, %rd1, 1;
	add.s64 	%rd12, %rd2, %rd11;
	ld.s16 	%rd48, [%rd12];
	bra.uni 	$L__BB24_40;
$L__BB24_38:
	shl.b64 	%rd4, %rd1, 2;
	add.s64 	%rd5, %rd2, %rd4;
	ld.b32 	%rd48, [%rd5];
	bra.uni 	$L__BB24_40;
$L__BB24_37:
	add.s64 	%rd8, %rd2, %rd1;
	ld.b8 	%rd48, [%rd8];
	bra.uni 	$L__BB24_40;
$L__BB24_34:
	shl.b64 	%rd16, %rd1, 3;
	add.s64 	%rd17, %rd2, %rd16;
	ld.b64 	%rd49, [%rd17];
	bra.uni 	$L__BB24_41;
$L__BB24_39:
	shl.b64 	%rd20, %rd1, 3;
	add.s64 	%rd21, %rd2, %rd20;
	ld.b64 	%rd48, [%rd21];
$L__BB24_40:
	setp.lt.s32 	%p20, %r46, 5;
	cvt.rn.f64.s64 	%rd22, %rd48;
	cvt.rn.f64.u64 	%rd23, %rd48;
	selp.f64 	%rd49, %rd22, %rd23, %p20;
$L__BB24_41:
	setp.gt.u32 	%p25, %r1, 3;
	mov.b32 	%r49, 0f00000000;
	@%p25 bra 	$L__BB24_76;
	@%p7 bra 	$L__BB24_52;
	shl.b64 	%rd46, %rd1, 1;
	add.s64 	%rd47, %rd2, %rd46;
	ld.b16 	%rs2, [%rd47+2];
	setp.ne.b32 	%p39, %r46, 13;
	cvt.u32.u16 	%r6, %rs2;
	@%p39 bra 	$L__BB24_45;
	shl.b32 	%r48, %r6, 16;
	bra.uni 	$L__BB24_51;
$L__BB24_52:
	setp.gt.s32 	%p26, %r46, 4;
	@%p26 bra 	$L__BB24_60;
	bra.uni 	$L__BB24_53;
$L__BB24_60:
	setp.gt.s32 	%p27, %r46, 6;
	@%p27 bra 	$L__BB24_64;
	bra.uni 	$L__BB24_61;
$L__BB24_64:
	setp.eq.b32 	%p28, %r46, 7;
	@%p28 bra 	$L__BB24_72;
	setp.eq.b32 	%p29, %r46, 9;
	@%p29 bra 	$L__BB24_68;
	setp.ne.b32 	%p30, %r46, 10;
	@%p30 bra 	$L__BB24_73;
	shl.b64 	%rd40, %rd1, 2;
	add.s64 	%rd41, %rd2, %rd40;
	ld.b32 	%r28, [%rd41+4];
	cvt.f64.f32 	%rd51, %r28;
	bra.uni 	$L__BB24_75;
$L__BB24_45:
	cvt.s32.s16 	%r29, %rs2;
	and.b32 	%r48, %r29, -2147483648;
	bfe.u32 	%r7, %r6, 10, 5;
	setp.eq.b32 	%p40, %r7, 31;
	@%p40 bra 	$L__BB24_49;
	and.b32 	%r8, %r6, 1023;
	setp.ne.b32 	%p41, %r7, 0;
	@%p41 bra 	$L__BB24_50;
	setp.eq.b32 	%p42, %r8, 0;
	@%p42 bra 	$L__BB24_51;
	clz.b32 	%r32, %r8;
	xor.b32 	%r33, %r32, 31;
	sub.s32 	%r34, 9, %r33;
	shl.b32 	%r35, %r6, %r34;
	shl.b32 	%r36, %r33, 23;
	shl.b32 	%r37, %r35, 14;
	and.b32 	%r38, %r37, 8372224;
	add.s32 	%r39, %r36, %r48;
	add.s32 	%r40, %r39, %r38;
	add.s32 	%r48, %r40, 864026624;
	bra.uni 	$L__BB24_51;
$L__BB24_53:
	setp.gt.s32 	%p33, %r46, 2;
	@%p33 bra 	$L__BB24_57;
	setp.eq.b32 	%p36, %r46, 1;
	@%p36 bra 	$L__BB24_69;
	setp.eq.b32 	%p37, %r46, 2;
	@%p37 bra 	$L__BB24_56;
	bra.uni 	$L__BB24_73;
$L__BB24_56:
	add.s64 	%rd35, %rd2, %rd1;
	ld.s8 	%rd50, [%rd35+1];
	bra.uni 	$L__BB24_74;
$L__BB24_57:
	setp.eq.b32 	%p34, %r46, 3;
	@%p34 bra 	$L__BB24_70;
	setp.eq.b32 	%p35, %r46, 4;
	@%p35 bra 	$L__BB24_59;
	bra.uni 	$L__BB24_73;
$L__BB24_59:
	shl.b64 	%rd31, %rd1, 2;
	add.s64 	%rd32, %rd2, %rd31;
	ld.s32 	%rd50, [%rd32+4];
	bra.uni 	$L__BB24_74;
$L__BB24_61:
	setp.eq.b32 	%p31, %r46, 5;
	@%p31 bra 	$L__BB24_71;
	setp.eq.b32 	%p32, %r46, 6;
	@%p32 bra 	$L__BB24_63;
	bra.uni 	$L__BB24_73;
$L__BB24_63:
	shl.b64 	%rd28, %rd1, 1;
	add.s64 	%rd29, %rd2, %rd28;
	ld.b16 	%rd50, [%rd29+2];
	bra.uni 	$L__BB24_74;
$L__BB24_49:
	shl.b32 	%r30, %r6, 13;
	or.b32 	%r31, %r48, %r30;
	or.b32 	%r48, %r31, 2139095040;
	bra.uni 	$L__BB24_51;
$L__BB24_50:
	shl.b32 	%r41, %r7, 23;
	shl.b32 	%r42, %r8, 13;
	or.b32 	%r43, %r41, %r42;
	add.s32 	%r44, %r43, %r48;
	add.s32 	%r48, %r44, 939524096;
$L__BB24_51:
	cvt.f64.f32 	%rd51, %r48;
	bra.uni 	$L__BB24_75;
$L__BB24_69:
	shl.b64 	%rd36, %rd1, 3;
	add.s64 	%rd37, %rd2, %rd36;
	ld.b64 	%rd50, [%rd37+8];
	bra.uni 	$L__BB24_74;
$L__BB24_70:
	shl.b64 	%rd33, %rd1, 1;
	add.s64 	%rd34, %rd2, %rd33;
	ld.s16 	%rd50, [%rd34+2];
	bra.uni 	$L__BB24_74;
$L__BB24_72:
	shl.b64 	%rd26, %rd1, 2;
	add.s64 	%rd27, %rd2, %rd26;
	ld.b32 	%rd50, [%rd27+4];
	bra.uni 	$L__BB24_74;
$L__BB24_71:
	add.s64 	%rd30, %rd2, %rd1;
	ld.b8 	%rd50, [%rd30+1];
	bra.uni 	$L__BB24_74;
$L__BB24_68:
	shl.b64 	%rd38, %rd1, 3;
	add.s64 	%rd39, %rd2, %rd38;
	ld.b64 	%rd51, [%rd39+8];
	bra.uni 	$L__BB24_75;
$L__BB24_73:
	shl.b64 	%rd42, %rd1, 3;
	add.s64 	%rd43, %rd2, %rd42;
	ld.b64 	%rd50, [%rd43+8];
$L__BB24_74:
	setp.lt.s32 	%p38, %r46, 5;
	cvt.rn.f64.s64 	%rd44, %rd50;
	cvt.rn.f64.u64 	%rd45, %rd50;
	selp.f64 	%rd51, %rd44, %rd45, %p38;
$L__BB24_75:
	cvt.rn.f32.f64 	%r49, %rd51;
$L__BB24_76:
	cvt.rn.f32.f64 	%r45, %rd49;
	st.param.b32 	[func_retval0+4], %r49;
	st.param.b32 	[func_retval0], %r45;
	ret;
}
.weak .func  (.param .b32 func_retval0) _Z7q_roundIfET_S0_i(
	.param .b32 _Z7q_roundIfET_S0_i_param_0,
	.param .b32 _Z7q_roundIfET_S0_i_param_1
)
{
	.reg .pred 	%p<25>;
	.reg .b16 	%rs<2>;
	.reg .b32 	%r<53>;
	.reg .b64 	%rd<33>;
	ld.param.b32 	%r12, [_Z7q_roundIfET_S0_i_param_1];
	ld.param.b32 	%r52, [_Z7q_roundIfET_S0_i_param_0];
	and.b32 	%r13, %r12, -2;
	setp.ne.b32 	%p1, %r13, 12;
	@%p1 bra 	$L__BB25_23;
	cvt.f64.f32 	%rd1, %r52;
	shr.u64 	%rd3, %rd1, 48;
	cvt.u32.u64 	%r14, %rd3;
	and.b32 	%r1, %r14, 32768;
	shr.u64 	%rd8, %rd1, 52;
	cvt.u32.u64 	%r15, %rd8;
	and.b32 	%r2, %r15, 2047;
	setp.eq.b32 	%p3, %r2, 0;
	@%p3 bra 	$L__BB25_4;
	and.b64 	%rd2, %rd1, 4503599627370495;
	setp.eq.b32 	%p2, %r12, 12;
	selp.b32 	%r3, 11, 8, %p2;
	selp.b32 	%r5, 31744, 32640, %p2;
	setp.ne.b32 	%p4, %r2, 2047;
	@%p4 bra 	$L__BB25_5;
	setp.eq.b64 	%p5, %rd2, 0;
	add.s32 	%r16, %r3, -2;
	mov.b32 	%r17, 1;
	shl.b32 	%r18, %r17, %r16;
	selp.b32 	%r19, 0, %r18, %p5;
	or.b32 	%r20, %r5, %r19;
	or.b32 	%r21, %r20, %r1;
	cvt.u16.u32 	%rs1, %r21;
	bra.uni 	$L__BB25_15;
$L__BB25_4:
	cvt.u16.u32 	%rs1, %r1;
	bra.uni 	$L__BB25_15;
$L__BB25_5:
	selp.b32 	%r22, -14, -126, %p2;
	add.s32 	%r6, %r2, -1023;
	or.b64 	%rd4, %rd2, 4503599627370496;
	setp.ge.s32 	%p6, %r6, %r22;
	@%p6 bra 	$L__BB25_11;
	and.b64 	%rd5, %rd3, 32768;
	selp.b32 	%r32, 28, -81, %p2;
	sub.s32 	%r7, %r32, %r6;
	setp.gt.s32 	%p14, %r7, 0;
	@%p14 bra 	$L__BB25_8;
	bra.uni 	$L__BB25_7;
$L__BB25_8:
	setp.gt.u32 	%p15, %r7, 63;
	mov.b64 	%rd32, 0;
	@%p15 bra 	$L__BB25_10;
	shr.u64 	%rd22, %rd4, %r7;
	mov.b64 	%rd23, -1;
	shl.b64 	%rd24, %rd23, %r7;
	not.b64 	%rd25, %rd24;
	and.b64 	%rd26, %rd4, %rd25;
	add.s32 	%r33, %r7, -1;
	mov.b64 	%rd27, 1;
	shl.b64 	%rd28, %rd27, %r33;
	setp.gt.u64 	%p16, %rd26, %rd28;
	setp.eq.b64 	%p17, %rd26, %rd28;
	and.b64 	%rd29, %rd22, 1;
	setp.ne.b64 	%p18, %rd29, 0;
	and.pred 	%p19, %p17, %p18;
	or.pred 	%p20, %p16, %p19;
	selp.b64 	%rd30, 1, 0, %p20;
	add.s64 	%rd32, %rd22, %rd30;
	bra.uni 	$L__BB25_10;
$L__BB25_11:
	selp.b32 	%r4, 15, 127, %p2;
	sub.s32 	%r23, 53, %r3;
	shr.u64 	%rd9, %rd4, %r23;
	mov.b64 	%rd10, -1;
	shl.b64 	%rd11, %rd10, %r23;
	not.b64 	%rd12, %rd11;
	and.b64 	%rd13, %rd12, %rd1;
	sub.s32 	%r24, 52, %r3;
	mov.b64 	%rd14, 1;
	shl.b64 	%rd15, %rd14, %r24;
	setp.gt.u64 	%p7, %rd13, %rd15;
	setp.eq.b64 	%p8, %rd13, %rd15;
	and.b64 	%rd16, %rd9, 1;
	setp.ne.b64 	%p9, %rd16, 0;
	and.pred 	%p10, %p8, %p9;
	or.pred 	%p11, %p7, %p10;
	selp.b64 	%rd17, 1, 0, %p11;
	add.s64 	%rd6, %rd9, %rd17;
	shl.b64 	%rd7, %rd14, %r3;
	setp.eq.b64 	%p12, %rd6, %rd7;
	add.s32 	%r25, %r2, -1022;
	selp.b32 	%r8, %r25, %r6, %p12;
	setp.le.s32 	%p13, %r8, %r4;
	@%p13 bra 	$L__BB25_13;
	or.b32 	%r51, %r1, %r5;
	bra.uni 	$L__BB25_14;
$L__BB25_13:
	selp.b32 	%r26, 1, 0, %p12;
	shr.u64 	%rd18, %rd6, %r26;
	add.s32 	%r27, %r8, %r4;
	add.s32 	%r28, %r3, -1;
	shl.b32 	%r29, %r27, %r28;
	shl.b64 	%rd19, %rd10, %r28;
	not.b64 	%rd20, %rd19;
	and.b64 	%rd21, %rd18, %rd20;
	cvt.u32.u64 	%r30, %rd21;
	or.b32 	%r31, %r29, %r30;
	or.b32 	%r51, %r31, %r1;
$L__BB25_14:
	cvt.u16.u32 	%rs1, %r51;
	bra.uni 	$L__BB25_15;
$L__BB25_7:
	neg.s32 	%r34, %r7;
	shl.b64 	%rd32, %rd4, %r34;
$L__BB25_10:
	or.b64 	%rd31, %rd32, %rd5;
	cvt.u16.u64 	%rs1, %rd31;
$L__BB25_15:
	setp.ne.b32 	%p21, %r12, 13;
	cvt.u32.u16 	%r9, %rs1;
	@%p21 bra 	$L__BB25_17;
	shl.b32 	%r52, %r9, 16;
	bra.uni 	$L__BB25_23;
$L__BB25_17:
	cvt.s32.s16 	%r35, %rs1;
	and.b32 	%r52, %r35, -2147483648;
	bfe.u32 	%r10, %r9, 10, 5;
	setp.eq.b32 	%p22, %r10, 31;
	@%p22 bra 	$L__BB25_21;
	and.b32 	%r11, %r9, 1023;
	setp.ne.b32 	%p23, %r10, 0;
	@%p23 bra 	$L__BB25_22;
	setp.eq.b32 	%p24, %r11, 0;
	@%p24 bra 	$L__BB25_23;
	clz.b32 	%r38, %r11;
	xor.b32 	%r39, %r38, 31;
	sub.s32 	%r40, 9, %r39;
	shl.b32 	%r41, %r9, %r40;
	shl.b32 	%r42, %r39, 23;
	shl.b32 	%r43, %r41, 14;
	and.b32 	%r44, %r43, 8372224;
	add.s32 	%r45, %r42, %r52;
	add.s32 	%r46, %r45, %r44;
	add.s32 	%r52, %r46, 864026624;
	bra.uni 	$L__BB25_23;
$L__BB25_21:
	shl.b32 	%r36, %r9, 13;
	or.b32 	%r37, %r52, %r36;
	or.b32 	%r52, %r37, 2139095040;
	bra.uni 	$L__BB25_23;
$L__BB25_22:
	shl.b32 	%r47, %r10, 23;
	shl.b32 	%r48, %r11, 13;
	or.b32 	%r49, %r47, %r48;
	add.s32 	%r50, %r49, %r52;
	add.s32 	%r52, %r50, 939524096;
$L__BB25_23:
	st.param.b32 	[func_retval0], %r52;
	ret;
}
.weak .func _Z7q_storeIfEvPvy5QPairIT_Ei(
	.param .b64 _Z7q_storeIfEvPvy5QPairIT_Ei_param_0,
	.param .b64 _Z7q_storeIfEvPvy5QPairIT_Ei_param_1,
	.param .align 4 .b8 _Z7q_storeIfEvPvy5QPairIT_Ei_param_2[8],
	.param .b32 _Z7q_storeIfEvPvy5QPairIT_Ei_param_3
)
{
	.reg .pred 	%p<49>;
	.reg .b16 	%rs<3>;
	.reg .b32 	%r<68>;
	.reg .b64 	%rd<80>;
	ld.param.b32 	%r21, [_Z7q_storeIfEvPvy5QPairIT_Ei_param_3];
	ld.param.b64 	%rd17, [_Z7q_storeIfEvPvy5QPairIT_Ei_param_1];
	setp.gt.s32 	%p1, %r21, 15;
	@%p1 bra 	$L__BB26_4;
	mov.b32 	%r65, 12;
	setp.eq.b32 	%p4, %r21, 14;
	@%p4 bra 	$L__BB26_8;
	setp.eq.b32 	%p5, %r21, 15;
	mov.b32 	%r65, %r21;
	@%p5 bra 	$L__BB26_3;
	bra.uni 	$L__BB26_8;
$L__BB26_3:
	mov.b32 	%r65, 13;
	bra.uni 	$L__BB26_8;
$L__BB26_4:
	setp.eq.b32 	%p2, %r21, 16;
	@%p2 bra 	$L__BB26_7;
	setp.ne.b32 	%p3, %r21, 17;
	mov.b32 	%r65, %r21;
	@%p3 bra 	$L__BB26_8;
	mov.b32 	%r65, 9;
	bra.uni 	$L__BB26_8;
$L__BB26_7:
	mov.b32 	%r65, 10;
$L__BB26_8:
	ld.param.b64 	%rd16, [_Z7q_storeIfEvPvy5QPairIT_Ei_param_0];
	add.s32 	%r1, %r21, -14;
	setp.lt.u32 	%p6, %r1, 4;
	selp.b32 	%r22, 1, 0, %p6;
	shl.b64 	%rd1, %rd17, %r22;
	ld.param.b32 	%r2, [_Z7q_storeIfEvPvy5QPairIT_Ei_param_2];
	cvt.f64.f32 	%rd2, %r2;
	and.b32 	%r3, %r65, -2;
	setp.ne.b32 	%p7, %r3, 12;
	@%p7 bra 	$L__BB26_24;
	shr.u64 	%rd4, %rd2, 48;
	cvt.u32.u64 	%r23, %rd4;
	and.b32 	%r4, %r23, 32768;
	shr.u64 	%rd22, %rd2, 52;
	cvt.u32.u64 	%r24, %rd22;
	and.b32 	%r5, %r24, 2047;
	setp.eq.b32 	%p10, %r5, 0;
	@%p10 bra 	$L__BB26_12;
	and.b64 	%rd3, %rd2, 4503599627370495;
	setp.eq.b32 	%p9, %r65, 12;
	selp.b32 	%r6, 11, 8, %p9;
	selp.b32 	%r8, 31744, 32640, %p9;
	setp.ne.b32 	%p11, %r5, 2047;
	@%p11 bra 	$L__BB26_13;
	setp.eq.b64 	%p12, %rd3, 0;
	add.s32 	%r25, %r6, -2;
	mov.b32 	%r26, 1;
	shl.b32 	%r27, %r26, %r25;
	selp.b32 	%r28, 0, %r27, %p12;
	or.b32 	%r29, %r28, %r8;
	or.b32 	%r30, %r29, %r4;
	cvt.u16.u32 	%rs1, %r30;
	bra.uni 	$L__BB26_23;
$L__BB26_24:
	setp.ne.b32 	%p8, %r65, 10;
	@%p8 bra 	$L__BB26_26;
	shl.b64 	%rd20, %rd1, 2;
	add.s64 	%rd21, %rd16, %rd20;
	st.b32 	[%rd21], %r2;
	bra.uni 	$L__BB26_27;
$L__BB26_26:
	shl.b64 	%rd18, %rd1, 3;
	add.s64 	%rd19, %rd16, %rd18;
	st.b64 	[%rd19], %rd2;
	bra.uni 	$L__BB26_27;
$L__BB26_12:
	cvt.u16.u32 	%rs1, %r4;
	bra.uni 	$L__BB26_23;
$L__BB26_13:
	selp.b32 	%r31, -14, -126, %p9;
	add.s32 	%r9, %r5, -1023;
	or.b64 	%rd5, %rd3, 4503599627370496;
	setp.ge.s32 	%p13, %r9, %r31;
	@%p13 bra 	$L__BB26_19;
	and.b64 	%rd6, %rd4, 32768;
	selp.b32 	%r41, 28, -81, %p9;
	sub.s32 	%r10, %r41, %r9;
	setp.gt.s32 	%p21, %r10, 0;
	@%p21 bra 	$L__BB26_16;
	bra.uni 	$L__BB26_15;
$L__BB26_16:
	setp.gt.u32 	%p22, %r10, 63;
	mov.b64 	%rd78, 0;
	@%p22 bra 	$L__BB26_18;
	shr.u64 	%rd36, %rd5, %r10;
	mov.b64 	%rd37, -1;
	shl.b64 	%rd38, %rd37, %r10;
	not.b64 	%rd39, %rd38;
	and.b64 	%rd40, %rd5, %rd39;
	add.s32 	%r42, %r10, -1;
	mov.b64 	%rd41, 1;
	shl.b64 	%rd42, %rd41, %r42;
	setp.gt.u64 	%p23, %rd40, %rd42;
	setp.eq.b64 	%p24, %rd40, %rd42;
	and.b64 	%rd43, %rd36, 1;
	setp.ne.b64 	%p25, %rd43, 0;
	and.pred 	%p26, %p24, %p25;
	or.pred 	%p27, %p23, %p26;
	selp.b64 	%rd44, 1, 0, %p27;
	add.s64 	%rd78, %rd36, %rd44;
	bra.uni 	$L__BB26_18;
$L__BB26_19:
	selp.b32 	%r7, 15, 127, %p9;
	sub.s32 	%r32, 53, %r6;
	shr.u64 	%rd23, %rd5, %r32;
	mov.b64 	%rd24, -1;
	shl.b64 	%rd25, %rd24, %r32;
	not.b64 	%rd26, %rd25;
	and.b64 	%rd27, %rd26, %rd2;
	sub.s32 	%r33, 52, %r6;
	mov.b64 	%rd28, 1;
	shl.b64 	%rd29, %rd28, %r33;
	setp.gt.u64 	%p14, %rd27, %rd29;
	setp.eq.b64 	%p15, %rd27, %rd29;
	and.b64 	%rd30, %rd23, 1;
	setp.ne.b64 	%p16, %rd30, 0;
	and.pred 	%p17, %p15, %p16;
	or.pred 	%p18, %p14, %p17;
	selp.b64 	%rd31, 1, 0, %p18;
	add.s64 	%rd7, %rd23, %rd31;
	shl.b64 	%rd8, %rd28, %r6;
	setp.eq.b64 	%p19, %rd7, %rd8;
	add.s32 	%r34, %r5, -1022;
	selp.b32 	%r11, %r34, %r9, %p19;
	setp.le.s32 	%p20, %r11, %r7;
	@%p20 bra 	$L__BB26_21;
	or.b32 	%r66, %r4, %r8;
	bra.uni 	$L__BB26_22;
$L__BB26_21:
	selp.b32 	%r35, 1, 0, %p19;
	shr.u64 	%rd32, %rd7, %r35;
	add.s32 	%r36, %r11, %r7;
	add.s32 	%r37, %r6, -1;
	shl.b32 	%r38, %r36, %r37;
	shl.b64 	%rd33, %rd24, %r37;
	not.b64 	%rd34, %rd33;
	and.b64 	%rd35, %rd32, %rd34;
	cvt.u32.u64 	%r39, %rd35;
	or.b32 	%r40, %r38, %r39;
	or.b32 	%r66, %r40, %r4;
$L__BB26_22:
	cvt.u16.u32 	%rs1, %r66;
	bra.uni 	$L__BB26_23;
$L__BB26_15:
	neg.s32 	%r43, %r10;
	shl.b64 	%rd78, %rd5, %r43;
$L__BB26_18:
	or.b64 	%rd45, %rd78, %rd6;
	cvt.u16.u64 	%rs1, %rd45;
$L__BB26_23:
	shl.b64 	%rd46, %rd1, 1;
	add.s64 	%rd47, %rd16, %rd46;
	st.b16 	[%rd47], %rs1;
$L__BB26_27:
	setp.gt.u32 	%p28, %r1, 3;
	@%p28 bra 	$L__BB26_47;
	ld.param.b32 	%r12, [_Z7q_storeIfEvPvy5QPairIT_Ei_param_2+4];
	cvt.f64.f32 	%rd9, %r12;
	@%p7 bra 	$L__BB26_44;
	shr.u64 	%rd11, %rd9, 48;
	cvt.u32.u64 	%r44, %rd11;
	and.b32 	%r13, %r44, 32768;
	shr.u64 	%rd52, %rd9, 52;
	cvt.u32.u64 	%r45, %rd52;
	and.b32 	%r14, %r45, 2047;
	setp.eq.b32 	%p31, %r14, 0;
	@%p31 bra 	$L__BB26_32;
	and.b64 	%rd10, %rd9, 4503599627370495;
	setp.eq.b32 	%p30, %r65, 12;
	selp.b32 	%r15, 11, 8, %p30;
	selp.b32 	%r17, 31744, 32640, %p30;
	setp.ne.b32 	%p32, %r14, 2047;
	@%p32 bra 	$L__BB26_33;
	setp.eq.b64 	%p33, %rd10, 0;
	add.s32 	%r46, %r15, -2;
	mov.b32 	%r47, 1;
	shl.b32 	%r48, %r47, %r46;
	selp.b32 	%r49, 0, %r48, %p33;
	or.b32 	%r50, %r49, %r17;
	or.b32 	%r51, %r50, %r13;
	cvt.u16.u32 	%rs2, %r51;
	bra.uni 	$L__BB26_43;
$L__BB26_44:
	setp.ne.b32 	%p29, %r65, 10;
	@%p29 bra 	$L__BB26_46;
	shl.b64 	%rd50, %rd1, 2;
	add.s64 	%rd51, %rd16, %rd50;
	st.b32 	[%rd51+4], %r12;
	bra.uni 	$L__BB26_47;
$L__BB26_46:
	shl.b64 	%rd48, %rd1, 3;
	add.s64 	%rd49, %rd16, %rd48;
	st.b64 	[%rd49+8], %rd9;
	bra.uni 	$L__BB26_47;
$L__BB26_32:
	cvt.u16.u32 	%rs2, %r13;
	bra.uni 	$L__BB26_43;
$L__BB26_33:
	selp.b32 	%r52, -14, -126, %p30;
	add.s32 	%r18, %r14, -1023;
	or.b64 	%rd12, %rd10, 4503599627370496;
	setp.ge.s32 	%p34, %r18, %r52;
	@%p34 bra 	$L__BB26_39;
	and.b64 	%rd13, %rd11, 32768;
	selp.b32 	%r62, 28, -81, %p30;
	sub.s32 	%r19, %r62, %r18;
	setp.gt.s32 	%p42, %r19, 0;
	@%p42 bra 	$L__BB26_36;
	bra.uni 	$L__BB26_35;
$L__BB26_36:
	setp.gt.u32 	%p43, %r19, 63;
	mov.b64 	%rd79, 0;
	@%p43 bra 	$L__BB26_38;
	shr.u64 	%rd66, %rd12, %r19;
	mov.b64 	%rd67, -1;
	shl.b64 	%rd68, %rd67, %r19;
	not.b64 	%rd69, %rd68;
	and.b64 	%rd70, %rd12, %rd69;
	add.s32 	%r63, %r19, -1;
	mov.b64 	%rd71, 1;
	shl.b64 	%rd72, %rd71, %r63;
	setp.gt.u64 	%p44, %rd70, %rd72;
	setp.eq.b64 	%p45, %rd70, %rd72;
	and.b64 	%rd73, %rd66, 1;
	setp.ne.b64 	%p46, %rd73, 0;
	and.pred 	%p47, %p45, %p46;
	or.pred 	%p48, %p44, %p47;
	selp.b64 	%rd74, 1, 0, %p48;
	add.s64 	%rd79, %rd66, %rd74;
	bra.uni 	$L__BB26_38;
$L__BB26_39:
	selp.b32 	%r16, 15, 127, %p30;
	sub.s32 	%r53, 53, %r15;
	shr.u64 	%rd53, %rd12, %r53;
	mov.b64 	%rd54, -1;
	shl.b64 	%rd55, %rd54, %r53;
	not.b64 	%rd56, %rd55;
	and.b64 	%rd57, %rd9, %rd56;
	sub.s32 	%r54, 52, %r15;
	mov.b64 	%rd58, 1;
	shl.b64 	%rd59, %rd58, %r54;
	setp.gt.u64 	%p35, %rd57, %rd59;
	setp.eq.b64 	%p36, %rd57, %rd59;
	and.b64 	%rd60, %rd53, 1;
	setp.ne.b64 	%p37, %rd60, 0;
	and.pred 	%p38, %p36, %p37;
	or.pred 	%p39, %p35, %p38;
	selp.b64 	%rd61, 1, 0, %p39;
	add.s64 	%rd14, %rd53, %rd61;
	shl.b64 	%rd15, %rd58, %r15;
	setp.eq.b64 	%p40, %rd14, %rd15;
	add.s32 	%r55, %r14, -1022;
	selp.b32 	%r20, %r55, %r18, %p40;
	setp.le.s32 	%p41, %r20, %r16;
	@%p41 bra 	$L__BB26_41;
	or.b32 	%r67, %r13, %r17;
	bra.uni 	$L__BB26_42;
$L__BB26_41:
	selp.b32 	%r56, 1, 0, %p40;
	shr.u64 	%rd62, %rd14, %r56;
	add.s32 	%r57, %r20, %r16;
	add.s32 	%r58, %r15, -1;
	shl.b32 	%r59, %r57, %r58;
	shl.b64 	%rd63, %rd54, %r58;
	not.b64 	%rd64, %rd63;
	and.b64 	%rd65, %rd62, %rd64;
	cvt.u32.u64 	%r60, %rd65;
	or.b32 	%r61, %r59, %r60;
	or.b32 	%r67, %r61, %r13;
$L__BB26_42:
	cvt.u16.u32 	%rs2, %r67;
	bra.uni 	$L__BB26_43;
$L__BB26_35:
	neg.s32 	%r64, %r19;
	shl.b64 	%rd79, %rd12, %r64;
$L__BB26_38:
	or.b64 	%rd75, %rd79, %rd13;
	cvt.u16.u64 	%rs2, %rd75;
$L__BB26_43:
	shl.b64 	%rd76, %rd1, 1;
	add.s64 	%rd77, %rd16, %rd76;
	st.b16 	[%rd77+2], %rs2;
$L__BB26_47:
	ret;
}
.weak .func  (.param .align 4 .b8 func_retval0[8]) _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj(
	.param .align 4 .b8 _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_0[8],
	.param .align 4 .b8 _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_1[8],
	.param .b32 _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_2,
	.param .b32 _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_3,
	.param .b64 _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_4
)
{
	.local .align 4 .b8 	__local_depot27[16];
	.reg .b64 	%SP;
	.reg .b64 	%SPL;
	.reg .pred 	%p<679>;
	.reg .b16 	%rs<29>;
	.reg .b32 	%r<1441>;
	.reg .b64 	%rd<910>;
	mov.b64 	%SPL, __local_depot27;
	cvta.local.u64 	%SP, %SPL;
	ld.param.b32 	%r319, [_Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_3];
	ld.param.b32 	%r318, [_Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_2];
	setp.gt.s32 	%p2, %r318, 15;
	@%p2 bra 	$L__BB27_4;
	mov.b32 	%r1396, 12;
	setp.eq.b32 	%p5, %r318, 14;
	@%p5 bra 	$L__BB27_8;
	setp.eq.b32 	%p6, %r318, 15;
	mov.b32 	%r1396, %r318;
	@%p6 bra 	$L__BB27_3;
	bra.uni 	$L__BB27_8;
$L__BB27_3:
	mov.b32 	%r1396, 13;
	bra.uni 	$L__BB27_8;
$L__BB27_4:
	setp.eq.b32 	%p3, %r318, 16;
	@%p3 bra 	$L__BB27_7;
	setp.ne.b32 	%p4, %r318, 17;
	mov.b32 	%r1396, %r318;
	@%p4 bra 	$L__BB27_8;
	mov.b32 	%r1396, 9;
	bra.uni 	$L__BB27_8;
$L__BB27_7:
	mov.b32 	%r1396, 10;
$L__BB27_8:
	ld.param.b64 	%rd881, [_Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_4];
	mov.b64 	%rd1, _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_0;
	mov.b64 	%rd2, _Z8q_binaryIfE5QPairIT_ES2_S2_iiPj_param_1;
	mov.b32 	%r1439, 0f00000000;
	setp.gt.s32 	%p7, %r319, 2;
	@%p7 bra 	$L__BB27_15;
	setp.eq.b32 	%p10, %r319, 1;
	@%p10 bra 	$L__BB27_22;
	setp.eq.b32 	%p11, %r319, 2;
	mov.b32 	%r1440, %r1439;
	@%p11 bra 	$L__BB27_11;
	bra.uni 	$L__BB27_664;
$L__BB27_11:
	ld.local.b32 	%r1231, [%rd1];
	ld.local.b32 	%r1232, [%rd2];
	sub.rn.f32 	%r1440, %r1231, %r1232;
	and.b32 	%r24, %r1396, -2;
	setp.ne.b32 	%p577, %r24, 12;
	@%p577 bra 	$L__BB27_87;
	cvt.f64.f32 	%rd17, %r1440;
	shr.u64 	%rd19, %rd17, 48;
	cvt.u32.u64 	%r1233, %rd19;
	and.b32 	%r25, %r1233, 32768;
	shr.u64 	%rd785, %rd17, 52;
	cvt.u32.u64 	%r1234, %rd785;
	and.b32 	%r26, %r1234, 2047;
	setp.eq.b32 	%p579, %r26, 0;
	@%p579 bra 	$L__BB27_68;
	and.b64 	%rd18, %rd17, 4503599627370495;
	setp.eq.b32 	%p578, %r1396, 12;
	selp.b32 	%r27, 11, 8, %p578;
	selp.b32 	%r29, 31744, 32640, %p578;
	setp.ne.b32 	%p580, %r26, 2047;
	@%p580 bra 	$L__BB27_69;
	setp.eq.b64 	%p581, %rd18, 0;
	add.s32 	%r1235, %r27, -2;
	mov.b32 	%r1236, 1;
	shl.b32 	%r1237, %r1236, %r1235;
	selp.b32 	%r1238, 0, %r1237, %p581;
	or.b32 	%r1239, %r1238, %r29;
	or.b32 	%r1240, %r1239, %r25;
	cvt.u16.u32 	%rs3, %r1240;
	bra.uni 	$L__BB27_79;
$L__BB27_15:
	setp.eq.b32 	%p8, %r319, 3;
	@%p8 bra 	$L__BB27_110;
	setp.eq.b32 	%p9, %r319, 4;
	mov.b32 	%r1440, %r1439;
	@%p9 bra 	$L__BB27_17;
	bra.uni 	$L__BB27_664;
$L__BB27_17:
	add.s32 	%r320, %r318, -14;
	setp.lt.u32 	%p12, %r320, 4;
	and.b32 	%r1395, %r1396, -2;
	@%p12 bra 	$L__BB27_291;
	bra.uni 	$L__BB27_18;
$L__BB27_291:
	ld.local.b32 	%r136, [%rd2];
	abs.f32 	%r360, %r136;
	ld.local.b32 	%r137, [%rd2+4];
	abs.f32 	%r361, %r137;
	setp.ltu.f32 	%p37, %r360, %r361;
	setp.ne.b32 	%p677, %r1395, 12;
	@%p37 bra 	$L__BB27_454;
	bra.uni 	$L__BB27_292;
$L__BB27_454:
	div.rn.f32 	%r1414, %r136, %r137;
	@%p677 bra 	$L__BB27_477;
	cvt.f64.f32 	%rd136, %r1414;
	shr.u64 	%rd138, %rd136, 48;
	cvt.u32.u64 	%r621, %rd138;
	and.b32 	%r217, %r621, 32768;
	shr.u64 	%rd391, %rd136, 52;
	cvt.u32.u64 	%r622, %rd391;
	and.b32 	%r218, %r622, 2047;
	setp.eq.b32 	%p200, %r218, 0;
	@%p200 bra 	$L__BB27_458;
	and.b64 	%rd137, %rd136, 4503599627370495;
	setp.eq.b32 	%p199, %r1396, 12;
	selp.b32 	%r219, 11, 8, %p199;
	selp.b32 	%r221, 31744, 32640, %p199;
	setp.ne.b32 	%p201, %r218, 2047;
	@%p201 bra 	$L__BB27_459;
	setp.eq.b64 	%p202, %rd137, 0;
	add.s32 	%r623, %r219, -2;
	mov.b32 	%r624, 1;
	shl.b32 	%r625, %r624, %r623;
	selp.b32 	%r626, 0, %r625, %p202;
	or.b32 	%r627, %r626, %r221;
	or.b32 	%r628, %r627, %r217;
	cvt.u16.u32 	%rs20, %r628;
	bra.uni 	$L__BB27_469;
$L__BB27_22:
	ld.local.b32 	%r1309, [%rd1];
	ld.local.b32 	%r1310, [%rd2];
	add.rn.f32 	%r1440, %r1309, %r1310;
	and.b32 	%r1, %r1396, -2;
	setp.ne.b32 	%p624, %r1, 12;
	@%p624 bra 	$L__BB27_45;
	cvt.f64.f32 	%rd3, %r1440;
	shr.u64 	%rd5, %rd3, 48;
	cvt.u32.u64 	%r1311, %rd5;
	and.b32 	%r2, %r1311, 32768;
	shr.u64 	%rd833, %rd3, 52;
	cvt.u32.u64 	%r1312, %rd833;
	and.b32 	%r3, %r1312, 2047;
	setp.eq.b32 	%p626, %r3, 0;
	@%p626 bra 	$L__BB27_26;
	and.b64 	%rd4, %rd3, 4503599627370495;
	setp.eq.b32 	%p625, %r1396, 12;
	selp.b32 	%r4, 11, 8, %p625;
	selp.b32 	%r6, 31744, 32640, %p625;
	setp.ne.b32 	%p627, %r3, 2047;
	@%p627 bra 	$L__BB27_27;
	setp.eq.b64 	%p628, %rd4, 0;
	add.s32 	%r1313, %r4, -2;
	mov.b32 	%r1314, 1;
	shl.b32 	%r1315, %r1314, %r1313;
	selp.b32 	%r1316, 0, %r1315, %p628;
	or.b32 	%r1317, %r1316, %r6;
	or.b32 	%r1318, %r1317, %r2;
	cvt.u16.u32 	%rs1, %r1318;
	bra.uni 	$L__BB27_37;
$L__BB27_110:
	add.s32 	%r960, %r318, -14;
	setp.lt.u32 	%p413, %r960, 4;
	@%p413 bra 	$L__BB27_134;
	bra.uni 	$L__BB27_111;
$L__BB27_134:
	ld.local.b32 	%r1001, [%rd1];
	ld.local.b32 	%r1002, [%rd2];
	mul.rn.f32 	%r1003, %r1001, %r1002;
	add.u64 	%rd631, %SPL, 0;
	st.local.b32 	[%rd631], %r1003;
	ld.local.b32 	%r1004, [%rd1+4];
	ld.local.b32 	%r1005, [%rd2+4];
	mul.rn.f32 	%r1006, %r1004, %r1005;
	add.u64 	%rd632, %SP, 4;
	add.u64 	%rd633, %SPL, 4;
	st.local.b32 	[%rd633], %r1006;
	mul.rn.f32 	%r1007, %r1001, %r1005;
	add.u64 	%rd634, %SP, 8;
	add.u64 	%rd635, %SPL, 8;
	st.local.b32 	[%rd635], %r1007;
	mul.rn.f32 	%r1008, %r1002, %r1004;
	add.u64 	%rd636, %SP, 12;
	add.u64 	%rd637, %SPL, 12;
	st.local.b32 	[%rd637], %r1008;
	ld.local.b32 	%r1403, [%rd631];
	and.b32 	%r58, %r1396, -2;
	setp.ne.b32 	%p438, %r58, 12;
	@%p438 bra 	$L__BB27_157;
	cvt.f64.f32 	%rd38, %r1403;
	shr.u64 	%rd40, %rd38, 48;
	cvt.u32.u64 	%r1009, %rd40;
	and.b32 	%r59, %r1009, 32768;
	shr.u64 	%rd638, %rd38, 52;
	cvt.u32.u64 	%r1010, %rd638;
	and.b32 	%r60, %r1010, 2047;
	setp.eq.b32 	%p440, %r60, 0;
	@%p440 bra 	$L__BB27_138;
	and.b64 	%rd39, %rd38, 4503599627370495;
	setp.eq.b32 	%p439, %r1396, 12;
	selp.b32 	%r61, 11, 8, %p439;
	selp.b32 	%r63, 31744, 32640, %p439;
	setp.ne.b32 	%p441, %r60, 2047;
	@%p441 bra 	$L__BB27_139;
	setp.eq.b64 	%p442, %rd39, 0;
	add.s32 	%r1011, %r61, -2;
	mov.b32 	%r1012, 1;
	shl.b32 	%r1013, %r1012, %r1011;
	selp.b32 	%r1014, 0, %r1013, %p442;
	or.b32 	%r1015, %r1014, %r63;
	or.b32 	%r1016, %r1015, %r59;
	cvt.u16.u32 	%rs6, %r1016;
	bra.uni 	$L__BB27_149;
$L__BB27_18:
	ld.local.b32 	%r321, [%rd1];
	ld.local.b32 	%r322, [%rd2];
	div.rn.f32 	%r1440, %r321, %r322;
	setp.ne.b32 	%p13, %r1395, 12;
	@%p13 bra 	$L__BB27_664;
	cvt.f64.f32 	%rd80, %r1440;
	shr.u64 	%rd82, %rd80, 48;
	cvt.u32.u64 	%r323, %rd82;
	and.b32 	%r125, %r323, 32768;
	shr.u64 	%rd199, %rd80, 52;
	cvt.u32.u64 	%r324, %rd199;
	and.b32 	%r126, %r324, 2047;
	setp.eq.b32 	%p15, %r126, 0;
	@%p15 bra 	$L__BB27_272;
	and.b64 	%rd81, %rd80, 4503599627370495;
	setp.eq.b32 	%p14, %r1396, 12;
	selp.b32 	%r127, 11, 8, %p14;
	selp.b32 	%r129, 31744, 32640, %p14;
	setp.ne.b32 	%p16, %r126, 2047;
	@%p16 bra 	$L__BB27_273;
	setp.eq.b64 	%p17, %rd81, 0;
	add.s32 	%r325, %r127, -2;
	mov.b32 	%r326, 1;
	shl.b32 	%r327, %r326, %r325;
	selp.b32 	%r328, 0, %r327, %p17;
	or.b32 	%r329, %r328, %r129;
	or.b32 	%r330, %r329, %r125;
	cvt.u16.u32 	%rs12, %r330;
	bra.uni 	$L__BB27_283;
$L__BB27_111:
	ld.local.b32 	%r961, [%rd1];
	ld.local.b32 	%r962, [%rd2];
	mul.rn.f32 	%r1440, %r961, %r962;
	and.b32 	%r963, %r1396, -2;
	setp.ne.b32 	%p414, %r963, 12;
	@%p414 bra 	$L__BB27_664;
	cvt.f64.f32 	%rd31, %r1440;
	shr.u64 	%rd33, %rd31, 48;
	cvt.u32.u64 	%r964, %rd33;
	and.b32 	%r47, %r964, 32768;
	shr.u64 	%rd607, %rd31, 52;
	cvt.u32.u64 	%r965, %rd607;
	and.b32 	%r48, %r965, 2047;
	setp.eq.b32 	%p416, %r48, 0;
	@%p416 bra 	$L__BB27_115;
	and.b64 	%rd32, %rd31, 4503599627370495;
	setp.eq.b32 	%p415, %r1396, 12;
	selp.b32 	%r49, 11, 8, %p415;
	selp.b32 	%r51, 31744, 32640, %p415;
	setp.ne.b32 	%p417, %r48, 2047;
	@%p417 bra 	$L__BB27_116;
	setp.eq.b64 	%p418, %rd32, 0;
	add.s32 	%r966, %r49, -2;
	mov.b32 	%r967, 1;
	shl.b32 	%r968, %r967, %r966;
	selp.b32 	%r969, 0, %r968, %p418;
	or.b32 	%r970, %r969, %r51;
	or.b32 	%r971, %r970, %r47;
	cvt.u16.u32 	%rs5, %r971;
	bra.uni 	$L__BB27_126;
$L__BB27_292:
	div.rn.f32 	%r1414, %r137, %r136;
	@%p677 bra 	$L__BB27_315;
	cvt.f64.f32 	%rd87, %r1414;
	shr.u64 	%rd89, %rd87, 48;
	cvt.u32.u64 	%r362, %rd89;
	and.b32 	%r138, %r362, 32768;
	shr.u64 	%rd223, %rd87, 52;
	cvt.u32.u64 	%r363, %rd223;
	and.b32 	%r139, %r363, 2047;
	setp.eq.b32 	%p39, %r139, 0;
	@%p39 bra 	$L__BB27_296;
	and.b64 	%rd88, %rd87, 4503599627370495;
	setp.eq.b32 	%p38, %r1396, 12;
	selp.b32 	%r140, 11, 8, %p38;
	selp.b32 	%r142, 31744, 32640, %p38;
	setp.ne.b32 	%p40, %r139, 2047;
	@%p40 bra 	$L__BB27_297;
	setp.eq.b64 	%p41, %rd88, 0;
	add.s32 	%r364, %r140, -2;
	mov.b32 	%r365, 1;
	shl.b32 	%r366, %r365, %r364;
	selp.b32 	%r367, 0, %r366, %p41;
	or.b32 	%r368, %r367, %r142;
	or.b32 	%r369, %r368, %r138;
	cvt.u16.u32 	%rs13, %r369;
	bra.uni 	$L__BB27_307;
$L__BB27_68:
	cvt.u16.u32 	%rs3, %r25;
	bra.uni 	$L__BB27_79;
$L__BB27_26:
	cvt.u16.u32 	%rs1, %r2;
	bra.uni 	$L__BB27_37;
$L__BB27_69:
	selp.b32 	%r1241, -14, -126, %p578;
	add.s32 	%r30, %r26, -1023;
	or.b64 	%rd20, %rd18, 4503599627370496;
	setp.ge.s32 	%p582, %r30, %r1241;
	@%p582 bra 	$L__BB27_75;
	and.b64 	%rd21, %rd19, 32768;
	selp.b32 	%r1251, 28, -81, %p578;
	sub.s32 	%r31, %r1251, %r30;
	setp.gt.s32 	%p590, %r31, 0;
	@%p590 bra 	$L__BB27_72;
	bra.uni 	$L__BB27_71;
$L__BB27_72:
	setp.gt.u32 	%p591, %r31, 63;
	mov.b64 	%rd884, 0;
	@%p591 bra 	$L__BB27_74;
	shr.u64 	%rd799, %rd20, %r31;
	mov.b64 	%rd800, -1;
	shl.b64 	%rd801, %rd800, %r31;
	not.b64 	%rd802, %rd801;
	and.b64 	%rd803, %rd20, %rd802;
	add.s32 	%r1252, %r31, -1;
	mov.b64 	%rd804, 1;
	shl.b64 	%rd805, %rd804, %r1252;
	setp.gt.u64 	%p592, %rd803, %rd805;
	setp.eq.b64 	%p593, %rd803, %rd805;
	and.b64 	%rd806, %rd799, 1;
	setp.ne.b64 	%p594, %rd806, 0;
	and.pred 	%p595, %p593, %p594;
	or.pred 	%p596, %p592, %p595;
	selp.b64 	%rd807, 1, 0, %p596;
	add.s64 	%rd884, %rd799, %rd807;
	bra.uni 	$L__BB27_74;
$L__BB27_27:
	selp.b32 	%r1319, -14, -126, %p625;
	add.s32 	%r7, %r3, -1023;
	or.b64 	%rd6, %rd4, 4503599627370496;
	setp.ge.s32 	%p629, %r7, %r1319;
	@%p629 bra 	$L__BB27_33;
	and.b64 	%rd7, %rd5, 32768;
	selp.b32 	%r1329, 28, -81, %p625;
	sub.s32 	%r8, %r1329, %r7;
	setp.gt.s32 	%p637, %r8, 0;
	@%p637 bra 	$L__BB27_30;
	bra.uni 	$L__BB27_29;
$L__BB27_30:
	setp.gt.u32 	%p638, %r8, 63;
	mov.b64 	%rd882, 0;
	@%p638 bra 	$L__BB27_32;
	shr.u64 	%rd847, %rd6, %r8;
	mov.b64 	%rd848, -1;
	shl.b64 	%rd849, %rd848, %r8;
	not.b64 	%rd850, %rd849;
	and.b64 	%rd851, %rd6, %rd850;
	add.s32 	%r1330, %r8, -1;
	mov.b64 	%rd852, 1;
	shl.b64 	%rd853, %rd852, %r1330;
	setp.gt.u64 	%p639, %rd851, %rd853;
	setp.eq.b64 	%p640, %rd851, %rd853;
	and.b64 	%rd854, %rd847, 1;
	setp.ne.b64 	%p641, %rd854, 0;
	and.pred 	%p642, %p640, %p641;
	or.pred 	%p643, %p639, %p642;
	selp.b64 	%rd855, 1, 0, %p643;
	add.s64 	%rd882, %rd847, %rd855;
	bra.uni 	$L__BB27_32;
$L__BB27_272:
	cvt.u16.u32 	%rs12, %r125;
	bra.uni 	$L__BB27_283;
$L__BB27_138:
	cvt.u16.u32 	%rs6, %r59;
	bra.uni 	$L__BB27_149;
$L__BB27_115:
	cvt.u16.u32 	%rs5, %r47;
	bra.uni 	$L__BB27_126;
$L__BB27_273:
	selp.b32 	%r331, -14, -126, %p14;
	add.s32 	%r130, %r126, -1023;
	or.b64 	%rd83, %rd81, 4503599627370496;
	setp.ge.s32 	%p18, %r130, %r331;
	@%p18 bra 	$L__BB27_279;
	and.b64 	%rd84, %rd82, 32768;
	selp.b32 	%r341, 28, -81, %p14;
	sub.s32 	%r131, %r341, %r130;
	setp.gt.s32 	%p26, %r131, 0;
	@%p26 bra 	$L__BB27_276;
	bra.uni 	$L__BB27_275;
$L__BB27_276:
	setp.gt.u32 	%p27, %r131, 63;
	mov.b64 	%rd893, 0;
	@%p27 bra 	$L__BB27_278;
	shr.u64 	%rd213, %rd83, %r131;
	mov.b64 	%rd214, -1;
	shl.b64 	%rd215, %rd214, %r131;
	not.b64 	%rd216, %rd215;
	and.b64 	%rd217, %rd83, %rd216;
	add.s32 	%r342, %r131, -1;
	mov.b64 	%rd218, 1;
	shl.b64 	%rd219, %rd218, %r342;
	setp.gt.u64 	%p28, %rd217, %rd219;
	setp.eq.b64 	%p29, %rd217, %rd219;
	and.b64 	%rd220, %rd213, 1;
	setp.ne.b64 	%p30, %rd220, 0;
	and.pred 	%p31, %p29, %p30;
	or.pred 	%p32, %p28, %p31;
	selp.b64 	%rd221, 1, 0, %p32;
	add.s64 	%rd893, %rd213, %rd221;
	bra.uni 	$L__BB27_278;
$L__BB27_75:
	selp.b32 	%r28, 15, 127, %p578;
	sub.s32 	%r1242, 53, %r27;
	shr.u64 	%rd786, %rd20, %r1242;
	mov.b64 	%rd787, -1;
	shl.b64 	%rd788, %rd787, %r1242;
	not.b64 	%rd789, %rd788;
	and.b64 	%rd790, %rd17, %rd789;
	sub.s32 	%r1243, 52, %r27;
	mov.b64 	%rd791, 1;
	shl.b64 	%rd792, %rd791, %r1243;
	setp.gt.u64 	%p583, %rd790, %rd792;
	setp.eq.b64 	%p584, %rd790, %rd792;
	and.b64 	%rd793, %rd786, 1;
	setp.ne.b64 	%p585, %rd793, 0;
	and.pred 	%p586, %p584, %p585;
	or.pred 	%p587, %p583, %p586;
	selp.b64 	%rd794, 1, 0, %p587;
	add.s64 	%rd22, %rd786, %rd794;
	shl.b64 	%rd23, %rd791, %r27;
	setp.eq.b64 	%p588, %rd22, %rd23;
	add.s32 	%r1244, %r26, -1022;
	selp.b32 	%r32, %r1244, %r30, %p588;
	setp.le.s32 	%p589, %r32, %r28;
	@%p589 bra 	$L__BB27_77;
	or.b32 	%r1399, %r25, %r29;
	bra.uni 	$L__BB27_78;
$L__BB27_139:
	selp.b32 	%r1017, -14, -126, %p439;
	add.s32 	%r64, %r60, -1023;
	or.b64 	%rd41, %rd39, 4503599627370496;
	setp.ge.s32 	%p443, %r64, %r1017;
	@%p443 bra 	$L__BB27_145;
	and.b64 	%rd42, %rd40, 32768;
	selp.b32 	%r1027, 28, -81, %p439;
	sub.s32 	%r65, %r1027, %r64;
)QPTX";
        result += R"QPTX(
	setp.gt.s32 	%p451, %r65, 0;
	@%p451 bra 	$L__BB27_142;
	bra.uni 	$L__BB27_141;
$L__BB27_142:
	setp.gt.u32 	%p452, %r65, 63;
	mov.b64 	%rd887, 0;
	@%p452 bra 	$L__BB27_144;
	shr.u64 	%rd652, %rd41, %r65;
	mov.b64 	%rd653, -1;
	shl.b64 	%rd654, %rd653, %r65;
	not.b64 	%rd655, %rd654;
	and.b64 	%rd656, %rd41, %rd655;
	add.s32 	%r1028, %r65, -1;
	mov.b64 	%rd657, 1;
	shl.b64 	%rd658, %rd657, %r1028;
	setp.gt.u64 	%p453, %rd656, %rd658;
	setp.eq.b64 	%p454, %rd656, %rd658;
	and.b64 	%rd659, %rd652, 1;
	setp.ne.b64 	%p455, %rd659, 0;
	and.pred 	%p456, %p454, %p455;
	or.pred 	%p457, %p453, %p456;
	selp.b64 	%rd660, 1, 0, %p457;
	add.s64 	%rd887, %rd652, %rd660;
	bra.uni 	$L__BB27_144;
$L__BB27_116:
	selp.b32 	%r972, -14, -126, %p415;
	add.s32 	%r52, %r48, -1023;
	or.b64 	%rd34, %rd32, 4503599627370496;
	setp.ge.s32 	%p419, %r52, %r972;
	@%p419 bra 	$L__BB27_122;
	and.b64 	%rd35, %rd33, 32768;
	selp.b32 	%r982, 28, -81, %p415;
	sub.s32 	%r53, %r982, %r52;
	setp.gt.s32 	%p427, %r53, 0;
	@%p427 bra 	$L__BB27_119;
	bra.uni 	$L__BB27_118;
$L__BB27_119:
	setp.gt.u32 	%p428, %r53, 63;
	mov.b64 	%rd886, 0;
	@%p428 bra 	$L__BB27_121;
	shr.u64 	%rd621, %rd34, %r53;
	mov.b64 	%rd622, -1;
	shl.b64 	%rd623, %rd622, %r53;
	not.b64 	%rd624, %rd623;
	and.b64 	%rd625, %rd34, %rd624;
	add.s32 	%r983, %r53, -1;
	mov.b64 	%rd626, 1;
	shl.b64 	%rd627, %rd626, %r983;
	setp.gt.u64 	%p429, %rd625, %rd627;
	setp.eq.b64 	%p430, %rd625, %rd627;
	and.b64 	%rd628, %rd621, 1;
	setp.ne.b64 	%p431, %rd628, 0;
	and.pred 	%p432, %p430, %p431;
	or.pred 	%p433, %p429, %p432;
	selp.b64 	%rd629, 1, 0, %p433;
	add.s64 	%rd886, %rd621, %rd629;
	bra.uni 	$L__BB27_121;
$L__BB27_33:
	selp.b32 	%r5, 15, 127, %p625;
	sub.s32 	%r1320, 53, %r4;
	shr.u64 	%rd834, %rd6, %r1320;
	mov.b64 	%rd835, -1;
	shl.b64 	%rd836, %rd835, %r1320;
	not.b64 	%rd837, %rd836;
	and.b64 	%rd838, %rd3, %rd837;
	sub.s32 	%r1321, 52, %r4;
	mov.b64 	%rd839, 1;
	shl.b64 	%rd840, %rd839, %r1321;
	setp.gt.u64 	%p630, %rd838, %rd840;
	setp.eq.b64 	%p631, %rd838, %rd840;
	and.b64 	%rd841, %rd834, 1;
	setp.ne.b64 	%p632, %rd841, 0;
	and.pred 	%p633, %p631, %p632;
	or.pred 	%p634, %p630, %p633;
	selp.b64 	%rd842, 1, 0, %p634;
	add.s64 	%rd8, %rd834, %rd842;
	shl.b64 	%rd9, %rd839, %r4;
	setp.eq.b64 	%p635, %rd8, %rd9;
	add.s32 	%r1322, %r3, -1022;
	selp.b32 	%r9, %r1322, %r7, %p635;
	setp.le.s32 	%p636, %r9, %r5;
	@%p636 bra 	$L__BB27_35;
	or.b32 	%r1397, %r2, %r6;
	bra.uni 	$L__BB27_36;
$L__BB27_458:
	cvt.u16.u32 	%rs20, %r217;
	bra.uni 	$L__BB27_469;
$L__BB27_296:
	cvt.u16.u32 	%rs13, %r138;
	bra.uni 	$L__BB27_307;
$L__BB27_459:
	selp.b32 	%r629, -14, -126, %p199;
	add.s32 	%r222, %r218, -1023;
	or.b64 	%rd139, %rd137, 4503599627370496;
	setp.ge.s32 	%p203, %r222, %r629;
	@%p203 bra 	$L__BB27_465;
	and.b64 	%rd140, %rd138, 32768;
	selp.b32 	%r639, 28, -81, %p199;
	sub.s32 	%r223, %r639, %r222;
	setp.gt.s32 	%p211, %r223, 0;
	@%p211 bra 	$L__BB27_462;
	bra.uni 	$L__BB27_461;
$L__BB27_462:
	setp.gt.u32 	%p212, %r223, 63;
	mov.b64 	%rd901, 0;
	@%p212 bra 	$L__BB27_464;
	shr.u64 	%rd405, %rd139, %r223;
	mov.b64 	%rd406, -1;
	shl.b64 	%rd407, %rd406, %r223;
	not.b64 	%rd408, %rd407;
	and.b64 	%rd409, %rd139, %rd408;
	add.s32 	%r640, %r223, -1;
	mov.b64 	%rd410, 1;
	shl.b64 	%rd411, %rd410, %r640;
	setp.gt.u64 	%p213, %rd409, %rd411;
	setp.eq.b64 	%p214, %rd409, %rd411;
	and.b64 	%rd412, %rd405, 1;
	setp.ne.b64 	%p215, %rd412, 0;
	and.pred 	%p216, %p214, %p215;
	or.pred 	%p217, %p213, %p216;
	selp.b64 	%rd413, 1, 0, %p217;
	add.s64 	%rd901, %rd405, %rd413;
	bra.uni 	$L__BB27_464;
$L__BB27_297:
	selp.b32 	%r370, -14, -126, %p38;
	add.s32 	%r143, %r139, -1023;
	or.b64 	%rd90, %rd88, 4503599627370496;
	setp.ge.s32 	%p42, %r143, %r370;
	@%p42 bra 	$L__BB27_303;
	and.b64 	%rd91, %rd89, 32768;
	selp.b32 	%r380, 28, -81, %p38;
	sub.s32 	%r144, %r380, %r143;
	setp.gt.s32 	%p50, %r144, 0;
	@%p50 bra 	$L__BB27_300;
	bra.uni 	$L__BB27_299;
$L__BB27_300:
	setp.gt.u32 	%p51, %r144, 63;
	mov.b64 	%rd894, 0;
	@%p51 bra 	$L__BB27_302;
	shr.u64 	%rd237, %rd90, %r144;
	mov.b64 	%rd238, -1;
	shl.b64 	%rd239, %rd238, %r144;
	not.b64 	%rd240, %rd239;
	and.b64 	%rd241, %rd90, %rd240;
	add.s32 	%r381, %r144, -1;
	mov.b64 	%rd242, 1;
	shl.b64 	%rd243, %rd242, %r381;
	setp.gt.u64 	%p52, %rd241, %rd243;
	setp.eq.b64 	%p53, %rd241, %rd243;
	and.b64 	%rd244, %rd237, 1;
	setp.ne.b64 	%p54, %rd244, 0;
	and.pred 	%p55, %p53, %p54;
	or.pred 	%p56, %p52, %p55;
	selp.b64 	%rd245, 1, 0, %p56;
	add.s64 	%rd894, %rd237, %rd245;
	bra.uni 	$L__BB27_302;
$L__BB27_279:
	selp.b32 	%r128, 15, 127, %p14;
	sub.s32 	%r332, 53, %r127;
	shr.u64 	%rd200, %rd83, %r332;
	mov.b64 	%rd201, -1;
	shl.b64 	%rd202, %rd201, %r332;
	not.b64 	%rd203, %rd202;
	and.b64 	%rd204, %rd80, %rd203;
	sub.s32 	%r333, 52, %r127;
	mov.b64 	%rd205, 1;
	shl.b64 	%rd206, %rd205, %r333;
	setp.gt.u64 	%p19, %rd204, %rd206;
	setp.eq.b64 	%p20, %rd204, %rd206;
	and.b64 	%rd207, %rd200, 1;
	setp.ne.b64 	%p21, %rd207, 0;
	and.pred 	%p22, %p20, %p21;
	or.pred 	%p23, %p19, %p22;
	selp.b64 	%rd208, 1, 0, %p23;
	add.s64 	%rd85, %rd200, %rd208;
	shl.b64 	%rd86, %rd205, %r127;
	setp.eq.b64 	%p24, %rd85, %rd86;
	add.s32 	%r334, %r126, -1022;
	selp.b32 	%r132, %r334, %r130, %p24;
	setp.le.s32 	%p25, %r132, %r128;
	@%p25 bra 	$L__BB27_281;
	or.b32 	%r1412, %r125, %r129;
	bra.uni 	$L__BB27_282;
$L__BB27_77:
	selp.b32 	%r1245, 1, 0, %p588;
	shr.u64 	%rd795, %rd22, %r1245;
	add.s32 	%r1246, %r32, %r28;
	add.s32 	%r1247, %r27, -1;
	shl.b32 	%r1248, %r1246, %r1247;
	shl.b64 	%rd796, %rd787, %r1247;
	not.b64 	%rd797, %rd796;
	and.b64 	%rd798, %rd795, %rd797;
	cvt.u32.u64 	%r1249, %rd798;
	or.b32 	%r1250, %r1248, %r1249;
	or.b32 	%r1399, %r1250, %r25;
$L__BB27_78:
	cvt.u16.u32 	%rs3, %r1399;
	bra.uni 	$L__BB27_79;
$L__BB27_145:
	selp.b32 	%r62, 15, 127, %p439;
	sub.s32 	%r1018, 53, %r61;
	shr.u64 	%rd639, %rd41, %r1018;
	mov.b64 	%rd640, -1;
	shl.b64 	%rd641, %rd640, %r1018;
	not.b64 	%rd642, %rd641;
	and.b64 	%rd643, %rd38, %rd642;
	sub.s32 	%r1019, 52, %r61;
	mov.b64 	%rd644, 1;
	shl.b64 	%rd645, %rd644, %r1019;
	setp.gt.u64 	%p444, %rd643, %rd645;
	setp.eq.b64 	%p445, %rd643, %rd645;
	and.b64 	%rd646, %rd639, 1;
	setp.ne.b64 	%p446, %rd646, 0;
	and.pred 	%p447, %p445, %p446;
	or.pred 	%p448, %p444, %p447;
	selp.b64 	%rd647, 1, 0, %p448;
	add.s64 	%rd43, %rd639, %rd647;
	shl.b64 	%rd44, %rd644, %r61;
	setp.eq.b64 	%p449, %rd43, %rd44;
	add.s32 	%r1020, %r60, -1022;
	selp.b32 	%r66, %r1020, %r64, %p449;
	setp.le.s32 	%p450, %r66, %r62;
	@%p450 bra 	$L__BB27_147;
	or.b32 	%r1402, %r59, %r63;
	bra.uni 	$L__BB27_148;
$L__BB27_122:
	selp.b32 	%r50, 15, 127, %p415;
	sub.s32 	%r973, 53, %r49;
	shr.u64 	%rd608, %rd34, %r973;
	mov.b64 	%rd609, -1;
	shl.b64 	%rd610, %rd609, %r973;
	not.b64 	%rd611, %rd610;
	and.b64 	%rd612, %rd31, %rd611;
	sub.s32 	%r974, 52, %r49;
	mov.b64 	%rd613, 1;
	shl.b64 	%rd614, %rd613, %r974;
	setp.gt.u64 	%p420, %rd612, %rd614;
	setp.eq.b64 	%p421, %rd612, %rd614;
	and.b64 	%rd615, %rd608, 1;
	setp.ne.b64 	%p422, %rd615, 0;
	and.pred 	%p423, %p421, %p422;
	or.pred 	%p424, %p420, %p423;
	selp.b64 	%rd616, 1, 0, %p424;
	add.s64 	%rd36, %rd608, %rd616;
	shl.b64 	%rd37, %rd613, %r49;
	setp.eq.b64 	%p425, %rd36, %rd37;
	add.s32 	%r975, %r48, -1022;
	selp.b32 	%r54, %r975, %r52, %p425;
	setp.le.s32 	%p426, %r54, %r50;
	@%p426 bra 	$L__BB27_124;
	or.b32 	%r1401, %r47, %r51;
	bra.uni 	$L__BB27_125;
$L__BB27_35:
	selp.b32 	%r1323, 1, 0, %p635;
	shr.u64 	%rd843, %rd8, %r1323;
	add.s32 	%r1324, %r9, %r5;
	add.s32 	%r1325, %r4, -1;
	shl.b32 	%r1326, %r1324, %r1325;
	shl.b64 	%rd844, %rd835, %r1325;
	not.b64 	%rd845, %rd844;
	and.b64 	%rd846, %rd843, %rd845;
	cvt.u32.u64 	%r1327, %rd846;
	or.b32 	%r1328, %r1326, %r1327;
	or.b32 	%r1397, %r1328, %r2;
$L__BB27_36:
	cvt.u16.u32 	%rs1, %r1397;
	bra.uni 	$L__BB27_37;
$L__BB27_71:
	neg.s32 	%r1253, %r31;
	shl.b64 	%rd884, %rd20, %r1253;
$L__BB27_74:
	or.b64 	%rd808, %rd884, %rd21;
	cvt.u16.u64 	%rs3, %rd808;
$L__BB27_79:
	setp.ne.b32 	%p597, %r1396, 13;
	cvt.u32.u16 	%r33, %rs3;
	@%p597 bra 	$L__BB27_81;
	shl.b32 	%r1440, %r33, 16;
	bra.uni 	$L__BB27_87;
$L__BB27_81:
	cvt.s32.s16 	%r1254, %rs3;
	and.b32 	%r1440, %r1254, -2147483648;
	bfe.u32 	%r34, %r33, 10, 5;
	setp.eq.b32 	%p598, %r34, 31;
	@%p598 bra 	$L__BB27_85;
	and.b32 	%r35, %r33, 1023;
	setp.ne.b32 	%p599, %r34, 0;
	@%p599 bra 	$L__BB27_86;
	setp.eq.b32 	%p600, %r35, 0;
	@%p600 bra 	$L__BB27_87;
	clz.b32 	%r1257, %r35;
	xor.b32 	%r1258, %r1257, 31;
	sub.s32 	%r1259, 9, %r1258;
	shl.b32 	%r1260, %r33, %r1259;
	shl.b32 	%r1261, %r1258, 23;
	shl.b32 	%r1262, %r1260, 14;
	and.b32 	%r1263, %r1262, 8372224;
	add.s32 	%r1264, %r1261, %r1440;
	add.s32 	%r1265, %r1264, %r1263;
	add.s32 	%r1440, %r1265, 864026624;
	bra.uni 	$L__BB27_87;
$L__BB27_85:
	shl.b32 	%r1255, %r33, 13;
	or.b32 	%r1256, %r1440, %r1255;
	or.b32 	%r1440, %r1256, 2139095040;
	bra.uni 	$L__BB27_87;
$L__BB27_86:
	shl.b32 	%r1266, %r34, 23;
	shl.b32 	%r1267, %r35, 13;
	or.b32 	%r1268, %r1266, %r1267;
	add.s32 	%r1269, %r1268, %r1440;
	add.s32 	%r1440, %r1269, 939524096;
$L__BB27_87:
	ld.local.b32 	%r1270, [%rd1+4];
	ld.local.b32 	%r1271, [%rd2+4];
	sub.rn.f32 	%r1439, %r1270, %r1271;
	@%p577 bra 	$L__BB27_664;
	cvt.f64.f32 	%rd24, %r1439;
	shr.u64 	%rd26, %rd24, 48;
	cvt.u32.u64 	%r1272, %rd26;
	and.b32 	%r36, %r1272, 32768;
	shr.u64 	%rd809, %rd24, 52;
	cvt.u32.u64 	%r1273, %rd809;
	and.b32 	%r37, %r1273, 2047;
	setp.eq.b32 	%p602, %r37, 0;
	@%p602 bra 	$L__BB27_91;
	and.b64 	%rd25, %rd24, 4503599627370495;
	setp.eq.b32 	%p601, %r1396, 12;
	selp.b32 	%r38, 11, 8, %p601;
	selp.b32 	%r40, 31744, 32640, %p601;
	setp.ne.b32 	%p603, %r37, 2047;
	@%p603 bra 	$L__BB27_92;
	setp.eq.b64 	%p604, %rd25, 0;
	add.s32 	%r1274, %r38, -2;
	mov.b32 	%r1275, 1;
	shl.b32 	%r1276, %r1275, %r1274;
	selp.b32 	%r1277, 0, %r1276, %p604;
	or.b32 	%r1278, %r1277, %r40;
	or.b32 	%r1279, %r1278, %r36;
	cvt.u16.u32 	%rs4, %r1279;
	bra.uni 	$L__BB27_102;
$L__BB27_91:
	cvt.u16.u32 	%rs4, %r36;
	bra.uni 	$L__BB27_102;
$L__BB27_92:
	selp.b32 	%r1280, -14, -126, %p601;
	add.s32 	%r41, %r37, -1023;
	or.b64 	%rd27, %rd25, 4503599627370496;
	setp.ge.s32 	%p605, %r41, %r1280;
	@%p605 bra 	$L__BB27_98;
	and.b64 	%rd28, %rd26, 32768;
	selp.b32 	%r1290, 28, -81, %p601;
	sub.s32 	%r42, %r1290, %r41;
	setp.gt.s32 	%p613, %r42, 0;
	@%p613 bra 	$L__BB27_95;
	bra.uni 	$L__BB27_94;
$L__BB27_95:
	setp.gt.u32 	%p614, %r42, 63;
	mov.b64 	%rd885, 0;
	@%p614 bra 	$L__BB27_97;
	shr.u64 	%rd823, %rd27, %r42;
	mov.b64 	%rd824, -1;
	shl.b64 	%rd825, %rd824, %r42;
	not.b64 	%rd826, %rd825;
	and.b64 	%rd827, %rd27, %rd826;
	add.s32 	%r1291, %r42, -1;
	mov.b64 	%rd828, 1;
	shl.b64 	%rd829, %rd828, %r1291;
	setp.gt.u64 	%p615, %rd827, %rd829;
	setp.eq.b64 	%p616, %rd827, %rd829;
	and.b64 	%rd830, %rd823, 1;
	setp.ne.b64 	%p617, %rd830, 0;
	and.pred 	%p618, %p616, %p617;
	or.pred 	%p619, %p615, %p618;
	selp.b64 	%rd831, 1, 0, %p619;
	add.s64 	%rd885, %rd823, %rd831;
	bra.uni 	$L__BB27_97;
$L__BB27_98:
	selp.b32 	%r39, 15, 127, %p601;
	sub.s32 	%r1281, 53, %r38;
	shr.u64 	%rd810, %rd27, %r1281;
	mov.b64 	%rd811, -1;
	shl.b64 	%rd812, %rd811, %r1281;
	not.b64 	%rd813, %rd812;
	and.b64 	%rd814, %rd24, %rd813;
	sub.s32 	%r1282, 52, %r38;
	mov.b64 	%rd815, 1;
	shl.b64 	%rd816, %rd815, %r1282;
	setp.gt.u64 	%p606, %rd814, %rd816;
	setp.eq.b64 	%p607, %rd814, %rd816;
	and.b64 	%rd817, %rd810, 1;
	setp.ne.b64 	%p608, %rd817, 0;
	and.pred 	%p609, %p607, %p608;
	or.pred 	%p610, %p606, %p609;
	selp.b64 	%rd818, 1, 0, %p610;
	add.s64 	%rd29, %rd810, %rd818;
	shl.b64 	%rd30, %rd815, %r38;
	setp.eq.b64 	%p611, %rd29, %rd30;
	add.s32 	%r1283, %r37, -1022;
	selp.b32 	%r43, %r1283, %r41, %p611;
	setp.le.s32 	%p612, %r43, %r39;
	@%p612 bra 	$L__BB27_100;
	or.b32 	%r1400, %r36, %r40;
	bra.uni 	$L__BB27_101;
$L__BB27_100:
	selp.b32 	%r1284, 1, 0, %p611;
	shr.u64 	%rd819, %rd29, %r1284;
	add.s32 	%r1285, %r43, %r39;
	add.s32 	%r1286, %r38, -1;
	shl.b32 	%r1287, %r1285, %r1286;
	shl.b64 	%rd820, %rd811, %r1286;
	not.b64 	%rd821, %rd820;
	and.b64 	%rd822, %rd819, %rd821;
	cvt.u32.u64 	%r1288, %rd822;
	or.b32 	%r1289, %r1287, %r1288;
	or.b32 	%r1400, %r1289, %r36;
$L__BB27_101:
	cvt.u16.u32 	%rs4, %r1400;
	bra.uni 	$L__BB27_102;
$L__BB27_94:
	neg.s32 	%r1292, %r42;
	shl.b64 	%rd885, %rd27, %r1292;
$L__BB27_97:
	or.b64 	%rd832, %rd885, %rd28;
	cvt.u16.u64 	%rs4, %rd832;
$L__BB27_102:
	setp.ne.b32 	%p620, %r1396, 13;
	cvt.u32.u16 	%r44, %rs4;
	@%p620 bra 	$L__BB27_104;
	shl.b32 	%r1439, %r44, 16;
	bra.uni 	$L__BB27_664;
$L__BB27_104:
	cvt.s32.s16 	%r1293, %rs4;
	and.b32 	%r1439, %r1293, -2147483648;
	bfe.u32 	%r45, %r44, 10, 5;
	setp.eq.b32 	%p621, %r45, 31;
	@%p621 bra 	$L__BB27_108;
	and.b32 	%r46, %r44, 1023;
	setp.ne.b32 	%p622, %r45, 0;
	@%p622 bra 	$L__BB27_109;
	setp.eq.b32 	%p623, %r46, 0;
	@%p623 bra 	$L__BB27_664;
	clz.b32 	%r1296, %r46;
	xor.b32 	%r1297, %r1296, 31;
	sub.s32 	%r1298, 9, %r1297;
	shl.b32 	%r1299, %r44, %r1298;
	shl.b32 	%r1300, %r1297, 23;
	shl.b32 	%r1301, %r1299, 14;
	and.b32 	%r1302, %r1301, 8372224;
	add.s32 	%r1303, %r1300, %r1439;
	add.s32 	%r1304, %r1303, %r1302;
	add.s32 	%r1439, %r1304, 864026624;
	bra.uni 	$L__BB27_664;
$L__BB27_108:
	shl.b32 	%r1294, %r44, 13;
	or.b32 	%r1295, %r1439, %r1294;
	or.b32 	%r1439, %r1295, 2139095040;
	bra.uni 	$L__BB27_664;
$L__BB27_109:
	shl.b32 	%r1305, %r45, 23;
	shl.b32 	%r1306, %r46, 13;
	or.b32 	%r1307, %r1305, %r1306;
	add.s32 	%r1308, %r1307, %r1439;
	add.s32 	%r1439, %r1308, 939524096;
	bra.uni 	$L__BB27_664;
$L__BB27_29:
	neg.s32 	%r1331, %r8;
	shl.b64 	%rd882, %rd6, %r1331;
$L__BB27_32:
	or.b64 	%rd856, %rd882, %rd7;
	cvt.u16.u64 	%rs1, %rd856;
$L__BB27_37:
	setp.ne.b32 	%p644, %r1396, 13;
	cvt.u32.u16 	%r10, %rs1;
	@%p644 bra 	$L__BB27_39;
	shl.b32 	%r1440, %r10, 16;
	bra.uni 	$L__BB27_45;
$L__BB27_39:
	cvt.s32.s16 	%r1332, %rs1;
	and.b32 	%r1440, %r1332, -2147483648;
	bfe.u32 	%r11, %r10, 10, 5;
	setp.eq.b32 	%p645, %r11, 31;
	@%p645 bra 	$L__BB27_43;
	and.b32 	%r12, %r10, 1023;
	setp.ne.b32 	%p646, %r11, 0;
	@%p646 bra 	$L__BB27_44;
	setp.eq.b32 	%p647, %r12, 0;
	@%p647 bra 	$L__BB27_45;
	clz.b32 	%r1335, %r12;
	xor.b32 	%r1336, %r1335, 31;
	sub.s32 	%r1337, 9, %r1336;
	shl.b32 	%r1338, %r10, %r1337;
	shl.b32 	%r1339, %r1336, 23;
	shl.b32 	%r1340, %r1338, 14;
	and.b32 	%r1341, %r1340, 8372224;
	add.s32 	%r1342, %r1339, %r1440;
	add.s32 	%r1343, %r1342, %r1341;
	add.s32 	%r1440, %r1343, 864026624;
	bra.uni 	$L__BB27_45;
$L__BB27_43:
	shl.b32 	%r1333, %r10, 13;
	or.b32 	%r1334, %r1440, %r1333;
	or.b32 	%r1440, %r1334, 2139095040;
	bra.uni 	$L__BB27_45;
$L__BB27_44:
	shl.b32 	%r1344, %r11, 23;
	shl.b32 	%r1345, %r12, 13;
	or.b32 	%r1346, %r1344, %r1345;
	add.s32 	%r1347, %r1346, %r1440;
	add.s32 	%r1440, %r1347, 939524096;
$L__BB27_45:
	ld.local.b32 	%r1348, [%rd1+4];
	ld.local.b32 	%r1349, [%rd2+4];
	add.rn.f32 	%r1439, %r1348, %r1349;
	@%p624 bra 	$L__BB27_664;
	cvt.f64.f32 	%rd10, %r1439;
	shr.u64 	%rd12, %rd10, 48;
	cvt.u32.u64 	%r1350, %rd12;
	and.b32 	%r13, %r1350, 32768;
	shr.u64 	%rd857, %rd10, 52;
	cvt.u32.u64 	%r1351, %rd857;
	and.b32 	%r14, %r1351, 2047;
	setp.eq.b32 	%p649, %r14, 0;
	@%p649 bra 	$L__BB27_49;
	and.b64 	%rd11, %rd10, 4503599627370495;
	setp.eq.b32 	%p648, %r1396, 12;
	selp.b32 	%r15, 11, 8, %p648;
	selp.b32 	%r17, 31744, 32640, %p648;
	setp.ne.b32 	%p650, %r14, 2047;
	@%p650 bra 	$L__BB27_50;
	setp.eq.b64 	%p651, %rd11, 0;
	add.s32 	%r1352, %r15, -2;
	mov.b32 	%r1353, 1;
	shl.b32 	%r1354, %r1353, %r1352;
	selp.b32 	%r1355, 0, %r1354, %p651;
	or.b32 	%r1356, %r1355, %r17;
	or.b32 	%r1357, %r1356, %r13;
	cvt.u16.u32 	%rs2, %r1357;
	bra.uni 	$L__BB27_60;
$L__BB27_49:
	cvt.u16.u32 	%rs2, %r13;
	bra.uni 	$L__BB27_60;
$L__BB27_50:
	selp.b32 	%r1358, -14, -126, %p648;
	add.s32 	%r18, %r14, -1023;
	or.b64 	%rd13, %rd11, 4503599627370496;
	setp.ge.s32 	%p652, %r18, %r1358;
	@%p652 bra 	$L__BB27_56;
	and.b64 	%rd14, %rd12, 32768;
	selp.b32 	%r1368, 28, -81, %p648;
	sub.s32 	%r19, %r1368, %r18;
	setp.gt.s32 	%p660, %r19, 0;
	@%p660 bra 	$L__BB27_53;
	bra.uni 	$L__BB27_52;
$L__BB27_53:
	setp.gt.u32 	%p661, %r19, 63;
	mov.b64 	%rd883, 0;
	@%p661 bra 	$L__BB27_55;
	shr.u64 	%rd871, %rd13, %r19;
	mov.b64 	%rd872, -1;
	shl.b64 	%rd873, %rd872, %r19;
	not.b64 	%rd874, %rd873;
	and.b64 	%rd875, %rd13, %rd874;
	add.s32 	%r1369, %r19, -1;
	mov.b64 	%rd876, 1;
	shl.b64 	%rd877, %rd876, %r1369;
	setp.gt.u64 	%p662, %rd875, %rd877;
	setp.eq.b64 	%p663, %rd875, %rd877;
	and.b64 	%rd878, %rd871, 1;
	setp.ne.b64 	%p664, %rd878, 0;
	and.pred 	%p665, %p663, %p664;
	or.pred 	%p666, %p662, %p665;
	selp.b64 	%rd879, 1, 0, %p666;
	add.s64 	%rd883, %rd871, %rd879;
	bra.uni 	$L__BB27_55;
$L__BB27_56:
	selp.b32 	%r16, 15, 127, %p648;
	sub.s32 	%r1359, 53, %r15;
	shr.u64 	%rd858, %rd13, %r1359;
	mov.b64 	%rd859, -1;
	shl.b64 	%rd860, %rd859, %r1359;
	not.b64 	%rd861, %rd860;
	and.b64 	%rd862, %rd10, %rd861;
	sub.s32 	%r1360, 52, %r15;
	mov.b64 	%rd863, 1;
	shl.b64 	%rd864, %rd863, %r1360;
	setp.gt.u64 	%p653, %rd862, %rd864;
	setp.eq.b64 	%p654, %rd862, %rd864;
	and.b64 	%rd865, %rd858, 1;
	setp.ne.b64 	%p655, %rd865, 0;
	and.pred 	%p656, %p654, %p655;
	or.pred 	%p657, %p653, %p656;
	selp.b64 	%rd866, 1, 0, %p657;
	add.s64 	%rd15, %rd858, %rd866;
	shl.b64 	%rd16, %rd863, %r15;
	setp.eq.b64 	%p658, %rd15, %rd16;
	add.s32 	%r1361, %r14, -1022;
	selp.b32 	%r20, %r1361, %r18, %p658;
	setp.le.s32 	%p659, %r20, %r16;
	@%p659 bra 	$L__BB27_58;
	or.b32 	%r1398, %r13, %r17;
	bra.uni 	$L__BB27_59;
$L__BB27_58:
	selp.b32 	%r1362, 1, 0, %p658;
	shr.u64 	%rd867, %rd15, %r1362;
	add.s32 	%r1363, %r20, %r16;
	add.s32 	%r1364, %r15, -1;
	shl.b32 	%r1365, %r1363, %r1364;
	shl.b64 	%rd868, %rd859, %r1364;
	not.b64 	%rd869, %rd868;
	and.b64 	%rd870, %rd867, %rd869;
	cvt.u32.u64 	%r1366, %rd870;
	or.b32 	%r1367, %r1365, %r1366;
	or.b32 	%r1398, %r1367, %r13;
$L__BB27_59:
	cvt.u16.u32 	%rs2, %r1398;
	bra.uni 	$L__BB27_60;
$L__BB27_52:
	neg.s32 	%r1370, %r19;
	shl.b64 	%rd883, %rd13, %r1370;
$L__BB27_55:
	or.b64 	%rd880, %rd883, %rd14;
	cvt.u16.u64 	%rs2, %rd880;
$L__BB27_60:
	setp.ne.b32 	%p667, %r1396, 13;
	cvt.u32.u16 	%r21, %rs2;
	@%p667 bra 	$L__BB27_62;
	shl.b32 	%r1439, %r21, 16;
	bra.uni 	$L__BB27_664;
$L__BB27_62:
	cvt.s32.s16 	%r1371, %rs2;
	and.b32 	%r1439, %r1371, -2147483648;
	bfe.u32 	%r22, %r21, 10, 5;
	setp.eq.b32 	%p668, %r22, 31;
	@%p668 bra 	$L__BB27_66;
	and.b32 	%r23, %r21, 1023;
	setp.ne.b32 	%p669, %r22, 0;
	@%p669 bra 	$L__BB27_67;
	setp.eq.b32 	%p670, %r23, 0;
	@%p670 bra 	$L__BB27_664;
	clz.b32 	%r1374, %r23;
	xor.b32 	%r1375, %r1374, 31;
	sub.s32 	%r1376, 9, %r1375;
	shl.b32 	%r1377, %r21, %r1376;
	shl.b32 	%r1378, %r1375, 23;
	shl.b32 	%r1379, %r1377, 14;
	and.b32 	%r1380, %r1379, 8372224;
	add.s32 	%r1381, %r1378, %r1439;
	add.s32 	%r1382, %r1381, %r1380;
	add.s32 	%r1439, %r1382, 864026624;
	bra.uni 	$L__BB27_664;
$L__BB27_66:
	shl.b32 	%r1372, %r21, 13;
	or.b32 	%r1373, %r1439, %r1372;
	or.b32 	%r1439, %r1373, 2139095040;
	bra.uni 	$L__BB27_664;
$L__BB27_67:
	shl.b32 	%r1383, %r22, 23;
	shl.b32 	%r1384, %r23, 13;
	or.b32 	%r1385, %r1383, %r1384;
	add.s32 	%r1386, %r1385, %r1439;
	add.s32 	%r1439, %r1386, 939524096;
	bra.uni 	$L__BB27_664;
$L__BB27_465:
	selp.b32 	%r220, 15, 127, %p199;
	sub.s32 	%r630, 53, %r219;
	shr.u64 	%rd392, %rd139, %r630;
	mov.b64 	%rd393, -1;
	shl.b64 	%rd394, %rd393, %r630;
	not.b64 	%rd395, %rd394;
	and.b64 	%rd396, %rd136, %rd395;
	sub.s32 	%r631, 52, %r219;
	mov.b64 	%rd397, 1;
	shl.b64 	%rd398, %rd397, %r631;
	setp.gt.u64 	%p204, %rd396, %rd398;
	setp.eq.b64 	%p205, %rd396, %rd398;
	and.b64 	%rd399, %rd392, 1;
	setp.ne.b64 	%p206, %rd399, 0;
	and.pred 	%p207, %p205, %p206;
	or.pred 	%p208, %p204, %p207;
	selp.b64 	%rd400, 1, 0, %p208;
	add.s64 	%rd141, %rd392, %rd400;
	shl.b64 	%rd142, %rd397, %r219;
	setp.eq.b64 	%p209, %rd141, %rd142;
	add.s32 	%r632, %r218, -1022;
	selp.b32 	%r224, %r632, %r222, %p209;
	setp.le.s32 	%p210, %r224, %r220;
	@%p210 bra 	$L__BB27_467;
	or.b32 	%r1427, %r217, %r221;
	bra.uni 	$L__BB27_468;
$L__BB27_303:
	selp.b32 	%r141, 15, 127, %p38;
	sub.s32 	%r371, 53, %r140;
	shr.u64 	%rd224, %rd90, %r371;
	mov.b64 	%rd225, -1;
	shl.b64 	%rd226, %rd225, %r371;
	not.b64 	%rd227, %rd226;
	and.b64 	%rd228, %rd87, %rd227;
	sub.s32 	%r372, 52, %r140;
	mov.b64 	%rd229, 1;
	shl.b64 	%rd230, %rd229, %r372;
	setp.gt.u64 	%p43, %rd228, %rd230;
	setp.eq.b64 	%p44, %rd228, %rd230;
	and.b64 	%rd231, %rd224, 1;
	setp.ne.b64 	%p45, %rd231, 0;
	and.pred 	%p46, %p44, %p45;
	or.pred 	%p47, %p43, %p46;
	selp.b64 	%rd232, 1, 0, %p47;
	add.s64 	%rd92, %rd224, %rd232;
	shl.b64 	%rd93, %rd229, %r140;
	setp.eq.b64 	%p48, %rd92, %rd93;
	add.s32 	%r373, %r139, -1022;
	selp.b32 	%r145, %r373, %r143, %p48;
	setp.le.s32 	%p49, %r145, %r141;
	@%p49 bra 	$L__BB27_305;
	or.b32 	%r1413, %r138, %r142;
	bra.uni 	$L__BB27_306;
$L__BB27_281:
	selp.b32 	%r335, 1, 0, %p24;
	shr.u64 	%rd209, %rd85, %r335;
	add.s32 	%r336, %r132, %r128;
	add.s32 	%r337, %r127, -1;
	shl.b32 	%r338, %r336, %r337;
	shl.b64 	%rd210, %rd201, %r337;
	not.b64 	%rd211, %rd210;
	and.b64 	%rd212, %rd209, %rd211;
	cvt.u32.u64 	%r339, %rd212;
	or.b32 	%r340, %r338, %r339;
	or.b32 	%r1412, %r340, %r125;
$L__BB27_282:
	cvt.u16.u32 	%rs12, %r1412;
	bra.uni 	$L__BB27_283;
$L__BB27_147:
	selp.b32 	%r1021, 1, 0, %p449;
	shr.u64 	%rd648, %rd43, %r1021;
	add.s32 	%r1022, %r66, %r62;
	add.s32 	%r1023, %r61, -1;
	shl.b32 	%r1024, %r1022, %r1023;
	shl.b64 	%rd649, %rd640, %r1023;
	not.b64 	%rd650, %rd649;
	and.b64 	%rd651, %rd648, %rd650;
	cvt.u32.u64 	%r1025, %rd651;
	or.b32 	%r1026, %r1024, %r1025;
	or.b32 	%r1402, %r1026, %r59;
$L__BB27_148:
	cvt.u16.u32 	%rs6, %r1402;
	bra.uni 	$L__BB27_149;
$L__BB27_124:
	selp.b32 	%r976, 1, 0, %p425;
	shr.u64 	%rd617, %rd36, %r976;
	add.s32 	%r977, %r54, %r50;
	add.s32 	%r978, %r49, -1;
	shl.b32 	%r979, %r977, %r978;
	shl.b64 	%rd618, %rd609, %r978;
	not.b64 	%rd619, %rd618;
	and.b64 	%rd620, %rd617, %rd619;
	cvt.u32.u64 	%r980, %rd620;
	or.b32 	%r981, %r979, %r980;
	or.b32 	%r1401, %r981, %r47;
$L__BB27_125:
	cvt.u16.u32 	%rs5, %r1401;
	bra.uni 	$L__BB27_126;
$L__BB27_275:
	neg.s32 	%r343, %r131;
	shl.b64 	%rd893, %rd83, %r343;
$L__BB27_278:
	or.b64 	%rd222, %rd893, %rd84;
	cvt.u16.u64 	%rs12, %rd222;
$L__BB27_283:
	setp.ne.b32 	%p33, %r1396, 13;
	cvt.u32.u16 	%r133, %rs12;
	@%p33 bra 	$L__BB27_285;
	shl.b32 	%r1440, %r133, 16;
	bra.uni 	$L__BB27_664;
$L__BB27_285:
	cvt.s32.s16 	%r344, %rs12;
	and.b32 	%r1440, %r344, -2147483648;
	bfe.u32 	%r134, %r133, 10, 5;
	setp.eq.b32 	%p34, %r134, 31;
	@%p34 bra 	$L__BB27_289;
	and.b32 	%r135, %r133, 1023;
	setp.ne.b32 	%p35, %r134, 0;
	@%p35 bra 	$L__BB27_290;
	setp.eq.b32 	%p36, %r135, 0;
	@%p36 bra 	$L__BB27_664;
	clz.b32 	%r347, %r135;
	xor.b32 	%r348, %r347, 31;
	sub.s32 	%r349, 9, %r348;
	shl.b32 	%r350, %r133, %r349;
	shl.b32 	%r351, %r348, 23;
	shl.b32 	%r352, %r350, 14;
	and.b32 	%r353, %r352, 8372224;
	add.s32 	%r354, %r351, %r1440;
	add.s32 	%r355, %r354, %r353;
	add.s32 	%r1440, %r355, 864026624;
	bra.uni 	$L__BB27_664;
$L__BB27_289:
	shl.b32 	%r345, %r133, 13;
	or.b32 	%r346, %r1440, %r345;
	or.b32 	%r1440, %r346, 2139095040;
	bra.uni 	$L__BB27_664;
$L__BB27_290:
	shl.b32 	%r356, %r134, 23;
	shl.b32 	%r357, %r135, 13;
	or.b32 	%r358, %r356, %r357;
	add.s32 	%r359, %r358, %r1440;
	add.s32 	%r1440, %r359, 939524096;
	bra.uni 	$L__BB27_664;
$L__BB27_141:
	neg.s32 	%r1029, %r65;
	shl.b64 	%rd887, %rd41, %r1029;
$L__BB27_144:
	or.b64 	%rd661, %rd887, %rd42;
	cvt.u16.u64 	%rs6, %rd661;
$L__BB27_149:
	setp.ne.b32 	%p458, %r1396, 13;
	cvt.u32.u16 	%r67, %rs6;
	@%p458 bra 	$L__BB27_151;
	shl.b32 	%r1403, %r67, 16;
	bra.uni 	$L__BB27_157;
$L__BB27_151:
	cvt.s32.s16 	%r1030, %rs6;
	and.b32 	%r1403, %r1030, -2147483648;
	bfe.u32 	%r68, %r67, 10, 5;
	setp.eq.b32 	%p459, %r68, 31;
	@%p459 bra 	$L__BB27_155;
	and.b32 	%r69, %r67, 1023;
	setp.ne.b32 	%p460, %r68, 0;
	@%p460 bra 	$L__BB27_156;
	setp.eq.b32 	%p461, %r69, 0;
	@%p461 bra 	$L__BB27_157;
	clz.b32 	%r1033, %r69;
	xor.b32 	%r1034, %r1033, 31;
	sub.s32 	%r1035, 9, %r1034;
	shl.b32 	%r1036, %r67, %r1035;
	shl.b32 	%r1037, %r1034, 23;
	shl.b32 	%r1038, %r1036, 14;
	and.b32 	%r1039, %r1038, 8372224;
	add.s32 	%r1040, %r1037, %r1403;
	add.s32 	%r1041, %r1040, %r1039;
	add.s32 	%r1403, %r1041, 864026624;
	bra.uni 	$L__BB27_157;
$L__BB27_155:
	shl.b32 	%r1031, %r67, 13;
	or.b32 	%r1032, %r1403, %r1031;
	or.b32 	%r1403, %r1032, 2139095040;
	bra.uni 	$L__BB27_157;
$L__BB27_156:
	shl.b32 	%r1042, %r68, 23;
	shl.b32 	%r1043, %r69, 13;
	or.b32 	%r1044, %r1042, %r1043;
	add.s32 	%r1045, %r1044, %r1403;
	add.s32 	%r1403, %r1045, 939524096;
$L__BB27_157:
	cvta.to.local.u64 	%rd662, %rd632;
	ld.local.b32 	%r1405, [%rd662];
	@%p438 bra 	$L__BB27_180;
	cvt.f64.f32 	%rd45, %r1405;
	shr.u64 	%rd47, %rd45, 48;
	cvt.u32.u64 	%r1046, %rd47;
	and.b32 	%r70, %r1046, 32768;
	shr.u64 	%rd663, %rd45, 52;
	cvt.u32.u64 	%r1047, %rd663;
	and.b32 	%r71, %r1047, 2047;
	setp.eq.b32 	%p463, %r71, 0;
	@%p463 bra 	$L__BB27_161;
	and.b64 	%rd46, %rd45, 4503599627370495;
	setp.eq.b32 	%p462, %r1396, 12;
	selp.b32 	%r72, 11, 8, %p462;
	selp.b32 	%r74, 31744, 32640, %p462;
	setp.ne.b32 	%p464, %r71, 2047;
	@%p464 bra 	$L__BB27_162;
	setp.eq.b64 	%p465, %rd46, 0;
	add.s32 	%r1048, %r72, -2;
	mov.b32 	%r1049, 1;
	shl.b32 	%r1050, %r1049, %r1048;
	selp.b32 	%r1051, 0, %r1050, %p465;
	or.b32 	%r1052, %r1051, %r74;
	or.b32 	%r1053, %r1052, %r70;
	cvt.u16.u32 	%rs7, %r1053;
	bra.uni 	$L__BB27_172;
$L__BB27_161:
	cvt.u16.u32 	%rs7, %r70;
	bra.uni 	$L__BB27_172;
$L__BB27_162:
	selp.b32 	%r1054, -14, -126, %p462;
	add.s32 	%r75, %r71, -1023;
	or.b64 	%rd48, %rd46, 4503599627370496;
	setp.ge.s32 	%p466, %r75, %r1054;
	@%p466 bra 	$L__BB27_168;
	and.b64 	%rd49, %rd47, 32768;
	selp.b32 	%r1064, 28, -81, %p462;
	sub.s32 	%r76, %r1064, %r75;
	setp.gt.s32 	%p474, %r76, 0;
	@%p474 bra 	$L__BB27_165;
	bra.uni 	$L__BB27_164;
$L__BB27_165:
	setp.gt.u32 	%p475, %r76, 63;
	mov.b64 	%rd888, 0;
	@%p475 bra 	$L__BB27_167;
	shr.u64 	%rd677, %rd48, %r76;
	mov.b64 	%rd678, -1;
	shl.b64 	%rd679, %rd678, %r76;
	not.b64 	%rd680, %rd679;
	and.b64 	%rd681, %rd48, %rd680;
	add.s32 	%r1065, %r76, -1;
	mov.b64 	%rd682, 1;
	shl.b64 	%rd683, %rd682, %r1065;
	setp.gt.u64 	%p476, %rd681, %rd683;
	setp.eq.b64 	%p477, %rd681, %rd683;
	and.b64 	%rd684, %rd677, 1;
	setp.ne.b64 	%p478, %rd684, 0;
	and.pred 	%p479, %p477, %p478;
	or.pred 	%p480, %p476, %p479;
	selp.b64 	%rd685, 1, 0, %p480;
	add.s64 	%rd888, %rd677, %rd685;
	bra.uni 	$L__BB27_167;
$L__BB27_168:
	selp.b32 	%r73, 15, 127, %p462;
	sub.s32 	%r1055, 53, %r72;
	shr.u64 	%rd664, %rd48, %r1055;
	mov.b64 	%rd665, -1;
	shl.b64 	%rd666, %rd665, %r1055;
	not.b64 	%rd667, %rd666;
	and.b64 	%rd668, %rd45, %rd667;
	sub.s32 	%r1056, 52, %r72;
	mov.b64 	%rd669, 1;
	shl.b64 	%rd670, %rd669, %r1056;
	setp.gt.u64 	%p467, %rd668, %rd670;
	setp.eq.b64 	%p468, %rd668, %rd670;
	and.b64 	%rd671, %rd664, 1;
	setp.ne.b64 	%p469, %rd671, 0;
	and.pred 	%p470, %p468, %p469;
	or.pred 	%p471, %p467, %p470;
	selp.b64 	%rd672, 1, 0, %p471;
	add.s64 	%rd50, %rd664, %rd672;
	shl.b64 	%rd51, %rd669, %r72;
	setp.eq.b64 	%p472, %rd50, %rd51;
	add.s32 	%r1057, %r71, -1022;
	selp.b32 	%r77, %r1057, %r75, %p472;
	setp.le.s32 	%p473, %r77, %r73;
	@%p473 bra 	$L__BB27_170;
	or.b32 	%r1404, %r70, %r74;
	bra.uni 	$L__BB27_171;
$L__BB27_170:
	selp.b32 	%r1058, 1, 0, %p472;
	shr.u64 	%rd673, %rd50, %r1058;
	add.s32 	%r1059, %r77, %r73;
	add.s32 	%r1060, %r72, -1;
	shl.b32 	%r1061, %r1059, %r1060;
	shl.b64 	%rd674, %rd665, %r1060;
	not.b64 	%rd675, %rd674;
	and.b64 	%rd676, %rd673, %rd675;
	cvt.u32.u64 	%r1062, %rd676;
	or.b32 	%r1063, %r1061, %r1062;
	or.b32 	%r1404, %r1063, %r70;
$L__BB27_171:
	cvt.u16.u32 	%rs7, %r1404;
	bra.uni 	$L__BB27_172;
$L__BB27_118:
	neg.s32 	%r984, %r53;
	shl.b64 	%rd886, %rd34, %r984;
$L__BB27_121:
	or.b64 	%rd630, %rd886, %rd35;
	cvt.u16.u64 	%rs5, %rd630;
$L__BB27_126:
	setp.ne.b32 	%p434, %r1396, 13;
	cvt.u32.u16 	%r55, %rs5;
	@%p434 bra 	$L__BB27_128;
	shl.b32 	%r1440, %r55, 16;
	bra.uni 	$L__BB27_664;
$L__BB27_128:
	cvt.s32.s16 	%r985, %rs5;
	and.b32 	%r1440, %r985, -2147483648;
	bfe.u32 	%r56, %r55, 10, 5;
	setp.eq.b32 	%p435, %r56, 31;
	@%p435 bra 	$L__BB27_132;
	and.b32 	%r57, %r55, 1023;
	setp.ne.b32 	%p436, %r56, 0;
	@%p436 bra 	$L__BB27_133;
	setp.eq.b32 	%p437, %r57, 0;
	@%p437 bra 	$L__BB27_664;
	clz.b32 	%r988, %r57;
	xor.b32 	%r989, %r988, 31;
	sub.s32 	%r990, 9, %r989;
	shl.b32 	%r991, %r55, %r990;
	shl.b32 	%r992, %r989, 23;
	shl.b32 	%r993, %r991, 14;
	and.b32 	%r994, %r993, 8372224;
	add.s32 	%r995, %r992, %r1440;
	add.s32 	%r996, %r995, %r994;
	add.s32 	%r1440, %r996, 864026624;
	bra.uni 	$L__BB27_664;
$L__BB27_132:
	shl.b32 	%r986, %r55, 13;
	or.b32 	%r987, %r1440, %r986;
	or.b32 	%r1440, %r987, 2139095040;
	bra.uni 	$L__BB27_664;
$L__BB27_133:
	shl.b32 	%r997, %r56, 23;
	shl.b32 	%r998, %r57, 13;
	or.b32 	%r999, %r997, %r998;
	add.s32 	%r1000, %r999, %r1440;
	add.s32 	%r1440, %r1000, 939524096;
	bra.uni 	$L__BB27_664;
$L__BB27_164:
	neg.s32 	%r1066, %r76;
	shl.b64 	%rd888, %rd48, %r1066;
$L__BB27_167:
	or.b64 	%rd686, %rd888, %rd49;
	cvt.u16.u64 	%rs7, %rd686;
$L__BB27_172:
	setp.ne.b32 	%p481, %r1396, 13;
	cvt.u32.u16 	%r78, %rs7;
	@%p481 bra 	$L__BB27_174;
	shl.b32 	%r1405, %r78, 16;
	bra.uni 	$L__BB27_180;
$L__BB27_174:
	cvt.s32.s16 	%r1067, %rs7;
	and.b32 	%r1405, %r1067, -2147483648;
	bfe.u32 	%r79, %r78, 10, 5;
	setp.eq.b32 	%p482, %r79, 31;
	@%p482 bra 	$L__BB27_178;
	and.b32 	%r80, %r78, 1023;
	setp.ne.b32 	%p483, %r79, 0;
	@%p483 bra 	$L__BB27_179;
	setp.eq.b32 	%p484, %r80, 0;
	@%p484 bra 	$L__BB27_180;
	clz.b32 	%r1070, %r80;
	xor.b32 	%r1071, %r1070, 31;
	sub.s32 	%r1072, 9, %r1071;
	shl.b32 	%r1073, %r78, %r1072;
	shl.b32 	%r1074, %r1071, 23;
	shl.b32 	%r1075, %r1073, 14;
	and.b32 	%r1076, %r1075, 8372224;
	add.s32 	%r1077, %r1074, %r1405;
	add.s32 	%r1078, %r1077, %r1076;
	add.s32 	%r1405, %r1078, 864026624;
	bra.uni 	$L__BB27_180;
$L__BB27_178:
	shl.b32 	%r1068, %r78, 13;
	or.b32 	%r1069, %r1405, %r1068;
	or.b32 	%r1405, %r1069, 2139095040;
	bra.uni 	$L__BB27_180;
$L__BB27_179:
	shl.b32 	%r1079, %r79, 23;
	shl.b32 	%r1080, %r80, 13;
)QPTX";
        result += R"QPTX(
	or.b32 	%r1081, %r1079, %r1080;
	add.s32 	%r1082, %r1081, %r1405;
	add.s32 	%r1405, %r1082, 939524096;
$L__BB27_180:
	sub.rn.f32 	%r1440, %r1403, %r1405;
	@%p438 bra 	$L__BB27_203;
	cvt.f64.f32 	%rd52, %r1440;
	shr.u64 	%rd54, %rd52, 48;
	cvt.u32.u64 	%r1083, %rd54;
	and.b32 	%r81, %r1083, 32768;
	shr.u64 	%rd687, %rd52, 52;
	cvt.u32.u64 	%r1084, %rd687;
	and.b32 	%r82, %r1084, 2047;
	setp.eq.b32 	%p486, %r82, 0;
	@%p486 bra 	$L__BB27_184;
	and.b64 	%rd53, %rd52, 4503599627370495;
	setp.eq.b32 	%p485, %r1396, 12;
	selp.b32 	%r83, 11, 8, %p485;
	selp.b32 	%r85, 31744, 32640, %p485;
	setp.ne.b32 	%p487, %r82, 2047;
	@%p487 bra 	$L__BB27_185;
	setp.eq.b64 	%p488, %rd53, 0;
	add.s32 	%r1085, %r83, -2;
	mov.b32 	%r1086, 1;
	shl.b32 	%r1087, %r1086, %r1085;
	selp.b32 	%r1088, 0, %r1087, %p488;
	or.b32 	%r1089, %r1088, %r85;
	or.b32 	%r1090, %r1089, %r81;
	cvt.u16.u32 	%rs8, %r1090;
	bra.uni 	$L__BB27_195;
$L__BB27_184:
	cvt.u16.u32 	%rs8, %r81;
	bra.uni 	$L__BB27_195;
$L__BB27_185:
	selp.b32 	%r1091, -14, -126, %p485;
	add.s32 	%r86, %r82, -1023;
	or.b64 	%rd55, %rd53, 4503599627370496;
	setp.ge.s32 	%p489, %r86, %r1091;
	@%p489 bra 	$L__BB27_191;
	and.b64 	%rd56, %rd54, 32768;
	selp.b32 	%r1101, 28, -81, %p485;
	sub.s32 	%r87, %r1101, %r86;
	setp.gt.s32 	%p497, %r87, 0;
	@%p497 bra 	$L__BB27_188;
	bra.uni 	$L__BB27_187;
$L__BB27_188:
	setp.gt.u32 	%p498, %r87, 63;
	mov.b64 	%rd889, 0;
	@%p498 bra 	$L__BB27_190;
	shr.u64 	%rd701, %rd55, %r87;
	mov.b64 	%rd702, -1;
	shl.b64 	%rd703, %rd702, %r87;
	not.b64 	%rd704, %rd703;
	and.b64 	%rd705, %rd55, %rd704;
	add.s32 	%r1102, %r87, -1;
	mov.b64 	%rd706, 1;
	shl.b64 	%rd707, %rd706, %r1102;
	setp.gt.u64 	%p499, %rd705, %rd707;
	setp.eq.b64 	%p500, %rd705, %rd707;
	and.b64 	%rd708, %rd701, 1;
	setp.ne.b64 	%p501, %rd708, 0;
	and.pred 	%p502, %p500, %p501;
	or.pred 	%p503, %p499, %p502;
	selp.b64 	%rd709, 1, 0, %p503;
	add.s64 	%rd889, %rd701, %rd709;
	bra.uni 	$L__BB27_190;
$L__BB27_191:
	selp.b32 	%r84, 15, 127, %p485;
	sub.s32 	%r1092, 53, %r83;
	shr.u64 	%rd688, %rd55, %r1092;
	mov.b64 	%rd689, -1;
	shl.b64 	%rd690, %rd689, %r1092;
	not.b64 	%rd691, %rd690;
	and.b64 	%rd692, %rd52, %rd691;
	sub.s32 	%r1093, 52, %r83;
	mov.b64 	%rd693, 1;
	shl.b64 	%rd694, %rd693, %r1093;
	setp.gt.u64 	%p490, %rd692, %rd694;
	setp.eq.b64 	%p491, %rd692, %rd694;
	and.b64 	%rd695, %rd688, 1;
	setp.ne.b64 	%p492, %rd695, 0;
	and.pred 	%p493, %p491, %p492;
	or.pred 	%p494, %p490, %p493;
	selp.b64 	%rd696, 1, 0, %p494;
	add.s64 	%rd57, %rd688, %rd696;
	shl.b64 	%rd58, %rd693, %r83;
	setp.eq.b64 	%p495, %rd57, %rd58;
	add.s32 	%r1094, %r82, -1022;
	selp.b32 	%r88, %r1094, %r86, %p495;
	setp.le.s32 	%p496, %r88, %r84;
	@%p496 bra 	$L__BB27_193;
	or.b32 	%r1406, %r81, %r85;
	bra.uni 	$L__BB27_194;
$L__BB27_193:
	selp.b32 	%r1095, 1, 0, %p495;
	shr.u64 	%rd697, %rd57, %r1095;
	add.s32 	%r1096, %r88, %r84;
	add.s32 	%r1097, %r83, -1;
	shl.b32 	%r1098, %r1096, %r1097;
	shl.b64 	%rd698, %rd689, %r1097;
	not.b64 	%rd699, %rd698;
	and.b64 	%rd700, %rd697, %rd699;
	cvt.u32.u64 	%r1099, %rd700;
	or.b32 	%r1100, %r1098, %r1099;
	or.b32 	%r1406, %r1100, %r81;
$L__BB27_194:
	cvt.u16.u32 	%rs8, %r1406;
	bra.uni 	$L__BB27_195;
$L__BB27_187:
	neg.s32 	%r1103, %r87;
	shl.b64 	%rd889, %rd55, %r1103;
$L__BB27_190:
	or.b64 	%rd710, %rd889, %rd56;
	cvt.u16.u64 	%rs8, %rd710;
$L__BB27_195:
	setp.ne.b32 	%p504, %r1396, 13;
	cvt.u32.u16 	%r89, %rs8;
	@%p504 bra 	$L__BB27_197;
	shl.b32 	%r1440, %r89, 16;
	bra.uni 	$L__BB27_203;
$L__BB27_197:
	cvt.s32.s16 	%r1104, %rs8;
	and.b32 	%r1440, %r1104, -2147483648;
	bfe.u32 	%r90, %r89, 10, 5;
	setp.eq.b32 	%p505, %r90, 31;
	@%p505 bra 	$L__BB27_201;
	and.b32 	%r91, %r89, 1023;
	setp.ne.b32 	%p506, %r90, 0;
	@%p506 bra 	$L__BB27_202;
	setp.eq.b32 	%p507, %r91, 0;
	@%p507 bra 	$L__BB27_203;
	clz.b32 	%r1107, %r91;
	xor.b32 	%r1108, %r1107, 31;
	sub.s32 	%r1109, 9, %r1108;
	shl.b32 	%r1110, %r89, %r1109;
	shl.b32 	%r1111, %r1108, 23;
	shl.b32 	%r1112, %r1110, 14;
	and.b32 	%r1113, %r1112, 8372224;
	add.s32 	%r1114, %r1111, %r1440;
	add.s32 	%r1115, %r1114, %r1113;
	add.s32 	%r1440, %r1115, 864026624;
	bra.uni 	$L__BB27_203;
$L__BB27_201:
	shl.b32 	%r1105, %r89, 13;
	or.b32 	%r1106, %r1440, %r1105;
	or.b32 	%r1440, %r1106, 2139095040;
	bra.uni 	$L__BB27_203;
$L__BB27_202:
	shl.b32 	%r1116, %r90, 23;
	shl.b32 	%r1117, %r91, 13;
	or.b32 	%r1118, %r1116, %r1117;
	add.s32 	%r1119, %r1118, %r1440;
	add.s32 	%r1440, %r1119, 939524096;
$L__BB27_203:
	cvta.to.local.u64 	%rd711, %rd634;
	ld.local.b32 	%r1408, [%rd711];
	@%p438 bra 	$L__BB27_226;
	cvt.f64.f32 	%rd59, %r1408;
	shr.u64 	%rd61, %rd59, 48;
	cvt.u32.u64 	%r1120, %rd61;
	and.b32 	%r92, %r1120, 32768;
	shr.u64 	%rd712, %rd59, 52;
	cvt.u32.u64 	%r1121, %rd712;
	and.b32 	%r93, %r1121, 2047;
	setp.eq.b32 	%p509, %r93, 0;
	@%p509 bra 	$L__BB27_207;
	and.b64 	%rd60, %rd59, 4503599627370495;
	setp.eq.b32 	%p508, %r1396, 12;
	selp.b32 	%r94, 11, 8, %p508;
	selp.b32 	%r96, 31744, 32640, %p508;
	setp.ne.b32 	%p510, %r93, 2047;
	@%p510 bra 	$L__BB27_208;
	setp.eq.b64 	%p511, %rd60, 0;
	add.s32 	%r1122, %r94, -2;
	mov.b32 	%r1123, 1;
	shl.b32 	%r1124, %r1123, %r1122;
	selp.b32 	%r1125, 0, %r1124, %p511;
	or.b32 	%r1126, %r1125, %r96;
	or.b32 	%r1127, %r1126, %r92;
	cvt.u16.u32 	%rs9, %r1127;
	bra.uni 	$L__BB27_218;
$L__BB27_207:
	cvt.u16.u32 	%rs9, %r92;
	bra.uni 	$L__BB27_218;
$L__BB27_208:
	selp.b32 	%r1128, -14, -126, %p508;
	add.s32 	%r97, %r93, -1023;
	or.b64 	%rd62, %rd60, 4503599627370496;
	setp.ge.s32 	%p512, %r97, %r1128;
	@%p512 bra 	$L__BB27_214;
	and.b64 	%rd63, %rd61, 32768;
	selp.b32 	%r1138, 28, -81, %p508;
	sub.s32 	%r98, %r1138, %r97;
	setp.gt.s32 	%p520, %r98, 0;
	@%p520 bra 	$L__BB27_211;
	bra.uni 	$L__BB27_210;
$L__BB27_211:
	setp.gt.u32 	%p521, %r98, 63;
	mov.b64 	%rd890, 0;
	@%p521 bra 	$L__BB27_213;
	shr.u64 	%rd726, %rd62, %r98;
	mov.b64 	%rd727, -1;
	shl.b64 	%rd728, %rd727, %r98;
	not.b64 	%rd729, %rd728;
	and.b64 	%rd730, %rd62, %rd729;
	add.s32 	%r1139, %r98, -1;
	mov.b64 	%rd731, 1;
	shl.b64 	%rd732, %rd731, %r1139;
	setp.gt.u64 	%p522, %rd730, %rd732;
	setp.eq.b64 	%p523, %rd730, %rd732;
	and.b64 	%rd733, %rd726, 1;
	setp.ne.b64 	%p524, %rd733, 0;
	and.pred 	%p525, %p523, %p524;
	or.pred 	%p526, %p522, %p525;
	selp.b64 	%rd734, 1, 0, %p526;
	add.s64 	%rd890, %rd726, %rd734;
	bra.uni 	$L__BB27_213;
$L__BB27_214:
	selp.b32 	%r95, 15, 127, %p508;
	sub.s32 	%r1129, 53, %r94;
	shr.u64 	%rd713, %rd62, %r1129;
	mov.b64 	%rd714, -1;
	shl.b64 	%rd715, %rd714, %r1129;
	not.b64 	%rd716, %rd715;
	and.b64 	%rd717, %rd59, %rd716;
	sub.s32 	%r1130, 52, %r94;
	mov.b64 	%rd718, 1;
	shl.b64 	%rd719, %rd718, %r1130;
	setp.gt.u64 	%p513, %rd717, %rd719;
	setp.eq.b64 	%p514, %rd717, %rd719;
	and.b64 	%rd720, %rd713, 1;
	setp.ne.b64 	%p515, %rd720, 0;
	and.pred 	%p516, %p514, %p515;
	or.pred 	%p517, %p513, %p516;
	selp.b64 	%rd721, 1, 0, %p517;
	add.s64 	%rd64, %rd713, %rd721;
	shl.b64 	%rd65, %rd718, %r94;
	setp.eq.b64 	%p518, %rd64, %rd65;
	add.s32 	%r1131, %r93, -1022;
	selp.b32 	%r99, %r1131, %r97, %p518;
	setp.le.s32 	%p519, %r99, %r95;
	@%p519 bra 	$L__BB27_216;
	or.b32 	%r1407, %r92, %r96;
	bra.uni 	$L__BB27_217;
$L__BB27_216:
	selp.b32 	%r1132, 1, 0, %p518;
	shr.u64 	%rd722, %rd64, %r1132;
	add.s32 	%r1133, %r99, %r95;
	add.s32 	%r1134, %r94, -1;
	shl.b32 	%r1135, %r1133, %r1134;
	shl.b64 	%rd723, %rd714, %r1134;
	not.b64 	%rd724, %rd723;
	and.b64 	%rd725, %rd722, %rd724;
	cvt.u32.u64 	%r1136, %rd725;
	or.b32 	%r1137, %r1135, %r1136;
	or.b32 	%r1407, %r1137, %r92;
$L__BB27_217:
	cvt.u16.u32 	%rs9, %r1407;
	bra.uni 	$L__BB27_218;
$L__BB27_210:
	neg.s32 	%r1140, %r98;
	shl.b64 	%rd890, %rd62, %r1140;
$L__BB27_213:
	or.b64 	%rd735, %rd890, %rd63;
	cvt.u16.u64 	%rs9, %rd735;
$L__BB27_218:
	setp.ne.b32 	%p527, %r1396, 13;
	cvt.u32.u16 	%r100, %rs9;
	@%p527 bra 	$L__BB27_220;
	shl.b32 	%r1408, %r100, 16;
	bra.uni 	$L__BB27_226;
$L__BB27_220:
	cvt.s32.s16 	%r1141, %rs9;
	and.b32 	%r1408, %r1141, -2147483648;
	bfe.u32 	%r101, %r100, 10, 5;
	setp.eq.b32 	%p528, %r101, 31;
	@%p528 bra 	$L__BB27_224;
	and.b32 	%r102, %r100, 1023;
	setp.ne.b32 	%p529, %r101, 0;
	@%p529 bra 	$L__BB27_225;
	setp.eq.b32 	%p530, %r102, 0;
	@%p530 bra 	$L__BB27_226;
	clz.b32 	%r1144, %r102;
	xor.b32 	%r1145, %r1144, 31;
	sub.s32 	%r1146, 9, %r1145;
	shl.b32 	%r1147, %r100, %r1146;
	shl.b32 	%r1148, %r1145, 23;
	shl.b32 	%r1149, %r1147, 14;
	and.b32 	%r1150, %r1149, 8372224;
	add.s32 	%r1151, %r1148, %r1408;
	add.s32 	%r1152, %r1151, %r1150;
	add.s32 	%r1408, %r1152, 864026624;
	bra.uni 	$L__BB27_226;
$L__BB27_224:
	shl.b32 	%r1142, %r100, 13;
	or.b32 	%r1143, %r1408, %r1142;
	or.b32 	%r1408, %r1143, 2139095040;
	bra.uni 	$L__BB27_226;
$L__BB27_225:
	shl.b32 	%r1153, %r101, 23;
	shl.b32 	%r1154, %r102, 13;
	or.b32 	%r1155, %r1153, %r1154;
	add.s32 	%r1156, %r1155, %r1408;
	add.s32 	%r1408, %r1156, 939524096;
$L__BB27_226:
	cvta.to.local.u64 	%rd736, %rd636;
	ld.local.b32 	%r1410, [%rd736];
	@%p438 bra 	$L__BB27_249;
	cvt.f64.f32 	%rd66, %r1410;
	shr.u64 	%rd68, %rd66, 48;
	cvt.u32.u64 	%r1157, %rd68;
	and.b32 	%r103, %r1157, 32768;
	shr.u64 	%rd737, %rd66, 52;
	cvt.u32.u64 	%r1158, %rd737;
	and.b32 	%r104, %r1158, 2047;
	setp.eq.b32 	%p532, %r104, 0;
	@%p532 bra 	$L__BB27_230;
	and.b64 	%rd67, %rd66, 4503599627370495;
	setp.eq.b32 	%p531, %r1396, 12;
	selp.b32 	%r105, 11, 8, %p531;
	selp.b32 	%r107, 31744, 32640, %p531;
	setp.ne.b32 	%p533, %r104, 2047;
	@%p533 bra 	$L__BB27_231;
	setp.eq.b64 	%p534, %rd67, 0;
	add.s32 	%r1159, %r105, -2;
	mov.b32 	%r1160, 1;
	shl.b32 	%r1161, %r1160, %r1159;
	selp.b32 	%r1162, 0, %r1161, %p534;
	or.b32 	%r1163, %r1162, %r107;
	or.b32 	%r1164, %r1163, %r103;
	cvt.u16.u32 	%rs10, %r1164;
	bra.uni 	$L__BB27_241;
$L__BB27_230:
	cvt.u16.u32 	%rs10, %r103;
	bra.uni 	$L__BB27_241;
$L__BB27_231:
	selp.b32 	%r1165, -14, -126, %p531;
	add.s32 	%r108, %r104, -1023;
	or.b64 	%rd69, %rd67, 4503599627370496;
	setp.ge.s32 	%p535, %r108, %r1165;
	@%p535 bra 	$L__BB27_237;
	and.b64 	%rd70, %rd68, 32768;
	selp.b32 	%r1175, 28, -81, %p531;
	sub.s32 	%r109, %r1175, %r108;
	setp.gt.s32 	%p543, %r109, 0;
	@%p543 bra 	$L__BB27_234;
	bra.uni 	$L__BB27_233;
$L__BB27_234:
	setp.gt.u32 	%p544, %r109, 63;
	mov.b64 	%rd891, 0;
	@%p544 bra 	$L__BB27_236;
	shr.u64 	%rd751, %rd69, %r109;
	mov.b64 	%rd752, -1;
	shl.b64 	%rd753, %rd752, %r109;
	not.b64 	%rd754, %rd753;
	and.b64 	%rd755, %rd69, %rd754;
	add.s32 	%r1176, %r109, -1;
	mov.b64 	%rd756, 1;
	shl.b64 	%rd757, %rd756, %r1176;
	setp.gt.u64 	%p545, %rd755, %rd757;
	setp.eq.b64 	%p546, %rd755, %rd757;
	and.b64 	%rd758, %rd751, 1;
	setp.ne.b64 	%p547, %rd758, 0;
	and.pred 	%p548, %p546, %p547;
	or.pred 	%p549, %p545, %p548;
	selp.b64 	%rd759, 1, 0, %p549;
	add.s64 	%rd891, %rd751, %rd759;
	bra.uni 	$L__BB27_236;
$L__BB27_237:
	selp.b32 	%r106, 15, 127, %p531;
	sub.s32 	%r1166, 53, %r105;
	shr.u64 	%rd738, %rd69, %r1166;
	mov.b64 	%rd739, -1;
	shl.b64 	%rd740, %rd739, %r1166;
	not.b64 	%rd741, %rd740;
	and.b64 	%rd742, %rd66, %rd741;
	sub.s32 	%r1167, 52, %r105;
	mov.b64 	%rd743, 1;
	shl.b64 	%rd744, %rd743, %r1167;
	setp.gt.u64 	%p536, %rd742, %rd744;
	setp.eq.b64 	%p537, %rd742, %rd744;
	and.b64 	%rd745, %rd738, 1;
	setp.ne.b64 	%p538, %rd745, 0;
	and.pred 	%p539, %p537, %p538;
	or.pred 	%p540, %p536, %p539;
	selp.b64 	%rd746, 1, 0, %p540;
	add.s64 	%rd71, %rd738, %rd746;
	shl.b64 	%rd72, %rd743, %r105;
	setp.eq.b64 	%p541, %rd71, %rd72;
	add.s32 	%r1168, %r104, -1022;
	selp.b32 	%r110, %r1168, %r108, %p541;
	setp.le.s32 	%p542, %r110, %r106;
	@%p542 bra 	$L__BB27_239;
	or.b32 	%r1409, %r103, %r107;
	bra.uni 	$L__BB27_240;
$L__BB27_239:
	selp.b32 	%r1169, 1, 0, %p541;
	shr.u64 	%rd747, %rd71, %r1169;
	add.s32 	%r1170, %r110, %r106;
	add.s32 	%r1171, %r105, -1;
	shl.b32 	%r1172, %r1170, %r1171;
	shl.b64 	%rd748, %rd739, %r1171;
	not.b64 	%rd749, %rd748;
	and.b64 	%rd750, %rd747, %rd749;
	cvt.u32.u64 	%r1173, %rd750;
	or.b32 	%r1174, %r1172, %r1173;
	or.b32 	%r1409, %r1174, %r103;
$L__BB27_240:
	cvt.u16.u32 	%rs10, %r1409;
	bra.uni 	$L__BB27_241;
$L__BB27_233:
	neg.s32 	%r1177, %r109;
	shl.b64 	%rd891, %rd69, %r1177;
$L__BB27_236:
	or.b64 	%rd760, %rd891, %rd70;
	cvt.u16.u64 	%rs10, %rd760;
$L__BB27_241:
	setp.ne.b32 	%p550, %r1396, 13;
	cvt.u32.u16 	%r111, %rs10;
	@%p550 bra 	$L__BB27_243;
	shl.b32 	%r1410, %r111, 16;
	bra.uni 	$L__BB27_249;
$L__BB27_243:
	cvt.s32.s16 	%r1178, %rs10;
	and.b32 	%r1410, %r1178, -2147483648;
	bfe.u32 	%r112, %r111, 10, 5;
	setp.eq.b32 	%p551, %r112, 31;
	@%p551 bra 	$L__BB27_247;
	and.b32 	%r113, %r111, 1023;
	setp.ne.b32 	%p552, %r112, 0;
	@%p552 bra 	$L__BB27_248;
	setp.eq.b32 	%p553, %r113, 0;
	@%p553 bra 	$L__BB27_249;
	clz.b32 	%r1181, %r113;
	xor.b32 	%r1182, %r1181, 31;
	sub.s32 	%r1183, 9, %r1182;
	shl.b32 	%r1184, %r111, %r1183;
	shl.b32 	%r1185, %r1182, 23;
	shl.b32 	%r1186, %r1184, 14;
	and.b32 	%r1187, %r1186, 8372224;
	add.s32 	%r1188, %r1185, %r1410;
	add.s32 	%r1189, %r1188, %r1187;
	add.s32 	%r1410, %r1189, 864026624;
	bra.uni 	$L__BB27_249;
$L__BB27_247:
	shl.b32 	%r1179, %r111, 13;
	or.b32 	%r1180, %r1410, %r1179;
	or.b32 	%r1410, %r1180, 2139095040;
	bra.uni 	$L__BB27_249;
$L__BB27_248:
	shl.b32 	%r1190, %r112, 23;
	shl.b32 	%r1191, %r113, 13;
	or.b32 	%r1192, %r1190, %r1191;
	add.s32 	%r1193, %r1192, %r1410;
	add.s32 	%r1410, %r1193, 939524096;
$L__BB27_249:
	add.rn.f32 	%r1439, %r1408, %r1410;
	@%p438 bra 	$L__BB27_664;
	cvt.f64.f32 	%rd73, %r1439;
	shr.u64 	%rd75, %rd73, 48;
	cvt.u32.u64 	%r1194, %rd75;
	and.b32 	%r114, %r1194, 32768;
	shr.u64 	%rd761, %rd73, 52;
	cvt.u32.u64 	%r1195, %rd761;
	and.b32 	%r115, %r1195, 2047;
	setp.eq.b32 	%p555, %r115, 0;
	@%p555 bra 	$L__BB27_253;
	and.b64 	%rd74, %rd73, 4503599627370495;
	setp.eq.b32 	%p554, %r1396, 12;
	selp.b32 	%r116, 11, 8, %p554;
	selp.b32 	%r118, 31744, 32640, %p554;
	setp.ne.b32 	%p556, %r115, 2047;
	@%p556 bra 	$L__BB27_254;
	setp.eq.b64 	%p557, %rd74, 0;
	add.s32 	%r1196, %r116, -2;
	mov.b32 	%r1197, 1;
	shl.b32 	%r1198, %r1197, %r1196;
	selp.b32 	%r1199, 0, %r1198, %p557;
	or.b32 	%r1200, %r1199, %r118;
	or.b32 	%r1201, %r1200, %r114;
	cvt.u16.u32 	%rs11, %r1201;
	bra.uni 	$L__BB27_264;
$L__BB27_253:
	cvt.u16.u32 	%rs11, %r114;
	bra.uni 	$L__BB27_264;
$L__BB27_254:
	selp.b32 	%r1202, -14, -126, %p554;
	add.s32 	%r119, %r115, -1023;
	or.b64 	%rd76, %rd74, 4503599627370496;
	setp.ge.s32 	%p558, %r119, %r1202;
	@%p558 bra 	$L__BB27_260;
	and.b64 	%rd77, %rd75, 32768;
	selp.b32 	%r1212, 28, -81, %p554;
	sub.s32 	%r120, %r1212, %r119;
	setp.gt.s32 	%p566, %r120, 0;
	@%p566 bra 	$L__BB27_257;
	bra.uni 	$L__BB27_256;
$L__BB27_257:
	setp.gt.u32 	%p567, %r120, 63;
	mov.b64 	%rd892, 0;
	@%p567 bra 	$L__BB27_259;
	shr.u64 	%rd775, %rd76, %r120;
	mov.b64 	%rd776, -1;
	shl.b64 	%rd777, %rd776, %r120;
	not.b64 	%rd778, %rd777;
	and.b64 	%rd779, %rd76, %rd778;
	add.s32 	%r1213, %r120, -1;
	mov.b64 	%rd780, 1;
	shl.b64 	%rd781, %rd780, %r1213;
	setp.gt.u64 	%p568, %rd779, %rd781;
	setp.eq.b64 	%p569, %rd779, %rd781;
	and.b64 	%rd782, %rd775, 1;
	setp.ne.b64 	%p570, %rd782, 0;
	and.pred 	%p571, %p569, %p570;
	or.pred 	%p572, %p568, %p571;
	selp.b64 	%rd783, 1, 0, %p572;
	add.s64 	%rd892, %rd775, %rd783;
	bra.uni 	$L__BB27_259;
$L__BB27_260:
	selp.b32 	%r117, 15, 127, %p554;
	sub.s32 	%r1203, 53, %r116;
	shr.u64 	%rd762, %rd76, %r1203;
	mov.b64 	%rd763, -1;
	shl.b64 	%rd764, %rd763, %r1203;
	not.b64 	%rd765, %rd764;
	and.b64 	%rd766, %rd73, %rd765;
	sub.s32 	%r1204, 52, %r116;
	mov.b64 	%rd767, 1;
	shl.b64 	%rd768, %rd767, %r1204;
	setp.gt.u64 	%p559, %rd766, %rd768;
	setp.eq.b64 	%p560, %rd766, %rd768;
	and.b64 	%rd769, %rd762, 1;
	setp.ne.b64 	%p561, %rd769, 0;
	and.pred 	%p562, %p560, %p561;
	or.pred 	%p563, %p559, %p562;
	selp.b64 	%rd770, 1, 0, %p563;
	add.s64 	%rd78, %rd762, %rd770;
	shl.b64 	%rd79, %rd767, %r116;
	setp.eq.b64 	%p564, %rd78, %rd79;
	add.s32 	%r1205, %r115, -1022;
	selp.b32 	%r121, %r1205, %r119, %p564;
	setp.le.s32 	%p565, %r121, %r117;
	@%p565 bra 	$L__BB27_262;
	or.b32 	%r1411, %r114, %r118;
	bra.uni 	$L__BB27_263;
$L__BB27_262:
	selp.b32 	%r1206, 1, 0, %p564;
	shr.u64 	%rd771, %rd78, %r1206;
	add.s32 	%r1207, %r121, %r117;
	add.s32 	%r1208, %r116, -1;
	shl.b32 	%r1209, %r1207, %r1208;
	shl.b64 	%rd772, %rd763, %r1208;
	not.b64 	%rd773, %rd772;
	and.b64 	%rd774, %rd771, %rd773;
	cvt.u32.u64 	%r1210, %rd774;
	or.b32 	%r1211, %r1209, %r1210;
	or.b32 	%r1411, %r1211, %r114;
$L__BB27_263:
	cvt.u16.u32 	%rs11, %r1411;
	bra.uni 	$L__BB27_264;
$L__BB27_256:
	neg.s32 	%r1214, %r120;
	shl.b64 	%rd892, %rd76, %r1214;
$L__BB27_259:
	or.b64 	%rd784, %rd892, %rd77;
	cvt.u16.u64 	%rs11, %rd784;
$L__BB27_264:
	setp.ne.b32 	%p573, %r1396, 13;
	cvt.u32.u16 	%r122, %rs11;
	@%p573 bra 	$L__BB27_266;
	shl.b32 	%r1439, %r122, 16;
	bra.uni 	$L__BB27_664;
$L__BB27_266:
	cvt.s32.s16 	%r1215, %rs11;
	and.b32 	%r1439, %r1215, -2147483648;
	bfe.u32 	%r123, %r122, 10, 5;
	setp.eq.b32 	%p574, %r123, 31;
	@%p574 bra 	$L__BB27_270;
	and.b32 	%r124, %r122, 1023;
	setp.ne.b32 	%p575, %r123, 0;
	@%p575 bra 	$L__BB27_271;
	setp.eq.b32 	%p576, %r124, 0;
	@%p576 bra 	$L__BB27_664;
	clz.b32 	%r1218, %r124;
	xor.b32 	%r1219, %r1218, 31;
	sub.s32 	%r1220, 9, %r1219;
	shl.b32 	%r1221, %r122, %r1220;
	shl.b32 	%r1222, %r1219, 23;
	shl.b32 	%r1223, %r1221, 14;
	and.b32 	%r1224, %r1223, 8372224;
	add.s32 	%r1225, %r1222, %r1439;
	add.s32 	%r1226, %r1225, %r1224;
	add.s32 	%r1439, %r1226, 864026624;
	bra.uni 	$L__BB27_664;
$L__BB27_270:
	shl.b32 	%r1216, %r122, 13;
	or.b32 	%r1217, %r1439, %r1216;
	or.b32 	%r1439, %r1217, 2139095040;
	bra.uni 	$L__BB27_664;
$L__BB27_271:
	shl.b32 	%r1227, %r123, 23;
	shl.b32 	%r1228, %r124, 13;
	or.b32 	%r1229, %r1227, %r1228;
	add.s32 	%r1230, %r1229, %r1439;
	add.s32 	%r1439, %r1230, 939524096;
	bra.uni 	$L__BB27_664;
$L__BB27_467:
	selp.b32 	%r633, 1, 0, %p209;
	shr.u64 	%rd401, %rd141, %r633;
	add.s32 	%r634, %r224, %r220;
	add.s32 	%r635, %r219, -1;
	shl.b32 	%r636, %r634, %r635;
	shl.b64 	%rd402, %rd393, %r635;
	not.b64 	%rd403, %rd402;
	and.b64 	%rd404, %rd401, %rd403;
	cvt.u32.u64 	%r637, %rd404;
	or.b32 	%r638, %r636, %r637;
	or.b32 	%r1427, %r638, %r217;
$L__BB27_468:
	cvt.u16.u32 	%rs20, %r1427;
	bra.uni 	$L__BB27_469;
$L__BB27_305:
	selp.b32 	%r374, 1, 0, %p48;
	shr.u64 	%rd233, %rd92, %r374;
	add.s32 	%r375, %r145, %r141;
	add.s32 	%r376, %r140, -1;
	shl.b32 	%r377, %r375, %r376;
	shl.b64 	%rd234, %rd225, %r376;
	not.b64 	%rd235, %rd234;
	and.b64 	%rd236, %rd233, %rd235;
	cvt.u32.u64 	%r378, %rd236;
	or.b32 	%r379, %r377, %r378;
	or.b32 	%r1413, %r379, %r138;
$L__BB27_306:
	cvt.u16.u32 	%rs13, %r1413;
	bra.uni 	$L__BB27_307;
$L__BB27_461:
	neg.s32 	%r641, %r223;
	shl.b64 	%rd901, %rd139, %r641;
$L__BB27_464:
	or.b64 	%rd414, %rd901, %rd140;
	cvt.u16.u64 	%rs20, %rd414;
$L__BB27_469:
	setp.ne.b32 	%p218, %r1396, 13;
	cvt.u32.u16 	%r225, %rs20;
	@%p218 bra 	$L__BB27_471;
	shl.b32 	%r1414, %r225, 16;
	bra.uni 	$L__BB27_477;
$L__BB27_471:
	cvt.s32.s16 	%r642, %rs20;
	and.b32 	%r1414, %r642, -2147483648;
	bfe.u32 	%r226, %r225, 10, 5;
	setp.eq.b32 	%p219, %r226, 31;
	@%p219 bra 	$L__BB27_475;
	and.b32 	%r227, %r225, 1023;
	setp.ne.b32 	%p220, %r226, 0;
	@%p220 bra 	$L__BB27_476;
	setp.eq.b32 	%p221, %r227, 0;
	@%p221 bra 	$L__BB27_477;
	clz.b32 	%r645, %r227;
	xor.b32 	%r646, %r645, 31;
	sub.s32 	%r647, 9, %r646;
	shl.b32 	%r648, %r225, %r647;
	shl.b32 	%r649, %r646, 23;
	shl.b32 	%r650, %r648, 14;
	and.b32 	%r651, %r650, 8372224;
	add.s32 	%r652, %r649, %r1414;
	add.s32 	%r653, %r652, %r651;
	add.s32 	%r1414, %r653, 864026624;
	bra.uni 	$L__BB27_477;
$L__BB27_475:
	shl.b32 	%r643, %r225, 13;
	or.b32 	%r644, %r1414, %r643;
	or.b32 	%r1414, %r644, 2139095040;
	bra.uni 	$L__BB27_477;
$L__BB27_476:
	shl.b32 	%r654, %r226, 23;
	shl.b32 	%r655, %r227, 13;
	or.b32 	%r656, %r654, %r655;
	add.s32 	%r657, %r656, %r1414;
	add.s32 	%r1414, %r657, 939524096;
$L__BB27_477:
	mul.rn.f32 	%r1429, %r136, %r1414;
	@%p677 bra 	$L__BB27_500;
	cvt.f64.f32 	%rd143, %r1429;
	shr.u64 	%rd145, %rd143, 48;
	cvt.u32.u64 	%r658, %rd145;
	and.b32 	%r228, %r658, 32768;
	shr.u64 	%rd415, %rd143, 52;
	cvt.u32.u64 	%r659, %rd415;
	and.b32 	%r229, %r659, 2047;
	setp.eq.b32 	%p223, %r229, 0;
	@%p223 bra 	$L__BB27_481;
	and.b64 	%rd144, %rd143, 4503599627370495;
	setp.eq.b32 	%p222, %r1396, 12;
	selp.b32 	%r230, 11, 8, %p222;
	selp.b32 	%r232, 31744, 32640, %p222;
	setp.ne.b32 	%p224, %r229, 2047;
	@%p224 bra 	$L__BB27_482;
	setp.eq.b64 	%p225, %rd144, 0;
	add.s32 	%r660, %r230, -2;
	mov.b32 	%r661, 1;
	shl.b32 	%r662, %r661, %r660;
	selp.b32 	%r663, 0, %r662, %p225;
	or.b32 	%r664, %r663, %r232;
	or.b32 	%r665, %r664, %r228;
	cvt.u16.u32 	%rs21, %r665;
	bra.uni 	$L__BB27_492;
$L__BB27_481:
	cvt.u16.u32 	%rs21, %r228;
	bra.uni 	$L__BB27_492;
$L__BB27_482:
	selp.b32 	%r666, -14, -126, %p222;
	add.s32 	%r233, %r229, -1023;
	or.b64 	%rd146, %rd144, 4503599627370496;
	setp.ge.s32 	%p226, %r233, %r666;
	@%p226 bra 	$L__BB27_488;
	and.b64 	%rd147, %rd145, 32768;
	selp.b32 	%r676, 28, -81, %p222;
	sub.s32 	%r234, %r676, %r233;
	setp.gt.s32 	%p234, %r234, 0;
	@%p234 bra 	$L__BB27_485;
	bra.uni 	$L__BB27_484;
$L__BB27_485:
	setp.gt.u32 	%p235, %r234, 63;
	mov.b64 	%rd902, 0;
	@%p235 bra 	$L__BB27_487;
	shr.u64 	%rd429, %rd146, %r234;
	mov.b64 	%rd430, -1;
	shl.b64 	%rd431, %rd430, %r234;
	not.b64 	%rd432, %rd431;
	and.b64 	%rd433, %rd146, %rd432;
	add.s32 	%r677, %r234, -1;
	mov.b64 	%rd434, 1;
	shl.b64 	%rd435, %rd434, %r677;
	setp.gt.u64 	%p236, %rd433, %rd435;
	setp.eq.b64 	%p237, %rd433, %rd435;
	and.b64 	%rd436, %rd429, 1;
	setp.ne.b64 	%p238, %rd436, 0;
	and.pred 	%p239, %p237, %p238;
	or.pred 	%p240, %p236, %p239;
	selp.b64 	%rd437, 1, 0, %p240;
	add.s64 	%rd902, %rd429, %rd437;
	bra.uni 	$L__BB27_487;
$L__BB27_488:
	selp.b32 	%r231, 15, 127, %p222;
	sub.s32 	%r667, 53, %r230;
	shr.u64 	%rd416, %rd146, %r667;
	mov.b64 	%rd417, -1;
	shl.b64 	%rd418, %rd417, %r667;
	not.b64 	%rd419, %rd418;
	and.b64 	%rd420, %rd143, %rd419;
	sub.s32 	%r668, 52, %r230;
	mov.b64 	%rd421, 1;
	shl.b64 	%rd422, %rd421, %r668;
	setp.gt.u64 	%p227, %rd420, %rd422;
	setp.eq.b64 	%p228, %rd420, %rd422;
	and.b64 	%rd423, %rd416, 1;
	setp.ne.b64 	%p229, %rd423, 0;
	and.pred 	%p230, %p228, %p229;
	or.pred 	%p231, %p227, %p230;
	selp.b64 	%rd424, 1, 0, %p231;
	add.s64 	%rd148, %rd416, %rd424;
	shl.b64 	%rd149, %rd421, %r230;
	setp.eq.b64 	%p232, %rd148, %rd149;
	add.s32 	%r669, %r229, -1022;
	selp.b32 	%r235, %r669, %r233, %p232;
	setp.le.s32 	%p233, %r235, %r231;
	@%p233 bra 	$L__BB27_490;
	or.b32 	%r1428, %r228, %r232;
	bra.uni 	$L__BB27_491;
$L__BB27_490:
	selp.b32 	%r670, 1, 0, %p232;
	shr.u64 	%rd425, %rd148, %r670;
	add.s32 	%r671, %r235, %r231;
	add.s32 	%r672, %r230, -1;
	shl.b32 	%r673, %r671, %r672;
	shl.b64 	%rd426, %rd417, %r672;
	not.b64 	%rd427, %rd426;
	and.b64 	%rd428, %rd425, %rd427;
	cvt.u32.u64 	%r674, %rd428;
	or.b32 	%r675, %r673, %r674;
	or.b32 	%r1428, %r675, %r228;
$L__BB27_491:
	cvt.u16.u32 	%rs21, %r1428;
	bra.uni 	$L__BB27_492;
$L__BB27_299:
	neg.s32 	%r382, %r144;
	shl.b64 	%rd894, %rd90, %r382;
$L__BB27_302:
	or.b64 	%rd246, %rd894, %rd91;
	cvt.u16.u64 	%rs13, %rd246;
$L__BB27_307:
	setp.ne.b32 	%p57, %r1396, 13;
	cvt.u32.u16 	%r146, %rs13;
	@%p57 bra 	$L__BB27_309;
	shl.b32 	%r1414, %r146, 16;
	bra.uni 	$L__BB27_315;
$L__BB27_309:
	cvt.s32.s16 	%r383, %rs13;
	and.b32 	%r1414, %r383, -2147483648;
	bfe.u32 	%r147, %r146, 10, 5;
	setp.eq.b32 	%p58, %r147, 31;
	@%p58 bra 	$L__BB27_313;
	and.b32 	%r148, %r146, 1023;
	setp.ne.b32 	%p59, %r147, 0;
	@%p59 bra 	$L__BB27_314;
	setp.eq.b32 	%p60, %r148, 0;
	@%p60 bra 	$L__BB27_315;
	clz.b32 	%r386, %r148;
	xor.b32 	%r387, %r386, 31;
	sub.s32 	%r388, 9, %r387;
	shl.b32 	%r389, %r146, %r388;
	shl.b32 	%r390, %r387, 23;
	shl.b32 	%r391, %r389, 14;
	and.b32 	%r392, %r391, 8372224;
	add.s32 	%r393, %r390, %r1414;
	add.s32 	%r394, %r393, %r392;
	add.s32 	%r1414, %r394, 864026624;
	bra.uni 	$L__BB27_315;
$L__BB27_313:
	shl.b32 	%r384, %r146, 13;
	or.b32 	%r385, %r1414, %r384;
	or.b32 	%r1414, %r385, 2139095040;
	bra.uni 	$L__BB27_315;
$L__BB27_314:
	shl.b32 	%r395, %r147, 23;
	shl.b32 	%r396, %r148, 13;
	or.b32 	%r397, %r395, %r396;
	add.s32 	%r398, %r397, %r1414;
	add.s32 	%r1414, %r398, 939524096;
$L__BB27_315:
	mul.rn.f32 	%r1416, %r137, %r1414;
	@%p677 bra 	$L__BB27_338;
	cvt.f64.f32 	%rd94, %r1416;
	shr.u64 	%rd96, %rd94, 48;
	cvt.u32.u64 	%r399, %rd96;
	and.b32 	%r149, %r399, 32768;
	shr.u64 	%rd247, %rd94, 52;
	cvt.u32.u64 	%r400, %rd247;
	and.b32 	%r150, %r400, 2047;
	setp.eq.b32 	%p62, %r150, 0;
	@%p62 bra 	$L__BB27_319;
	and.b64 	%rd95, %rd94, 4503599627370495;
	setp.eq.b32 	%p61, %r1396, 12;
	selp.b32 	%r151, 11, 8, %p61;
	selp.b32 	%r153, 31744, 32640, %p61;
	setp.ne.b32 	%p63, %r150, 2047;
	@%p63 bra 	$L__BB27_320;
	setp.eq.b64 	%p64, %rd95, 0;
	add.s32 	%r401, %r151, -2;
	mov.b32 	%r402, 1;
	shl.b32 	%r403, %r402, %r401;
	selp.b32 	%r404, 0, %r403, %p64;
	or.b32 	%r405, %r404, %r153;
	or.b32 	%r406, %r405, %r149;
	cvt.u16.u32 	%rs14, %r406;
	bra.uni 	$L__BB27_330;
$L__BB27_319:
	cvt.u16.u32 	%rs14, %r149;
	bra.uni 	$L__BB27_330;
$L__BB27_320:
	selp.b32 	%r407, -14, -126, %p61;
	add.s32 	%r154, %r150, -1023;
	or.b64 	%rd97, %rd95, 4503599627370496;
	setp.ge.s32 	%p65, %r154, %r407;
	@%p65 bra 	$L__BB27_326;
	and.b64 	%rd98, %rd96, 32768;
	selp.b32 	%r417, 28, -81, %p61;
	sub.s32 	%r155, %r417, %r154;
	setp.gt.s32 	%p73, %r155, 0;
	@%p73 bra 	$L__BB27_323;
	bra.uni 	$L__BB27_322;
$L__BB27_323:
	setp.gt.u32 	%p74, %r155, 63;
	mov.b64 	%rd895, 0;
	@%p74 bra 	$L__BB27_325;
	shr.u64 	%rd261, %rd97, %r155;
	mov.b64 	%rd262, -1;
	shl.b64 	%rd263, %rd262, %r155;
	not.b64 	%rd264, %rd263;
	and.b64 	%rd265, %rd97, %rd264;
	add.s32 	%r418, %r155, -1;
	mov.b64 	%rd266, 1;
	shl.b64 	%rd267, %rd266, %r418;
	setp.gt.u64 	%p75, %rd265, %rd267;
	setp.eq.b64 	%p76, %rd265, %rd267;
	and.b64 	%rd268, %rd261, 1;
	setp.ne.b64 	%p77, %rd268, 0;
	and.pred 	%p78, %p76, %p77;
	or.pred 	%p79, %p75, %p78;
	selp.b64 	%rd269, 1, 0, %p79;
	add.s64 	%rd895, %rd261, %rd269;
	bra.uni 	$L__BB27_325;
$L__BB27_326:
	selp.b32 	%r152, 15, 127, %p61;
	sub.s32 	%r408, 53, %r151;
	shr.u64 	%rd248, %rd97, %r408;
	mov.b64 	%rd249, -1;
	shl.b64 	%rd250, %rd249, %r408;
	not.b64 	%rd251, %rd250;
	and.b64 	%rd252, %rd94, %rd251;
	sub.s32 	%r409, 52, %r151;
	mov.b64 	%rd253, 1;
	shl.b64 	%rd254, %rd253, %r409;
	setp.gt.u64 	%p66, %rd252, %rd254;
	setp.eq.b64 	%p67, %rd252, %rd254;
	and.b64 	%rd255, %rd248, 1;
	setp.ne.b64 	%p68, %rd255, 0;
	and.pred 	%p69, %p67, %p68;
	or.pred 	%p70, %p66, %p69;
	selp.b64 	%rd256, 1, 0, %p70;
	add.s64 	%rd99, %rd248, %rd256;
	shl.b64 	%rd100, %rd253, %r151;
	setp.eq.b64 	%p71, %rd99, %rd100;
	add.s32 	%r410, %r150, -1022;
	selp.b32 	%r156, %r410, %r154, %p71;
	setp.le.s32 	%p72, %r156, %r152;
	@%p72 bra 	$L__BB27_328;
	or.b32 	%r1415, %r149, %r153;
	bra.uni 	$L__BB27_329;
$L__BB27_328:
	selp.b32 	%r411, 1, 0, %p71;
	shr.u64 	%rd257, %rd99, %r411;
	add.s32 	%r412, %r156, %r152;
	add.s32 	%r413, %r151, -1;
	shl.b32 	%r414, %r412, %r413;
	shl.b64 	%rd258, %rd249, %r413;
	not.b64 	%rd259, %rd258;
	and.b64 	%rd260, %rd257, %rd259;
	cvt.u32.u64 	%r415, %rd260;
	or.b32 	%r416, %r414, %r415;
	or.b32 	%r1415, %r416, %r149;
$L__BB27_329:
	cvt.u16.u32 	%rs14, %r1415;
	bra.uni 	$L__BB27_330;
$L__BB27_484:
	neg.s32 	%r678, %r234;
	shl.b64 	%rd902, %rd146, %r678;
$L__BB27_487:
	or.b64 	%rd438, %rd902, %rd147;
	cvt.u16.u64 	%rs21, %rd438;
$L__BB27_492:
	setp.ne.b32 	%p241, %r1396, 13;
	cvt.u32.u16 	%r236, %rs21;
	@%p241 bra 	$L__BB27_494;
	shl.b32 	%r1429, %r236, 16;
	bra.uni 	$L__BB27_500;
$L__BB27_494:
	cvt.s32.s16 	%r679, %rs21;
	and.b32 	%r1429, %r679, -2147483648;
	bfe.u32 	%r237, %r236, 10, 5;
	setp.eq.b32 	%p242, %r237, 31;
	@%p242 bra 	$L__BB27_498;
	and.b32 	%r238, %r236, 1023;
	setp.ne.b32 	%p243, %r237, 0;
	@%p243 bra 	$L__BB27_499;
	setp.eq.b32 	%p244, %r238, 0;
	@%p244 bra 	$L__BB27_500;
	clz.b32 	%r682, %r238;
	xor.b32 	%r683, %r682, 31;
	sub.s32 	%r684, 9, %r683;
	shl.b32 	%r685, %r236, %r684;
	shl.b32 	%r686, %r683, 23;
	shl.b32 	%r687, %r685, 14;
	and.b32 	%r688, %r687, 8372224;
	add.s32 	%r689, %r686, %r1429;
	add.s32 	%r690, %r689, %r688;
	add.s32 	%r1429, %r690, 864026624;
	bra.uni 	$L__BB27_500;
$L__BB27_498:
	shl.b32 	%r680, %r236, 13;
	or.b32 	%r681, %r1429, %r680;
	or.b32 	%r1429, %r681, 2139095040;
	bra.uni 	$L__BB27_500;
$L__BB27_499:
	shl.b32 	%r691, %r237, 23;
	shl.b32 	%r692, %r238, 13;
	or.b32 	%r693, %r691, %r692;
	add.s32 	%r694, %r693, %r1429;
	add.s32 	%r1429, %r694, 939524096;
$L__BB27_500:
	add.rn.f32 	%r1418, %r137, %r1429;
	@%p677 bra 	$L__BB27_523;
	cvt.f64.f32 	%rd150, %r1418;
	shr.u64 	%rd152, %rd150, 48;
	cvt.u32.u64 	%r695, %rd152;
	and.b32 	%r239, %r695, 32768;
	shr.u64 	%rd439, %rd150, 52;
	cvt.u32.u64 	%r696, %rd439;
	and.b32 	%r240, %r696, 2047;
	setp.eq.b32 	%p246, %r240, 0;
	@%p246 bra 	$L__BB27_504;
	and.b64 	%rd151, %rd150, 4503599627370495;
	setp.eq.b32 	%p245, %r1396, 12;
	selp.b32 	%r241, 11, 8, %p245;
	selp.b32 	%r243, 31744, 32640, %p245;
	setp.ne.b32 	%p247, %r240, 2047;
	@%p247 bra 	$L__BB27_505;
	setp.eq.b64 	%p248, %rd151, 0;
	add.s32 	%r697, %r241, -2;
	mov.b32 	%r698, 1;
	shl.b32 	%r699, %r698, %r697;
	selp.b32 	%r700, 0, %r699, %p248;
	or.b32 	%r701, %r700, %r243;
	or.b32 	%r702, %r701, %r239;
	cvt.u16.u32 	%rs22, %r702;
	bra.uni 	$L__BB27_515;
$L__BB27_504:
	cvt.u16.u32 	%rs22, %r239;
	bra.uni 	$L__BB27_515;
$L__BB27_505:
	selp.b32 	%r703, -14, -126, %p245;
	add.s32 	%r244, %r240, -1023;
	or.b64 	%rd153, %rd151, 4503599627370496;
	setp.ge.s32 	%p249, %r244, %r703;
	@%p249 bra 	$L__BB27_511;
	and.b64 	%rd154, %rd152, 32768;
	selp.b32 	%r713, 28, -81, %p245;
	sub.s32 	%r245, %r713, %r244;
	setp.gt.s32 	%p257, %r245, 0;
	@%p257 bra 	$L__BB27_508;
	bra.uni 	$L__BB27_507;
$L__BB27_508:
	setp.gt.u32 	%p258, %r245, 63;
	mov.b64 	%rd903, 0;
	@%p258 bra 	$L__BB27_510;
	shr.u64 	%rd453, %rd153, %r245;
	mov.b64 	%rd454, -1;
	shl.b64 	%rd455, %rd454, %r245;
	not.b64 	%rd456, %rd455;
	and.b64 	%rd457, %rd153, %rd456;
	add.s32 	%r714, %r245, -1;
	mov.b64 	%rd458, 1;
	shl.b64 	%rd459, %rd458, %r714;
	setp.gt.u64 	%p259, %rd457, %rd459;
)QPTX";
        result += R"QPTX(
	setp.eq.b64 	%p260, %rd457, %rd459;
	and.b64 	%rd460, %rd453, 1;
	setp.ne.b64 	%p261, %rd460, 0;
	and.pred 	%p262, %p260, %p261;
	or.pred 	%p263, %p259, %p262;
	selp.b64 	%rd461, 1, 0, %p263;
	add.s64 	%rd903, %rd453, %rd461;
	bra.uni 	$L__BB27_510;
$L__BB27_511:
	selp.b32 	%r242, 15, 127, %p245;
	sub.s32 	%r704, 53, %r241;
	shr.u64 	%rd440, %rd153, %r704;
	mov.b64 	%rd441, -1;
	shl.b64 	%rd442, %rd441, %r704;
	not.b64 	%rd443, %rd442;
	and.b64 	%rd444, %rd150, %rd443;
	sub.s32 	%r705, 52, %r241;
	mov.b64 	%rd445, 1;
	shl.b64 	%rd446, %rd445, %r705;
	setp.gt.u64 	%p250, %rd444, %rd446;
	setp.eq.b64 	%p251, %rd444, %rd446;
	and.b64 	%rd447, %rd440, 1;
	setp.ne.b64 	%p252, %rd447, 0;
	and.pred 	%p253, %p251, %p252;
	or.pred 	%p254, %p250, %p253;
	selp.b64 	%rd448, 1, 0, %p254;
	add.s64 	%rd155, %rd440, %rd448;
	shl.b64 	%rd156, %rd445, %r241;
	setp.eq.b64 	%p255, %rd155, %rd156;
	add.s32 	%r706, %r240, -1022;
	selp.b32 	%r246, %r706, %r244, %p255;
	setp.le.s32 	%p256, %r246, %r242;
	@%p256 bra 	$L__BB27_513;
	or.b32 	%r1430, %r239, %r243;
	bra.uni 	$L__BB27_514;
$L__BB27_513:
	selp.b32 	%r707, 1, 0, %p255;
	shr.u64 	%rd449, %rd155, %r707;
	add.s32 	%r708, %r246, %r242;
	add.s32 	%r709, %r241, -1;
	shl.b32 	%r710, %r708, %r709;
	shl.b64 	%rd450, %rd441, %r709;
	not.b64 	%rd451, %rd450;
	and.b64 	%rd452, %rd449, %rd451;
	cvt.u32.u64 	%r711, %rd452;
	or.b32 	%r712, %r710, %r711;
	or.b32 	%r1430, %r712, %r239;
$L__BB27_514:
	cvt.u16.u32 	%rs22, %r1430;
	bra.uni 	$L__BB27_515;
$L__BB27_322:
	neg.s32 	%r419, %r155;
	shl.b64 	%rd895, %rd97, %r419;
$L__BB27_325:
	or.b64 	%rd270, %rd895, %rd98;
	cvt.u16.u64 	%rs14, %rd270;
$L__BB27_330:
	setp.ne.b32 	%p80, %r1396, 13;
	cvt.u32.u16 	%r157, %rs14;
	@%p80 bra 	$L__BB27_332;
	shl.b32 	%r1416, %r157, 16;
	bra.uni 	$L__BB27_338;
$L__BB27_332:
	cvt.s32.s16 	%r420, %rs14;
	and.b32 	%r1416, %r420, -2147483648;
	bfe.u32 	%r158, %r157, 10, 5;
	setp.eq.b32 	%p81, %r158, 31;
	@%p81 bra 	$L__BB27_336;
	and.b32 	%r159, %r157, 1023;
	setp.ne.b32 	%p82, %r158, 0;
	@%p82 bra 	$L__BB27_337;
	setp.eq.b32 	%p83, %r159, 0;
	@%p83 bra 	$L__BB27_338;
	clz.b32 	%r423, %r159;
	xor.b32 	%r424, %r423, 31;
	sub.s32 	%r425, 9, %r424;
	shl.b32 	%r426, %r157, %r425;
	shl.b32 	%r427, %r424, 23;
	shl.b32 	%r428, %r426, 14;
	and.b32 	%r429, %r428, 8372224;
	add.s32 	%r430, %r427, %r1416;
	add.s32 	%r431, %r430, %r429;
	add.s32 	%r1416, %r431, 864026624;
	bra.uni 	$L__BB27_338;
$L__BB27_336:
	shl.b32 	%r421, %r157, 13;
	or.b32 	%r422, %r1416, %r421;
	or.b32 	%r1416, %r422, 2139095040;
	bra.uni 	$L__BB27_338;
$L__BB27_337:
	shl.b32 	%r432, %r158, 23;
	shl.b32 	%r433, %r159, 13;
	or.b32 	%r434, %r432, %r433;
	add.s32 	%r435, %r434, %r1416;
	add.s32 	%r1416, %r435, 939524096;
$L__BB27_338:
	add.rn.f32 	%r1418, %r136, %r1416;
	@%p677 bra 	$L__BB27_361;
	cvt.f64.f32 	%rd101, %r1418;
	shr.u64 	%rd103, %rd101, 48;
	cvt.u32.u64 	%r436, %rd103;
	and.b32 	%r160, %r436, 32768;
	shr.u64 	%rd271, %rd101, 52;
	cvt.u32.u64 	%r437, %rd271;
	and.b32 	%r161, %r437, 2047;
	setp.eq.b32 	%p85, %r161, 0;
	@%p85 bra 	$L__BB27_342;
	and.b64 	%rd102, %rd101, 4503599627370495;
	setp.eq.b32 	%p84, %r1396, 12;
	selp.b32 	%r162, 11, 8, %p84;
	selp.b32 	%r164, 31744, 32640, %p84;
	setp.ne.b32 	%p86, %r161, 2047;
	@%p86 bra 	$L__BB27_343;
	setp.eq.b64 	%p87, %rd102, 0;
	add.s32 	%r438, %r162, -2;
	mov.b32 	%r439, 1;
	shl.b32 	%r440, %r439, %r438;
	selp.b32 	%r441, 0, %r440, %p87;
	or.b32 	%r442, %r441, %r164;
	or.b32 	%r443, %r442, %r160;
	cvt.u16.u32 	%rs15, %r443;
	bra.uni 	$L__BB27_353;
$L__BB27_342:
	cvt.u16.u32 	%rs15, %r160;
	bra.uni 	$L__BB27_353;
$L__BB27_343:
	selp.b32 	%r444, -14, -126, %p84;
	add.s32 	%r165, %r161, -1023;
	or.b64 	%rd104, %rd102, 4503599627370496;
	setp.ge.s32 	%p88, %r165, %r444;
	@%p88 bra 	$L__BB27_349;
	and.b64 	%rd105, %rd103, 32768;
	selp.b32 	%r454, 28, -81, %p84;
	sub.s32 	%r166, %r454, %r165;
	setp.gt.s32 	%p96, %r166, 0;
	@%p96 bra 	$L__BB27_346;
	bra.uni 	$L__BB27_345;
$L__BB27_346:
	setp.gt.u32 	%p97, %r166, 63;
	mov.b64 	%rd896, 0;
	@%p97 bra 	$L__BB27_348;
	shr.u64 	%rd285, %rd104, %r166;
	mov.b64 	%rd286, -1;
	shl.b64 	%rd287, %rd286, %r166;
	not.b64 	%rd288, %rd287;
	and.b64 	%rd289, %rd104, %rd288;
	add.s32 	%r455, %r166, -1;
	mov.b64 	%rd290, 1;
	shl.b64 	%rd291, %rd290, %r455;
	setp.gt.u64 	%p98, %rd289, %rd291;
	setp.eq.b64 	%p99, %rd289, %rd291;
	and.b64 	%rd292, %rd285, 1;
	setp.ne.b64 	%p100, %rd292, 0;
	and.pred 	%p101, %p99, %p100;
	or.pred 	%p102, %p98, %p101;
	selp.b64 	%rd293, 1, 0, %p102;
	add.s64 	%rd896, %rd285, %rd293;
	bra.uni 	$L__BB27_348;
$L__BB27_349:
	selp.b32 	%r163, 15, 127, %p84;
	sub.s32 	%r445, 53, %r162;
	shr.u64 	%rd272, %rd104, %r445;
	mov.b64 	%rd273, -1;
	shl.b64 	%rd274, %rd273, %r445;
	not.b64 	%rd275, %rd274;
	and.b64 	%rd276, %rd101, %rd275;
	sub.s32 	%r446, 52, %r162;
	mov.b64 	%rd277, 1;
	shl.b64 	%rd278, %rd277, %r446;
	setp.gt.u64 	%p89, %rd276, %rd278;
	setp.eq.b64 	%p90, %rd276, %rd278;
	and.b64 	%rd279, %rd272, 1;
	setp.ne.b64 	%p91, %rd279, 0;
	and.pred 	%p92, %p90, %p91;
	or.pred 	%p93, %p89, %p92;
	selp.b64 	%rd280, 1, 0, %p93;
	add.s64 	%rd106, %rd272, %rd280;
	shl.b64 	%rd107, %rd277, %r162;
	setp.eq.b64 	%p94, %rd106, %rd107;
	add.s32 	%r447, %r161, -1022;
	selp.b32 	%r167, %r447, %r165, %p94;
	setp.le.s32 	%p95, %r167, %r163;
	@%p95 bra 	$L__BB27_351;
	or.b32 	%r1417, %r160, %r164;
	bra.uni 	$L__BB27_352;
$L__BB27_351:
	selp.b32 	%r448, 1, 0, %p94;
	shr.u64 	%rd281, %rd106, %r448;
	add.s32 	%r449, %r167, %r163;
	add.s32 	%r450, %r162, -1;
	shl.b32 	%r451, %r449, %r450;
	shl.b64 	%rd282, %rd273, %r450;
	not.b64 	%rd283, %rd282;
	and.b64 	%rd284, %rd281, %rd283;
	cvt.u32.u64 	%r452, %rd284;
	or.b32 	%r453, %r451, %r452;
	or.b32 	%r1417, %r453, %r160;
$L__BB27_352:
	cvt.u16.u32 	%rs15, %r1417;
	bra.uni 	$L__BB27_353;
$L__BB27_507:
	neg.s32 	%r715, %r245;
	shl.b64 	%rd903, %rd153, %r715;
$L__BB27_510:
	or.b64 	%rd462, %rd903, %rd154;
	cvt.u16.u64 	%rs22, %rd462;
$L__BB27_515:
	setp.ne.b32 	%p264, %r1396, 13;
	cvt.u32.u16 	%r247, %rs22;
	@%p264 bra 	$L__BB27_517;
	shl.b32 	%r1418, %r247, 16;
	bra.uni 	$L__BB27_523;
$L__BB27_517:
	cvt.s32.s16 	%r716, %rs22;
	and.b32 	%r1418, %r716, -2147483648;
	bfe.u32 	%r248, %r247, 10, 5;
	setp.eq.b32 	%p265, %r248, 31;
	@%p265 bra 	$L__BB27_521;
	and.b32 	%r249, %r247, 1023;
	setp.ne.b32 	%p266, %r248, 0;
	@%p266 bra 	$L__BB27_522;
	setp.eq.b32 	%p267, %r249, 0;
	@%p267 bra 	$L__BB27_523;
	clz.b32 	%r719, %r249;
	xor.b32 	%r720, %r719, 31;
	sub.s32 	%r721, 9, %r720;
	shl.b32 	%r722, %r247, %r721;
	shl.b32 	%r723, %r720, 23;
	shl.b32 	%r724, %r722, 14;
	and.b32 	%r725, %r724, 8372224;
	add.s32 	%r726, %r723, %r1418;
	add.s32 	%r727, %r726, %r725;
	add.s32 	%r1418, %r727, 864026624;
	bra.uni 	$L__BB27_523;
$L__BB27_521:
	shl.b32 	%r717, %r247, 13;
	or.b32 	%r718, %r1418, %r717;
	or.b32 	%r1418, %r718, 2139095040;
	bra.uni 	$L__BB27_523;
$L__BB27_522:
	shl.b32 	%r728, %r248, 23;
	shl.b32 	%r729, %r249, 13;
	or.b32 	%r730, %r728, %r729;
	add.s32 	%r731, %r730, %r1418;
	add.s32 	%r1418, %r731, 939524096;
$L__BB27_523:
	ld.local.b32 	%r250, [%rd1];
	mul.rn.f32 	%r1432, %r1414, %r250;
	@%p677 bra 	$L__BB27_546;
	cvt.f64.f32 	%rd157, %r1432;
	shr.u64 	%rd159, %rd157, 48;
	cvt.u32.u64 	%r732, %rd159;
	and.b32 	%r251, %r732, 32768;
	shr.u64 	%rd463, %rd157, 52;
	cvt.u32.u64 	%r733, %rd463;
	and.b32 	%r252, %r733, 2047;
	setp.eq.b32 	%p269, %r252, 0;
	@%p269 bra 	$L__BB27_527;
	and.b64 	%rd158, %rd157, 4503599627370495;
	setp.eq.b32 	%p268, %r1396, 12;
	selp.b32 	%r253, 11, 8, %p268;
	selp.b32 	%r255, 31744, 32640, %p268;
	setp.ne.b32 	%p270, %r252, 2047;
	@%p270 bra 	$L__BB27_528;
	setp.eq.b64 	%p271, %rd158, 0;
	add.s32 	%r734, %r253, -2;
	mov.b32 	%r735, 1;
	shl.b32 	%r736, %r735, %r734;
	selp.b32 	%r737, 0, %r736, %p271;
	or.b32 	%r738, %r737, %r255;
	or.b32 	%r739, %r738, %r251;
	cvt.u16.u32 	%rs23, %r739;
	bra.uni 	$L__BB27_538;
$L__BB27_527:
	cvt.u16.u32 	%rs23, %r251;
	bra.uni 	$L__BB27_538;
$L__BB27_528:
	selp.b32 	%r740, -14, -126, %p268;
	add.s32 	%r256, %r252, -1023;
	or.b64 	%rd160, %rd158, 4503599627370496;
	setp.ge.s32 	%p272, %r256, %r740;
	@%p272 bra 	$L__BB27_534;
	and.b64 	%rd161, %rd159, 32768;
	selp.b32 	%r750, 28, -81, %p268;
	sub.s32 	%r257, %r750, %r256;
	setp.gt.s32 	%p280, %r257, 0;
	@%p280 bra 	$L__BB27_531;
	bra.uni 	$L__BB27_530;
$L__BB27_531:
	setp.gt.u32 	%p281, %r257, 63;
	mov.b64 	%rd904, 0;
	@%p281 bra 	$L__BB27_533;
	shr.u64 	%rd477, %rd160, %r257;
	mov.b64 	%rd478, -1;
	shl.b64 	%rd479, %rd478, %r257;
	not.b64 	%rd480, %rd479;
	and.b64 	%rd481, %rd160, %rd480;
	add.s32 	%r751, %r257, -1;
	mov.b64 	%rd482, 1;
	shl.b64 	%rd483, %rd482, %r751;
	setp.gt.u64 	%p282, %rd481, %rd483;
	setp.eq.b64 	%p283, %rd481, %rd483;
	and.b64 	%rd484, %rd477, 1;
	setp.ne.b64 	%p284, %rd484, 0;
	and.pred 	%p285, %p283, %p284;
	or.pred 	%p286, %p282, %p285;
	selp.b64 	%rd485, 1, 0, %p286;
	add.s64 	%rd904, %rd477, %rd485;
	bra.uni 	$L__BB27_533;
$L__BB27_534:
	selp.b32 	%r254, 15, 127, %p268;
	sub.s32 	%r741, 53, %r253;
	shr.u64 	%rd464, %rd160, %r741;
	mov.b64 	%rd465, -1;
	shl.b64 	%rd466, %rd465, %r741;
	not.b64 	%rd467, %rd466;
	and.b64 	%rd468, %rd157, %rd467;
	sub.s32 	%r742, 52, %r253;
	mov.b64 	%rd469, 1;
	shl.b64 	%rd470, %rd469, %r742;
	setp.gt.u64 	%p273, %rd468, %rd470;
	setp.eq.b64 	%p274, %rd468, %rd470;
	and.b64 	%rd471, %rd464, 1;
	setp.ne.b64 	%p275, %rd471, 0;
	and.pred 	%p276, %p274, %p275;
	or.pred 	%p277, %p273, %p276;
	selp.b64 	%rd472, 1, 0, %p277;
	add.s64 	%rd162, %rd464, %rd472;
	shl.b64 	%rd163, %rd469, %r253;
	setp.eq.b64 	%p278, %rd162, %rd163;
	add.s32 	%r743, %r252, -1022;
	selp.b32 	%r258, %r743, %r256, %p278;
	setp.le.s32 	%p279, %r258, %r254;
	@%p279 bra 	$L__BB27_536;
	or.b32 	%r1431, %r251, %r255;
	bra.uni 	$L__BB27_537;
$L__BB27_536:
	selp.b32 	%r744, 1, 0, %p278;
	shr.u64 	%rd473, %rd162, %r744;
	add.s32 	%r745, %r258, %r254;
	add.s32 	%r746, %r253, -1;
	shl.b32 	%r747, %r745, %r746;
	shl.b64 	%rd474, %rd465, %r746;
	not.b64 	%rd475, %rd474;
	and.b64 	%rd476, %rd473, %rd475;
	cvt.u32.u64 	%r748, %rd476;
	or.b32 	%r749, %r747, %r748;
	or.b32 	%r1431, %r749, %r251;
$L__BB27_537:
	cvt.u16.u32 	%rs23, %r1431;
	bra.uni 	$L__BB27_538;
$L__BB27_345:
	neg.s32 	%r456, %r166;
	shl.b64 	%rd896, %rd104, %r456;
$L__BB27_348:
	or.b64 	%rd294, %rd896, %rd105;
	cvt.u16.u64 	%rs15, %rd294;
$L__BB27_353:
	setp.ne.b32 	%p103, %r1396, 13;
	cvt.u32.u16 	%r168, %rs15;
	@%p103 bra 	$L__BB27_355;
	shl.b32 	%r1418, %r168, 16;
	bra.uni 	$L__BB27_361;
$L__BB27_355:
	cvt.s32.s16 	%r457, %rs15;
	and.b32 	%r1418, %r457, -2147483648;
	bfe.u32 	%r169, %r168, 10, 5;
	setp.eq.b32 	%p104, %r169, 31;
	@%p104 bra 	$L__BB27_359;
	and.b32 	%r170, %r168, 1023;
	setp.ne.b32 	%p105, %r169, 0;
	@%p105 bra 	$L__BB27_360;
	setp.eq.b32 	%p106, %r170, 0;
	@%p106 bra 	$L__BB27_361;
	clz.b32 	%r460, %r170;
	xor.b32 	%r461, %r460, 31;
	sub.s32 	%r462, 9, %r461;
	shl.b32 	%r463, %r168, %r462;
	shl.b32 	%r464, %r461, 23;
	shl.b32 	%r465, %r463, 14;
	and.b32 	%r466, %r465, 8372224;
	add.s32 	%r467, %r464, %r1418;
	add.s32 	%r468, %r467, %r466;
	add.s32 	%r1418, %r468, 864026624;
	bra.uni 	$L__BB27_361;
$L__BB27_359:
	shl.b32 	%r458, %r168, 13;
	or.b32 	%r459, %r1418, %r458;
	or.b32 	%r1418, %r459, 2139095040;
	bra.uni 	$L__BB27_361;
$L__BB27_360:
	shl.b32 	%r469, %r169, 23;
	shl.b32 	%r470, %r170, 13;
	or.b32 	%r471, %r469, %r470;
	add.s32 	%r472, %r471, %r1418;
	add.s32 	%r1418, %r472, 939524096;
$L__BB27_361:
	ld.local.b32 	%r171, [%rd1];
	ld.local.b32 	%r172, [%rd1+4];
	mul.rn.f32 	%r1420, %r1414, %r172;
	@%p677 bra 	$L__BB27_384;
	cvt.f64.f32 	%rd108, %r1420;
	shr.u64 	%rd110, %rd108, 48;
	cvt.u32.u64 	%r473, %rd110;
	and.b32 	%r173, %r473, 32768;
	shr.u64 	%rd295, %rd108, 52;
	cvt.u32.u64 	%r474, %rd295;
	and.b32 	%r174, %r474, 2047;
	setp.eq.b32 	%p108, %r174, 0;
	@%p108 bra 	$L__BB27_365;
	and.b64 	%rd109, %rd108, 4503599627370495;
	setp.eq.b32 	%p107, %r1396, 12;
	selp.b32 	%r175, 11, 8, %p107;
	selp.b32 	%r177, 31744, 32640, %p107;
	setp.ne.b32 	%p109, %r174, 2047;
	@%p109 bra 	$L__BB27_366;
	setp.eq.b64 	%p110, %rd109, 0;
	add.s32 	%r475, %r175, -2;
	mov.b32 	%r476, 1;
	shl.b32 	%r477, %r476, %r475;
	selp.b32 	%r478, 0, %r477, %p110;
	or.b32 	%r479, %r478, %r177;
	or.b32 	%r480, %r479, %r173;
	cvt.u16.u32 	%rs16, %r480;
	bra.uni 	$L__BB27_376;
$L__BB27_365:
	cvt.u16.u32 	%rs16, %r173;
	bra.uni 	$L__BB27_376;
$L__BB27_366:
	selp.b32 	%r481, -14, -126, %p107;
	add.s32 	%r178, %r174, -1023;
	or.b64 	%rd111, %rd109, 4503599627370496;
	setp.ge.s32 	%p111, %r178, %r481;
	@%p111 bra 	$L__BB27_372;
	and.b64 	%rd112, %rd110, 32768;
	selp.b32 	%r491, 28, -81, %p107;
	sub.s32 	%r179, %r491, %r178;
	setp.gt.s32 	%p119, %r179, 0;
	@%p119 bra 	$L__BB27_369;
	bra.uni 	$L__BB27_368;
$L__BB27_369:
	setp.gt.u32 	%p120, %r179, 63;
	mov.b64 	%rd897, 0;
	@%p120 bra 	$L__BB27_371;
	shr.u64 	%rd309, %rd111, %r179;
	mov.b64 	%rd310, -1;
	shl.b64 	%rd311, %rd310, %r179;
	not.b64 	%rd312, %rd311;
	and.b64 	%rd313, %rd111, %rd312;
	add.s32 	%r492, %r179, -1;
	mov.b64 	%rd314, 1;
	shl.b64 	%rd315, %rd314, %r492;
	setp.gt.u64 	%p121, %rd313, %rd315;
	setp.eq.b64 	%p122, %rd313, %rd315;
	and.b64 	%rd316, %rd309, 1;
	setp.ne.b64 	%p123, %rd316, 0;
	and.pred 	%p124, %p122, %p123;
	or.pred 	%p125, %p121, %p124;
	selp.b64 	%rd317, 1, 0, %p125;
	add.s64 	%rd897, %rd309, %rd317;
	bra.uni 	$L__BB27_371;
$L__BB27_372:
	selp.b32 	%r176, 15, 127, %p107;
	sub.s32 	%r482, 53, %r175;
	shr.u64 	%rd296, %rd111, %r482;
	mov.b64 	%rd297, -1;
	shl.b64 	%rd298, %rd297, %r482;
	not.b64 	%rd299, %rd298;
	and.b64 	%rd300, %rd108, %rd299;
	sub.s32 	%r483, 52, %r175;
	mov.b64 	%rd301, 1;
	shl.b64 	%rd302, %rd301, %r483;
	setp.gt.u64 	%p112, %rd300, %rd302;
	setp.eq.b64 	%p113, %rd300, %rd302;
	and.b64 	%rd303, %rd296, 1;
	setp.ne.b64 	%p114, %rd303, 0;
	and.pred 	%p115, %p113, %p114;
	or.pred 	%p116, %p112, %p115;
	selp.b64 	%rd304, 1, 0, %p116;
	add.s64 	%rd113, %rd296, %rd304;
	shl.b64 	%rd114, %rd301, %r175;
	setp.eq.b64 	%p117, %rd113, %rd114;
	add.s32 	%r484, %r174, -1022;
	selp.b32 	%r180, %r484, %r178, %p117;
	setp.le.s32 	%p118, %r180, %r176;
	@%p118 bra 	$L__BB27_374;
	or.b32 	%r1419, %r173, %r177;
	bra.uni 	$L__BB27_375;
$L__BB27_374:
	selp.b32 	%r485, 1, 0, %p117;
	shr.u64 	%rd305, %rd113, %r485;
	add.s32 	%r486, %r180, %r176;
	add.s32 	%r487, %r175, -1;
	shl.b32 	%r488, %r486, %r487;
	shl.b64 	%rd306, %rd297, %r487;
	not.b64 	%rd307, %rd306;
	and.b64 	%rd308, %rd305, %rd307;
	cvt.u32.u64 	%r489, %rd308;
	or.b32 	%r490, %r488, %r489;
	or.b32 	%r1419, %r490, %r173;
$L__BB27_375:
	cvt.u16.u32 	%rs16, %r1419;
	bra.uni 	$L__BB27_376;
$L__BB27_530:
	neg.s32 	%r752, %r257;
	shl.b64 	%rd904, %rd160, %r752;
$L__BB27_533:
	or.b64 	%rd486, %rd904, %rd161;
	cvt.u16.u64 	%rs23, %rd486;
$L__BB27_538:
	setp.ne.b32 	%p287, %r1396, 13;
	cvt.u32.u16 	%r259, %rs23;
	@%p287 bra 	$L__BB27_540;
	shl.b32 	%r1432, %r259, 16;
	bra.uni 	$L__BB27_546;
$L__BB27_540:
	cvt.s32.s16 	%r753, %rs23;
	and.b32 	%r1432, %r753, -2147483648;
	bfe.u32 	%r260, %r259, 10, 5;
	setp.eq.b32 	%p288, %r260, 31;
	@%p288 bra 	$L__BB27_544;
	and.b32 	%r261, %r259, 1023;
	setp.ne.b32 	%p289, %r260, 0;
	@%p289 bra 	$L__BB27_545;
	setp.eq.b32 	%p290, %r261, 0;
	@%p290 bra 	$L__BB27_546;
	clz.b32 	%r756, %r261;
	xor.b32 	%r757, %r756, 31;
	sub.s32 	%r758, 9, %r757;
	shl.b32 	%r759, %r259, %r758;
	shl.b32 	%r760, %r757, 23;
	shl.b32 	%r761, %r759, 14;
	and.b32 	%r762, %r761, 8372224;
	add.s32 	%r763, %r760, %r1432;
	add.s32 	%r764, %r763, %r762;
	add.s32 	%r1432, %r764, 864026624;
	bra.uni 	$L__BB27_546;
$L__BB27_544:
	shl.b32 	%r754, %r259, 13;
	or.b32 	%r755, %r1432, %r754;
	or.b32 	%r1432, %r755, 2139095040;
	bra.uni 	$L__BB27_546;
$L__BB27_545:
	shl.b32 	%r765, %r260, 23;
	shl.b32 	%r766, %r261, 13;
	or.b32 	%r767, %r765, %r766;
	add.s32 	%r768, %r767, %r1432;
	add.s32 	%r1432, %r768, 939524096;
$L__BB27_546:
	ld.local.b32 	%r262, [%rd1+4];
	add.rn.f32 	%r1422, %r1432, %r262;
	@%p677 bra 	$L__BB27_569;
	cvt.f64.f32 	%rd164, %r1422;
	shr.u64 	%rd166, %rd164, 48;
	cvt.u32.u64 	%r769, %rd166;
	and.b32 	%r263, %r769, 32768;
	shr.u64 	%rd487, %rd164, 52;
	cvt.u32.u64 	%r770, %rd487;
	and.b32 	%r264, %r770, 2047;
	setp.eq.b32 	%p292, %r264, 0;
	@%p292 bra 	$L__BB27_550;
	and.b64 	%rd165, %rd164, 4503599627370495;
	setp.eq.b32 	%p291, %r1396, 12;
	selp.b32 	%r265, 11, 8, %p291;
	selp.b32 	%r267, 31744, 32640, %p291;
	setp.ne.b32 	%p293, %r264, 2047;
	@%p293 bra 	$L__BB27_551;
	setp.eq.b64 	%p294, %rd165, 0;
	add.s32 	%r771, %r265, -2;
	mov.b32 	%r772, 1;
	shl.b32 	%r773, %r772, %r771;
	selp.b32 	%r774, 0, %r773, %p294;
	or.b32 	%r775, %r774, %r267;
	or.b32 	%r776, %r775, %r263;
	cvt.u16.u32 	%rs24, %r776;
	bra.uni 	$L__BB27_561;
$L__BB27_550:
	cvt.u16.u32 	%rs24, %r263;
	bra.uni 	$L__BB27_561;
$L__BB27_551:
	selp.b32 	%r777, -14, -126, %p291;
	add.s32 	%r268, %r264, -1023;
	or.b64 	%rd167, %rd165, 4503599627370496;
	setp.ge.s32 	%p295, %r268, %r777;
	@%p295 bra 	$L__BB27_557;
	and.b64 	%rd168, %rd166, 32768;
	selp.b32 	%r787, 28, -81, %p291;
	sub.s32 	%r269, %r787, %r268;
	setp.gt.s32 	%p303, %r269, 0;
	@%p303 bra 	$L__BB27_554;
	bra.uni 	$L__BB27_553;
$L__BB27_554:
	setp.gt.u32 	%p304, %r269, 63;
	mov.b64 	%rd905, 0;
	@%p304 bra 	$L__BB27_556;
	shr.u64 	%rd501, %rd167, %r269;
	mov.b64 	%rd502, -1;
	shl.b64 	%rd503, %rd502, %r269;
	not.b64 	%rd504, %rd503;
	and.b64 	%rd505, %rd167, %rd504;
	add.s32 	%r788, %r269, -1;
	mov.b64 	%rd506, 1;
	shl.b64 	%rd507, %rd506, %r788;
	setp.gt.u64 	%p305, %rd505, %rd507;
	setp.eq.b64 	%p306, %rd505, %rd507;
	and.b64 	%rd508, %rd501, 1;
	setp.ne.b64 	%p307, %rd508, 0;
	and.pred 	%p308, %p306, %p307;
	or.pred 	%p309, %p305, %p308;
	selp.b64 	%rd509, 1, 0, %p309;
	add.s64 	%rd905, %rd501, %rd509;
	bra.uni 	$L__BB27_556;
$L__BB27_557:
	selp.b32 	%r266, 15, 127, %p291;
	sub.s32 	%r778, 53, %r265;
	shr.u64 	%rd488, %rd167, %r778;
	mov.b64 	%rd489, -1;
	shl.b64 	%rd490, %rd489, %r778;
	not.b64 	%rd491, %rd490;
	and.b64 	%rd492, %rd164, %rd491;
	sub.s32 	%r779, 52, %r265;
	mov.b64 	%rd493, 1;
	shl.b64 	%rd494, %rd493, %r779;
	setp.gt.u64 	%p296, %rd492, %rd494;
	setp.eq.b64 	%p297, %rd492, %rd494;
	and.b64 	%rd495, %rd488, 1;
	setp.ne.b64 	%p298, %rd495, 0;
	and.pred 	%p299, %p297, %p298;
	or.pred 	%p300, %p296, %p299;
	selp.b64 	%rd496, 1, 0, %p300;
	add.s64 	%rd169, %rd488, %rd496;
	shl.b64 	%rd170, %rd493, %r265;
	setp.eq.b64 	%p301, %rd169, %rd170;
	add.s32 	%r780, %r264, -1022;
	selp.b32 	%r270, %r780, %r268, %p301;
	setp.le.s32 	%p302, %r270, %r266;
	@%p302 bra 	$L__BB27_559;
	or.b32 	%r1433, %r263, %r267;
	bra.uni 	$L__BB27_560;
$L__BB27_559:
	selp.b32 	%r781, 1, 0, %p301;
	shr.u64 	%rd497, %rd169, %r781;
	add.s32 	%r782, %r270, %r266;
	add.s32 	%r783, %r265, -1;
	shl.b32 	%r784, %r782, %r783;
	shl.b64 	%rd498, %rd489, %r783;
	not.b64 	%rd499, %rd498;
	and.b64 	%rd500, %rd497, %rd499;
	cvt.u32.u64 	%r785, %rd500;
	or.b32 	%r786, %r784, %r785;
	or.b32 	%r1433, %r786, %r263;
$L__BB27_560:
	cvt.u16.u32 	%rs24, %r1433;
	bra.uni 	$L__BB27_561;
$L__BB27_368:
	neg.s32 	%r493, %r179;
	shl.b64 	%rd897, %rd111, %r493;
$L__BB27_371:
	or.b64 	%rd318, %rd897, %rd112;
	cvt.u16.u64 	%rs16, %rd318;
$L__BB27_376:
	setp.ne.b32 	%p126, %r1396, 13;
	cvt.u32.u16 	%r181, %rs16;
	@%p126 bra 	$L__BB27_378;
	shl.b32 	%r1420, %r181, 16;
	bra.uni 	$L__BB27_384;
$L__BB27_378:
	cvt.s32.s16 	%r494, %rs16;
	and.b32 	%r1420, %r494, -2147483648;
	bfe.u32 	%r182, %r181, 10, 5;
	setp.eq.b32 	%p127, %r182, 31;
	@%p127 bra 	$L__BB27_382;
	and.b32 	%r183, %r181, 1023;
	setp.ne.b32 	%p128, %r182, 0;
	@%p128 bra 	$L__BB27_383;
	setp.eq.b32 	%p129, %r183, 0;
	@%p129 bra 	$L__BB27_384;
	clz.b32 	%r497, %r183;
	xor.b32 	%r498, %r497, 31;
	sub.s32 	%r499, 9, %r498;
	shl.b32 	%r500, %r181, %r499;
	shl.b32 	%r501, %r498, 23;
	shl.b32 	%r502, %r500, 14;
	and.b32 	%r503, %r502, 8372224;
	add.s32 	%r504, %r501, %r1420;
	add.s32 	%r505, %r504, %r503;
	add.s32 	%r1420, %r505, 864026624;
	bra.uni 	$L__BB27_384;
$L__BB27_382:
	shl.b32 	%r495, %r181, 13;
	or.b32 	%r496, %r1420, %r495;
	or.b32 	%r1420, %r496, 2139095040;
	bra.uni 	$L__BB27_384;
$L__BB27_383:
	shl.b32 	%r506, %r182, 23;
	shl.b32 	%r507, %r183, 13;
	or.b32 	%r508, %r506, %r507;
	add.s32 	%r509, %r508, %r1420;
	add.s32 	%r1420, %r509, 939524096;
$L__BB27_384:
	add.rn.f32 	%r1422, %r171, %r1420;
	@%p677 bra 	$L__BB27_407;
	cvt.f64.f32 	%rd115, %r1422;
	shr.u64 	%rd117, %rd115, 48;
	cvt.u32.u64 	%r510, %rd117;
	and.b32 	%r184, %r510, 32768;
	shr.u64 	%rd319, %rd115, 52;
	cvt.u32.u64 	%r511, %rd319;
	and.b32 	%r185, %r511, 2047;
	setp.eq.b32 	%p131, %r185, 0;
	@%p131 bra 	$L__BB27_388;
	and.b64 	%rd116, %rd115, 4503599627370495;
	setp.eq.b32 	%p130, %r1396, 12;
	selp.b32 	%r186, 11, 8, %p130;
	selp.b32 	%r188, 31744, 32640, %p130;
	setp.ne.b32 	%p132, %r185, 2047;
	@%p132 bra 	$L__BB27_389;
	setp.eq.b64 	%p133, %rd116, 0;
	add.s32 	%r512, %r186, -2;
	mov.b32 	%r513, 1;
	shl.b32 	%r514, %r513, %r512;
	selp.b32 	%r515, 0, %r514, %p133;
	or.b32 	%r516, %r515, %r188;
	or.b32 	%r517, %r516, %r184;
	cvt.u16.u32 	%rs17, %r517;
	bra.uni 	$L__BB27_399;
$L__BB27_388:
	cvt.u16.u32 	%rs17, %r184;
	bra.uni 	$L__BB27_399;
$L__BB27_389:
	selp.b32 	%r518, -14, -126, %p130;
	add.s32 	%r189, %r185, -1023;
	or.b64 	%rd118, %rd116, 4503599627370496;
	setp.ge.s32 	%p134, %r189, %r518;
	@%p134 bra 	$L__BB27_395;
	and.b64 	%rd119, %rd117, 32768;
	selp.b32 	%r528, 28, -81, %p130;
	sub.s32 	%r190, %r528, %r189;
	setp.gt.s32 	%p142, %r190, 0;
	@%p142 bra 	$L__BB27_392;
	bra.uni 	$L__BB27_391;
$L__BB27_392:
	setp.gt.u32 	%p143, %r190, 63;
	mov.b64 	%rd898, 0;
	@%p143 bra 	$L__BB27_394;
	shr.u64 	%rd333, %rd118, %r190;
	mov.b64 	%rd334, -1;
	shl.b64 	%rd335, %rd334, %r190;
	not.b64 	%rd336, %rd335;
	and.b64 	%rd337, %rd118, %rd336;
	add.s32 	%r529, %r190, -1;
	mov.b64 	%rd338, 1;
	shl.b64 	%rd339, %rd338, %r529;
	setp.gt.u64 	%p144, %rd337, %rd339;
	setp.eq.b64 	%p145, %rd337, %rd339;
	and.b64 	%rd340, %rd333, 1;
	setp.ne.b64 	%p146, %rd340, 0;
	and.pred 	%p147, %p145, %p146;
	or.pred 	%p148, %p144, %p147;
	selp.b64 	%rd341, 1, 0, %p148;
	add.s64 	%rd898, %rd333, %rd341;
	bra.uni 	$L__BB27_394;
$L__BB27_395:
	selp.b32 	%r187, 15, 127, %p130;
	sub.s32 	%r519, 53, %r186;
	shr.u64 	%rd320, %rd118, %r519;
	mov.b64 	%rd321, -1;
	shl.b64 	%rd322, %rd321, %r519;
	not.b64 	%rd323, %rd322;
	and.b64 	%rd324, %rd115, %rd323;
	sub.s32 	%r520, 52, %r186;
	mov.b64 	%rd325, 1;
	shl.b64 	%rd326, %rd325, %r520;
	setp.gt.u64 	%p135, %rd324, %rd326;
	setp.eq.b64 	%p136, %rd324, %rd326;
	and.b64 	%rd327, %rd320, 1;
	setp.ne.b64 	%p137, %rd327, 0;
	and.pred 	%p138, %p136, %p137;
	or.pred 	%p139, %p135, %p138;
	selp.b64 	%rd328, 1, 0, %p139;
	add.s64 	%rd120, %rd320, %rd328;
	shl.b64 	%rd121, %rd325, %r186;
	setp.eq.b64 	%p140, %rd120, %rd121;
	add.s32 	%r521, %r185, -1022;
	selp.b32 	%r191, %r521, %r189, %p140;
	setp.le.s32 	%p141, %r191, %r187;
	@%p141 bra 	$L__BB27_397;
	or.b32 	%r1421, %r184, %r188;
	bra.uni 	$L__BB27_398;
$L__BB27_397:
	selp.b32 	%r522, 1, 0, %p140;
	shr.u64 	%rd329, %rd120, %r522;
	add.s32 	%r523, %r191, %r187;
	add.s32 	%r524, %r186, -1;
	shl.b32 	%r525, %r523, %r524;
	shl.b64 	%rd330, %rd321, %r524;
	not.b64 	%rd331, %rd330;
	and.b64 	%rd332, %rd329, %rd331;
	cvt.u32.u64 	%r526, %rd332;
	or.b32 	%r527, %r525, %r526;
	or.b32 	%r1421, %r527, %r184;
$L__BB27_398:
	cvt.u16.u32 	%rs17, %r1421;
	bra.uni 	$L__BB27_399;
$L__BB27_553:
	neg.s32 	%r789, %r269;
	shl.b64 	%rd905, %rd167, %r789;
$L__BB27_556:
	or.b64 	%rd510, %rd905, %rd168;
	cvt.u16.u64 	%rs24, %rd510;
$L__BB27_561:
	setp.ne.b32 	%p310, %r1396, 13;
	cvt.u32.u16 	%r271, %rs24;
	@%p310 bra 	$L__BB27_563;
	shl.b32 	%r1422, %r271, 16;
	bra.uni 	$L__BB27_569;
$L__BB27_563:
	cvt.s32.s16 	%r790, %rs24;
	and.b32 	%r1422, %r790, -2147483648;
	bfe.u32 	%r272, %r271, 10, 5;
	setp.eq.b32 	%p311, %r272, 31;
	@%p311 bra 	$L__BB27_567;
	and.b32 	%r273, %r271, 1023;
	setp.ne.b32 	%p312, %r272, 0;
	@%p312 bra 	$L__BB27_568;
	setp.eq.b32 	%p313, %r273, 0;
	@%p313 bra 	$L__BB27_569;
	clz.b32 	%r793, %r273;
	xor.b32 	%r794, %r793, 31;
	sub.s32 	%r795, 9, %r794;
	shl.b32 	%r796, %r271, %r795;
	shl.b32 	%r797, %r794, 23;
	shl.b32 	%r798, %r796, 14;
	and.b32 	%r799, %r798, 8372224;
	add.s32 	%r800, %r797, %r1422;
	add.s32 	%r801, %r800, %r799;
	add.s32 	%r1422, %r801, 864026624;
	bra.uni 	$L__BB27_569;
$L__BB27_567:
	shl.b32 	%r791, %r271, 13;
	or.b32 	%r792, %r1422, %r791;
	or.b32 	%r1422, %r792, 2139095040;
	bra.uni 	$L__BB27_569;
$L__BB27_568:
	shl.b32 	%r802, %r272, 23;
	shl.b32 	%r803, %r273, 13;
	or.b32 	%r804, %r802, %r803;
	add.s32 	%r805, %r804, %r1422;
	add.s32 	%r1422, %r805, 939524096;
$L__BB27_569:
	mul.rn.f32 	%r1435, %r1414, %r262;
	@%p677 bra 	$L__BB27_592;
	cvt.f64.f32 	%rd171, %r1435;
	shr.u64 	%rd173, %rd171, 48;
	cvt.u32.u64 	%r806, %rd173;
	and.b32 	%r274, %r806, 32768;
	shr.u64 	%rd511, %rd171, 52;
	cvt.u32.u64 	%r807, %rd511;
	and.b32 	%r275, %r807, 2047;
	setp.eq.b32 	%p315, %r275, 0;
	@%p315 bra 	$L__BB27_573;
	and.b64 	%rd172, %rd171, 4503599627370495;
	setp.eq.b32 	%p314, %r1396, 12;
	selp.b32 	%r276, 11, 8, %p314;
	selp.b32 	%r278, 31744, 32640, %p314;
	setp.ne.b32 	%p316, %r275, 2047;
	@%p316 bra 	$L__BB27_574;
	setp.eq.b64 	%p317, %rd172, 0;
	add.s32 	%r808, %r276, -2;
	mov.b32 	%r809, 1;
	shl.b32 	%r810, %r809, %r808;
	selp.b32 	%r811, 0, %r810, %p317;
	or.b32 	%r812, %r811, %r278;
	or.b32 	%r813, %r812, %r274;
	cvt.u16.u32 	%rs25, %r813;
	bra.uni 	$L__BB27_584;
$L__BB27_573:
	cvt.u16.u32 	%rs25, %r274;
	bra.uni 	$L__BB27_584;
$L__BB27_574:
	selp.b32 	%r814, -14, -126, %p314;
	add.s32 	%r279, %r275, -1023;
	or.b64 	%rd174, %rd172, 4503599627370496;
	setp.ge.s32 	%p318, %r279, %r814;
	@%p318 bra 	$L__BB27_580;
	and.b64 	%rd175, %rd173, 32768;
	selp.b32 	%r824, 28, -81, %p314;
	sub.s32 	%r280, %r824, %r279;
	setp.gt.s32 	%p326, %r280, 0;
	@%p326 bra 	$L__BB27_577;
	bra.uni 	$L__BB27_576;
$L__BB27_577:
	setp.gt.u32 	%p327, %r280, 63;
	mov.b64 	%rd906, 0;
	@%p327 bra 	$L__BB27_579;
	shr.u64 	%rd525, %rd174, %r280;
	mov.b64 	%rd526, -1;
	shl.b64 	%rd527, %rd526, %r280;
	not.b64 	%rd528, %rd527;
	and.b64 	%rd529, %rd174, %rd528;
	add.s32 	%r825, %r280, -1;
	mov.b64 	%rd530, 1;
	shl.b64 	%rd531, %rd530, %r825;
	setp.gt.u64 	%p328, %rd529, %rd531;
	setp.eq.b64 	%p329, %rd529, %rd531;
	and.b64 	%rd532, %rd525, 1;
	setp.ne.b64 	%p330, %rd532, 0;
	and.pred 	%p331, %p329, %p330;
	or.pred 	%p332, %p328, %p331;
	selp.b64 	%rd533, 1, 0, %p332;
	add.s64 	%rd906, %rd525, %rd533;
	bra.uni 	$L__BB27_579;
$L__BB27_580:
	selp.b32 	%r277, 15, 127, %p314;
	sub.s32 	%r815, 53, %r276;
	shr.u64 	%rd512, %rd174, %r815;
	mov.b64 	%rd513, -1;
	shl.b64 	%rd514, %rd513, %r815;
	not.b64 	%rd515, %rd514;
	and.b64 	%rd516, %rd171, %rd515;
	sub.s32 	%r816, 52, %r276;
	mov.b64 	%rd517, 1;
	shl.b64 	%rd518, %rd517, %r816;
	setp.gt.u64 	%p319, %rd516, %rd518;
	setp.eq.b64 	%p320, %rd516, %rd518;
	and.b64 	%rd519, %rd512, 1;
	setp.ne.b64 	%p321, %rd519, 0;
	and.pred 	%p322, %p320, %p321;
	or.pred 	%p323, %p319, %p322;
	selp.b64 	%rd520, 1, 0, %p323;
	add.s64 	%rd176, %rd512, %rd520;
	shl.b64 	%rd177, %rd517, %r276;
	setp.eq.b64 	%p324, %rd176, %rd177;
	add.s32 	%r817, %r275, -1022;
	selp.b32 	%r281, %r817, %r279, %p324;
	setp.le.s32 	%p325, %r281, %r277;
	@%p325 bra 	$L__BB27_582;
	or.b32 	%r1434, %r274, %r278;
	bra.uni 	$L__BB27_583;
$L__BB27_582:
	selp.b32 	%r818, 1, 0, %p324;
	shr.u64 	%rd521, %rd176, %r818;
	add.s32 	%r819, %r281, %r277;
	add.s32 	%r820, %r276, -1;
	shl.b32 	%r821, %r819, %r820;
	shl.b64 	%rd522, %rd513, %r820;
	not.b64 	%rd523, %rd522;
	and.b64 	%rd524, %rd521, %rd523;
	cvt.u32.u64 	%r822, %rd524;
	or.b32 	%r823, %r821, %r822;
	or.b32 	%r1434, %r823, %r274;
$L__BB27_583:
	cvt.u16.u32 	%rs25, %r1434;
	bra.uni 	$L__BB27_584;
$L__BB27_391:
	neg.s32 	%r530, %r190;
	shl.b64 	%rd898, %rd118, %r530;
$L__BB27_394:
	or.b64 	%rd342, %rd898, %rd119;
	cvt.u16.u64 	%rs17, %rd342;
$L__BB27_399:
	setp.ne.b32 	%p149, %r1396, 13;
	cvt.u32.u16 	%r192, %rs17;
	@%p149 bra 	$L__BB27_401;
	shl.b32 	%r1422, %r192, 16;
	bra.uni 	$L__BB27_407;
$L__BB27_401:
	cvt.s32.s16 	%r531, %rs17;
	and.b32 	%r1422, %r531, -2147483648;
	bfe.u32 	%r193, %r192, 10, 5;
	setp.eq.b32 	%p150, %r193, 31;
	@%p150 bra 	$L__BB27_405;
	and.b32 	%r194, %r192, 1023;
	setp.ne.b32 	%p151, %r193, 0;
	@%p151 bra 	$L__BB27_406;
	setp.eq.b32 	%p152, %r194, 0;
	@%p152 bra 	$L__BB27_407;
	clz.b32 	%r534, %r194;
	xor.b32 	%r535, %r534, 31;
	sub.s32 	%r536, 9, %r535;
	shl.b32 	%r537, %r192, %r536;
	shl.b32 	%r538, %r535, 23;
	shl.b32 	%r539, %r537, 14;
	and.b32 	%r540, %r539, 8372224;
	add.s32 	%r541, %r538, %r1422;
	add.s32 	%r542, %r541, %r540;
	add.s32 	%r1422, %r542, 864026624;
	bra.uni 	$L__BB27_407;
$L__BB27_405:
	shl.b32 	%r532, %r192, 13;
	or.b32 	%r533, %r1422, %r532;
	or.b32 	%r1422, %r533, 2139095040;
	bra.uni 	$L__BB27_407;
$L__BB27_406:
	shl.b32 	%r543, %r193, 23;
	shl.b32 	%r544, %r194, 13;
	or.b32 	%r545, %r543, %r544;
	add.s32 	%r546, %r545, %r1422;
	add.s32 	%r1422, %r546, 939524096;
$L__BB27_407:
	mul.rn.f32 	%r1424, %r1414, %r171;
	@%p677 bra 	$L__BB27_430;
	cvt.f64.f32 	%rd122, %r1424;
	shr.u64 	%rd124, %rd122, 48;
	cvt.u32.u64 	%r547, %rd124;
	and.b32 	%r195, %r547, 32768;
	shr.u64 	%rd343, %rd122, 52;
	cvt.u32.u64 	%r548, %rd343;
	and.b32 	%r196, %r548, 2047;
	setp.eq.b32 	%p154, %r196, 0;
	@%p154 bra 	$L__BB27_411;
	and.b64 	%rd123, %rd122, 4503599627370495;
	setp.eq.b32 	%p153, %r1396, 12;
	selp.b32 	%r197, 11, 8, %p153;
	selp.b32 	%r199, 31744, 32640, %p153;
	setp.ne.b32 	%p155, %r196, 2047;
	@%p155 bra 	$L__BB27_412;
	setp.eq.b64 	%p156, %rd123, 0;
	add.s32 	%r549, %r197, -2;
	mov.b32 	%r550, 1;
	shl.b32 	%r551, %r550, %r549;
	selp.b32 	%r552, 0, %r551, %p156;
	or.b32 	%r553, %r552, %r199;
	or.b32 	%r554, %r553, %r195;
	cvt.u16.u32 	%rs18, %r554;
	bra.uni 	$L__BB27_422;
$L__BB27_411:
	cvt.u16.u32 	%rs18, %r195;
	bra.uni 	$L__BB27_422;
$L__BB27_412:
	selp.b32 	%r555, -14, -126, %p153;
	add.s32 	%r200, %r196, -1023;
	or.b64 	%rd125, %rd123, 4503599627370496;
	setp.ge.s32 	%p157, %r200, %r555;
	@%p157 bra 	$L__BB27_418;
	and.b64 	%rd126, %rd124, 32768;
	selp.b32 	%r565, 28, -81, %p153;
)QPTX";
        result += R"QPTX(
	sub.s32 	%r201, %r565, %r200;
	setp.gt.s32 	%p165, %r201, 0;
	@%p165 bra 	$L__BB27_415;
	bra.uni 	$L__BB27_414;
$L__BB27_415:
	setp.gt.u32 	%p166, %r201, 63;
	mov.b64 	%rd899, 0;
	@%p166 bra 	$L__BB27_417;
	shr.u64 	%rd357, %rd125, %r201;
	mov.b64 	%rd358, -1;
	shl.b64 	%rd359, %rd358, %r201;
	not.b64 	%rd360, %rd359;
	and.b64 	%rd361, %rd125, %rd360;
	add.s32 	%r566, %r201, -1;
	mov.b64 	%rd362, 1;
	shl.b64 	%rd363, %rd362, %r566;
	setp.gt.u64 	%p167, %rd361, %rd363;
	setp.eq.b64 	%p168, %rd361, %rd363;
	and.b64 	%rd364, %rd357, 1;
	setp.ne.b64 	%p169, %rd364, 0;
	and.pred 	%p170, %p168, %p169;
	or.pred 	%p171, %p167, %p170;
	selp.b64 	%rd365, 1, 0, %p171;
	add.s64 	%rd899, %rd357, %rd365;
	bra.uni 	$L__BB27_417;
$L__BB27_418:
	selp.b32 	%r198, 15, 127, %p153;
	sub.s32 	%r556, 53, %r197;
	shr.u64 	%rd344, %rd125, %r556;
	mov.b64 	%rd345, -1;
	shl.b64 	%rd346, %rd345, %r556;
	not.b64 	%rd347, %rd346;
	and.b64 	%rd348, %rd122, %rd347;
	sub.s32 	%r557, 52, %r197;
	mov.b64 	%rd349, 1;
	shl.b64 	%rd350, %rd349, %r557;
	setp.gt.u64 	%p158, %rd348, %rd350;
	setp.eq.b64 	%p159, %rd348, %rd350;
	and.b64 	%rd351, %rd344, 1;
	setp.ne.b64 	%p160, %rd351, 0;
	and.pred 	%p161, %p159, %p160;
	or.pred 	%p162, %p158, %p161;
	selp.b64 	%rd352, 1, 0, %p162;
	add.s64 	%rd127, %rd344, %rd352;
	shl.b64 	%rd128, %rd349, %r197;
	setp.eq.b64 	%p163, %rd127, %rd128;
	add.s32 	%r558, %r196, -1022;
	selp.b32 	%r202, %r558, %r200, %p163;
	setp.le.s32 	%p164, %r202, %r198;
	@%p164 bra 	$L__BB27_420;
	or.b32 	%r1423, %r195, %r199;
	bra.uni 	$L__BB27_421;
$L__BB27_420:
	selp.b32 	%r559, 1, 0, %p163;
	shr.u64 	%rd353, %rd127, %r559;
	add.s32 	%r560, %r202, %r198;
	add.s32 	%r561, %r197, -1;
	shl.b32 	%r562, %r560, %r561;
	shl.b64 	%rd354, %rd345, %r561;
	not.b64 	%rd355, %rd354;
	and.b64 	%rd356, %rd353, %rd355;
	cvt.u32.u64 	%r563, %rd356;
	or.b32 	%r564, %r562, %r563;
	or.b32 	%r1423, %r564, %r195;
$L__BB27_421:
	cvt.u16.u32 	%rs18, %r1423;
	bra.uni 	$L__BB27_422;
$L__BB27_576:
	neg.s32 	%r826, %r280;
	shl.b64 	%rd906, %rd174, %r826;
$L__BB27_579:
	or.b64 	%rd534, %rd906, %rd175;
	cvt.u16.u64 	%rs25, %rd534;
$L__BB27_584:
	setp.ne.b32 	%p333, %r1396, 13;
	cvt.u32.u16 	%r282, %rs25;
	@%p333 bra 	$L__BB27_586;
	shl.b32 	%r1435, %r282, 16;
	bra.uni 	$L__BB27_592;
$L__BB27_586:
	cvt.s32.s16 	%r827, %rs25;
	and.b32 	%r1435, %r827, -2147483648;
	bfe.u32 	%r283, %r282, 10, 5;
	setp.eq.b32 	%p334, %r283, 31;
	@%p334 bra 	$L__BB27_590;
	and.b32 	%r284, %r282, 1023;
	setp.ne.b32 	%p335, %r283, 0;
	@%p335 bra 	$L__BB27_591;
	setp.eq.b32 	%p336, %r284, 0;
	@%p336 bra 	$L__BB27_592;
	clz.b32 	%r830, %r284;
	xor.b32 	%r831, %r830, 31;
	sub.s32 	%r832, 9, %r831;
	shl.b32 	%r833, %r282, %r832;
	shl.b32 	%r834, %r831, 23;
	shl.b32 	%r835, %r833, 14;
	and.b32 	%r836, %r835, 8372224;
	add.s32 	%r837, %r834, %r1435;
	add.s32 	%r838, %r837, %r836;
	add.s32 	%r1435, %r838, 864026624;
	bra.uni 	$L__BB27_592;
$L__BB27_590:
	shl.b32 	%r828, %r282, 13;
	or.b32 	%r829, %r1435, %r828;
	or.b32 	%r1435, %r829, 2139095040;
	bra.uni 	$L__BB27_592;
$L__BB27_591:
	shl.b32 	%r839, %r283, 23;
	shl.b32 	%r840, %r284, 13;
	or.b32 	%r841, %r839, %r840;
	add.s32 	%r842, %r841, %r1435;
	add.s32 	%r1435, %r842, 939524096;
$L__BB27_592:
	sub.rn.f32 	%r1426, %r1435, %r250;
	mov.pred 	%p678, 0;
	@%p677 bra 	$L__BB27_616;
	cvt.f64.f32 	%rd178, %r1426;
	shr.u64 	%rd180, %rd178, 48;
	cvt.u32.u64 	%r843, %rd180;
	and.b32 	%r285, %r843, 32768;
	shr.u64 	%rd535, %rd178, 52;
	cvt.u32.u64 	%r844, %rd535;
	and.b32 	%r286, %r844, 2047;
	setp.eq.b32 	%p338, %r286, 0;
	@%p338 bra 	$L__BB27_596;
	and.b64 	%rd179, %rd178, 4503599627370495;
	setp.eq.b32 	%p337, %r1396, 12;
	selp.b32 	%r287, 11, 8, %p337;
	selp.b32 	%r289, 31744, 32640, %p337;
	setp.ne.b32 	%p339, %r286, 2047;
	@%p339 bra 	$L__BB27_597;
	setp.eq.b64 	%p340, %rd179, 0;
	add.s32 	%r845, %r287, -2;
	mov.b32 	%r846, 1;
	shl.b32 	%r847, %r846, %r845;
	selp.b32 	%r848, 0, %r847, %p340;
	or.b32 	%r849, %r848, %r289;
	or.b32 	%r850, %r849, %r285;
	cvt.u16.u32 	%rs26, %r850;
	bra.uni 	$L__BB27_607;
$L__BB27_596:
	cvt.u16.u32 	%rs26, %r285;
	bra.uni 	$L__BB27_607;
$L__BB27_597:
	selp.b32 	%r851, -14, -126, %p337;
	add.s32 	%r290, %r286, -1023;
	or.b64 	%rd181, %rd179, 4503599627370496;
	setp.ge.s32 	%p341, %r290, %r851;
	@%p341 bra 	$L__BB27_603;
	and.b64 	%rd182, %rd180, 32768;
	selp.b32 	%r861, 28, -81, %p337;
	sub.s32 	%r291, %r861, %r290;
	setp.gt.s32 	%p349, %r291, 0;
	@%p349 bra 	$L__BB27_600;
	bra.uni 	$L__BB27_599;
$L__BB27_600:
	setp.gt.u32 	%p350, %r291, 63;
	mov.b64 	%rd907, 0;
	@%p350 bra 	$L__BB27_602;
	shr.u64 	%rd549, %rd181, %r291;
	mov.b64 	%rd550, -1;
	shl.b64 	%rd551, %rd550, %r291;
	not.b64 	%rd552, %rd551;
	and.b64 	%rd553, %rd181, %rd552;
	add.s32 	%r862, %r291, -1;
	mov.b64 	%rd554, 1;
	shl.b64 	%rd555, %rd554, %r862;
	setp.gt.u64 	%p351, %rd553, %rd555;
	setp.eq.b64 	%p352, %rd553, %rd555;
	and.b64 	%rd556, %rd549, 1;
	setp.ne.b64 	%p353, %rd556, 0;
	and.pred 	%p354, %p352, %p353;
	or.pred 	%p355, %p351, %p354;
	selp.b64 	%rd557, 1, 0, %p355;
	add.s64 	%rd907, %rd549, %rd557;
	bra.uni 	$L__BB27_602;
$L__BB27_603:
	selp.b32 	%r288, 15, 127, %p337;
	sub.s32 	%r852, 53, %r287;
	shr.u64 	%rd536, %rd181, %r852;
	mov.b64 	%rd537, -1;
	shl.b64 	%rd538, %rd537, %r852;
	not.b64 	%rd539, %rd538;
	and.b64 	%rd540, %rd178, %rd539;
	sub.s32 	%r853, 52, %r287;
	mov.b64 	%rd541, 1;
	shl.b64 	%rd542, %rd541, %r853;
	setp.gt.u64 	%p342, %rd540, %rd542;
	setp.eq.b64 	%p343, %rd540, %rd542;
	and.b64 	%rd543, %rd536, 1;
	setp.ne.b64 	%p344, %rd543, 0;
	and.pred 	%p345, %p343, %p344;
	or.pred 	%p346, %p342, %p345;
	selp.b64 	%rd544, 1, 0, %p346;
	add.s64 	%rd183, %rd536, %rd544;
	shl.b64 	%rd184, %rd541, %r287;
	setp.eq.b64 	%p347, %rd183, %rd184;
	add.s32 	%r854, %r286, -1022;
	selp.b32 	%r292, %r854, %r290, %p347;
	setp.le.s32 	%p348, %r292, %r288;
	@%p348 bra 	$L__BB27_605;
	or.b32 	%r1436, %r285, %r289;
	bra.uni 	$L__BB27_606;
$L__BB27_605:
	selp.b32 	%r855, 1, 0, %p347;
	shr.u64 	%rd545, %rd183, %r855;
	add.s32 	%r856, %r292, %r288;
	add.s32 	%r857, %r287, -1;
	shl.b32 	%r858, %r856, %r857;
	shl.b64 	%rd546, %rd537, %r857;
	not.b64 	%rd547, %rd546;
	and.b64 	%rd548, %rd545, %rd547;
	cvt.u32.u64 	%r859, %rd548;
	or.b32 	%r860, %r858, %r859;
	or.b32 	%r1436, %r860, %r285;
$L__BB27_606:
	cvt.u16.u32 	%rs26, %r1436;
	bra.uni 	$L__BB27_607;
$L__BB27_414:
	neg.s32 	%r567, %r201;
	shl.b64 	%rd899, %rd125, %r567;
$L__BB27_417:
	or.b64 	%rd366, %rd899, %rd126;
	cvt.u16.u64 	%rs18, %rd366;
$L__BB27_422:
	setp.ne.b32 	%p172, %r1396, 13;
	cvt.u32.u16 	%r203, %rs18;
	@%p172 bra 	$L__BB27_424;
	shl.b32 	%r1424, %r203, 16;
	bra.uni 	$L__BB27_430;
$L__BB27_424:
	cvt.s32.s16 	%r568, %rs18;
	and.b32 	%r1424, %r568, -2147483648;
	bfe.u32 	%r204, %r203, 10, 5;
	setp.eq.b32 	%p173, %r204, 31;
	@%p173 bra 	$L__BB27_428;
	and.b32 	%r205, %r203, 1023;
	setp.ne.b32 	%p174, %r204, 0;
	@%p174 bra 	$L__BB27_429;
	setp.eq.b32 	%p175, %r205, 0;
	@%p175 bra 	$L__BB27_430;
	clz.b32 	%r571, %r205;
	xor.b32 	%r572, %r571, 31;
	sub.s32 	%r573, 9, %r572;
	shl.b32 	%r574, %r203, %r573;
	shl.b32 	%r575, %r572, 23;
	shl.b32 	%r576, %r574, 14;
	and.b32 	%r577, %r576, 8372224;
	add.s32 	%r578, %r575, %r1424;
	add.s32 	%r579, %r578, %r577;
	add.s32 	%r1424, %r579, 864026624;
	bra.uni 	$L__BB27_430;
$L__BB27_428:
	shl.b32 	%r569, %r203, 13;
	or.b32 	%r570, %r1424, %r569;
	or.b32 	%r1424, %r570, 2139095040;
	bra.uni 	$L__BB27_430;
$L__BB27_429:
	shl.b32 	%r580, %r204, 23;
	shl.b32 	%r581, %r205, 13;
	or.b32 	%r582, %r580, %r581;
	add.s32 	%r583, %r582, %r1424;
	add.s32 	%r1424, %r583, 939524096;
$L__BB27_430:
	sub.rn.f32 	%r1426, %r172, %r1424;
	mov.pred 	%p678, 0;
	@%p677 bra 	$L__BB27_616;
	cvt.f64.f32 	%rd129, %r1426;
	shr.u64 	%rd131, %rd129, 48;
	cvt.u32.u64 	%r584, %rd131;
	and.b32 	%r206, %r584, 32768;
	shr.u64 	%rd367, %rd129, 52;
	cvt.u32.u64 	%r585, %rd367;
	and.b32 	%r207, %r585, 2047;
	setp.eq.b32 	%p177, %r207, 0;
	@%p177 bra 	$L__BB27_434;
	and.b64 	%rd130, %rd129, 4503599627370495;
	setp.eq.b32 	%p176, %r1396, 12;
	selp.b32 	%r208, 11, 8, %p176;
	selp.b32 	%r210, 31744, 32640, %p176;
	setp.ne.b32 	%p178, %r207, 2047;
	@%p178 bra 	$L__BB27_435;
	setp.eq.b64 	%p179, %rd130, 0;
	add.s32 	%r586, %r208, -2;
	mov.b32 	%r587, 1;
	shl.b32 	%r588, %r587, %r586;
	selp.b32 	%r589, 0, %r588, %p179;
	or.b32 	%r590, %r589, %r210;
	or.b32 	%r591, %r590, %r206;
	cvt.u16.u32 	%rs19, %r591;
	bra.uni 	$L__BB27_445;
$L__BB27_434:
	cvt.u16.u32 	%rs19, %r206;
	bra.uni 	$L__BB27_445;
$L__BB27_435:
	selp.b32 	%r592, -14, -126, %p176;
	add.s32 	%r211, %r207, -1023;
	or.b64 	%rd132, %rd130, 4503599627370496;
	setp.ge.s32 	%p180, %r211, %r592;
	@%p180 bra 	$L__BB27_441;
	and.b64 	%rd133, %rd131, 32768;
	selp.b32 	%r602, 28, -81, %p176;
	sub.s32 	%r212, %r602, %r211;
	setp.gt.s32 	%p188, %r212, 0;
	@%p188 bra 	$L__BB27_438;
	bra.uni 	$L__BB27_437;
$L__BB27_438:
	setp.gt.u32 	%p189, %r212, 63;
	mov.b64 	%rd900, 0;
	@%p189 bra 	$L__BB27_440;
	shr.u64 	%rd381, %rd132, %r212;
	mov.b64 	%rd382, -1;
	shl.b64 	%rd383, %rd382, %r212;
	not.b64 	%rd384, %rd383;
	and.b64 	%rd385, %rd132, %rd384;
	add.s32 	%r603, %r212, -1;
	mov.b64 	%rd386, 1;
	shl.b64 	%rd387, %rd386, %r603;
	setp.gt.u64 	%p190, %rd385, %rd387;
	setp.eq.b64 	%p191, %rd385, %rd387;
	and.b64 	%rd388, %rd381, 1;
	setp.ne.b64 	%p192, %rd388, 0;
	and.pred 	%p193, %p191, %p192;
	or.pred 	%p194, %p190, %p193;
	selp.b64 	%rd389, 1, 0, %p194;
	add.s64 	%rd900, %rd381, %rd389;
	bra.uni 	$L__BB27_440;
$L__BB27_441:
	selp.b32 	%r209, 15, 127, %p176;
	sub.s32 	%r593, 53, %r208;
	shr.u64 	%rd368, %rd132, %r593;
	mov.b64 	%rd369, -1;
	shl.b64 	%rd370, %rd369, %r593;
	not.b64 	%rd371, %rd370;
	and.b64 	%rd372, %rd129, %rd371;
	sub.s32 	%r594, 52, %r208;
	mov.b64 	%rd373, 1;
	shl.b64 	%rd374, %rd373, %r594;
	setp.gt.u64 	%p181, %rd372, %rd374;
	setp.eq.b64 	%p182, %rd372, %rd374;
	and.b64 	%rd375, %rd368, 1;
	setp.ne.b64 	%p183, %rd375, 0;
	and.pred 	%p184, %p182, %p183;
	or.pred 	%p185, %p181, %p184;
	selp.b64 	%rd376, 1, 0, %p185;
	add.s64 	%rd134, %rd368, %rd376;
	shl.b64 	%rd135, %rd373, %r208;
	setp.eq.b64 	%p186, %rd134, %rd135;
	add.s32 	%r595, %r207, -1022;
	selp.b32 	%r213, %r595, %r211, %p186;
	setp.le.s32 	%p187, %r213, %r209;
	@%p187 bra 	$L__BB27_443;
	or.b32 	%r1425, %r206, %r210;
	bra.uni 	$L__BB27_444;
$L__BB27_443:
	selp.b32 	%r596, 1, 0, %p186;
	shr.u64 	%rd377, %rd134, %r596;
	add.s32 	%r597, %r213, %r209;
	add.s32 	%r598, %r208, -1;
	shl.b32 	%r599, %r597, %r598;
	shl.b64 	%rd378, %rd369, %r598;
	not.b64 	%rd379, %rd378;
	and.b64 	%rd380, %rd377, %rd379;
	cvt.u32.u64 	%r600, %rd380;
	or.b32 	%r601, %r599, %r600;
	or.b32 	%r1425, %r601, %r206;
$L__BB27_444:
	cvt.u16.u32 	%rs19, %r1425;
	bra.uni 	$L__BB27_445;
$L__BB27_599:
	neg.s32 	%r863, %r291;
	shl.b64 	%rd907, %rd181, %r863;
$L__BB27_602:
	or.b64 	%rd558, %rd907, %rd182;
	cvt.u16.u64 	%rs26, %rd558;
$L__BB27_607:
	setp.ne.b32 	%p356, %r1396, 13;
	cvt.u32.u16 	%r293, %rs26;
	@%p356 bra 	$L__BB27_609;
	shl.b32 	%r1426, %r293, 16;
	bra.uni 	$L__BB27_615;
$L__BB27_609:
	cvt.s32.s16 	%r864, %rs26;
	and.b32 	%r1426, %r864, -2147483648;
	bfe.u32 	%r294, %r293, 10, 5;
	setp.eq.b32 	%p357, %r294, 31;
	@%p357 bra 	$L__BB27_613;
	and.b32 	%r295, %r293, 1023;
	setp.ne.b32 	%p358, %r294, 0;
	@%p358 bra 	$L__BB27_614;
	setp.eq.b32 	%p359, %r295, 0;
	@%p359 bra 	$L__BB27_615;
	clz.b32 	%r867, %r295;
	xor.b32 	%r868, %r867, 31;
	sub.s32 	%r869, 9, %r868;
	shl.b32 	%r870, %r293, %r869;
	shl.b32 	%r871, %r868, 23;
	shl.b32 	%r872, %r870, 14;
	and.b32 	%r873, %r872, 8372224;
	add.s32 	%r874, %r871, %r1426;
	add.s32 	%r875, %r874, %r873;
	add.s32 	%r1426, %r875, 864026624;
	bra.uni 	$L__BB27_615;
$L__BB27_613:
	shl.b32 	%r865, %r293, 13;
	or.b32 	%r866, %r1426, %r865;
	or.b32 	%r1426, %r866, 2139095040;
	bra.uni 	$L__BB27_615;
$L__BB27_614:
	shl.b32 	%r876, %r294, 23;
	shl.b32 	%r877, %r295, 13;
	or.b32 	%r878, %r876, %r877;
	add.s32 	%r879, %r878, %r1426;
	add.s32 	%r1426, %r879, 939524096;
$L__BB27_615:
	mov.pred 	%p678, -1;
	bra.uni 	$L__BB27_616;
$L__BB27_437:
	neg.s32 	%r604, %r212;
	shl.b64 	%rd900, %rd132, %r604;
$L__BB27_440:
	or.b64 	%rd390, %rd900, %rd133;
	cvt.u16.u64 	%rs19, %rd390;
$L__BB27_445:
	setp.ne.b32 	%p195, %r1396, 13;
	cvt.u32.u16 	%r214, %rs19;
	@%p195 bra 	$L__BB27_447;
	shl.b32 	%r1426, %r214, 16;
	bra.uni 	$L__BB27_453;
$L__BB27_447:
	cvt.s32.s16 	%r605, %rs19;
	and.b32 	%r1426, %r605, -2147483648;
	bfe.u32 	%r215, %r214, 10, 5;
	setp.eq.b32 	%p196, %r215, 31;
	@%p196 bra 	$L__BB27_451;
	and.b32 	%r216, %r214, 1023;
	setp.ne.b32 	%p197, %r215, 0;
	@%p197 bra 	$L__BB27_452;
	setp.eq.b32 	%p198, %r216, 0;
	@%p198 bra 	$L__BB27_453;
	clz.b32 	%r608, %r216;
	xor.b32 	%r609, %r608, 31;
	sub.s32 	%r610, 9, %r609;
	shl.b32 	%r611, %r214, %r610;
	shl.b32 	%r612, %r609, 23;
	shl.b32 	%r613, %r611, 14;
	and.b32 	%r614, %r613, 8372224;
	add.s32 	%r615, %r612, %r1426;
	add.s32 	%r616, %r615, %r614;
	add.s32 	%r1426, %r616, 864026624;
	bra.uni 	$L__BB27_453;
$L__BB27_451:
	shl.b32 	%r606, %r214, 13;
	or.b32 	%r607, %r1426, %r606;
	or.b32 	%r1426, %r607, 2139095040;
	bra.uni 	$L__BB27_453;
$L__BB27_452:
	shl.b32 	%r617, %r215, 23;
	shl.b32 	%r618, %r216, 13;
	or.b32 	%r619, %r617, %r618;
	add.s32 	%r620, %r619, %r1426;
	add.s32 	%r1426, %r620, 939524096;
$L__BB27_453:
	mov.pred 	%p678, -1;
$L__BB27_616:
	abs.f32 	%r880, %r1414;
	setp.ne.f32 	%p360, %r880, 0f7F800000;
	abs.f32 	%r881, %r1418;
	setp.ne.f32 	%p361, %r881, 0f7F800000;
	and.pred 	%p362, %p360, %p361;
	abs.f32 	%r882, %r1422;
	setp.ne.f32 	%p363, %r882, 0f7F800000;
	and.pred 	%p364, %p362, %p363;
	abs.f32 	%r883, %r1426;
	setp.ne.f32 	%p365, %r883, 0f7F800000;
	div.rn.f32 	%r1440, %r1422, %r1418;
	not.pred 	%p366, %p678;
	@%p366 bra 	$L__BB27_639;
	cvt.f64.f32 	%rd185, %r1440;
	shr.u64 	%rd187, %rd185, 48;
	cvt.u32.u64 	%r884, %rd187;
	and.b32 	%r296, %r884, 32768;
	shr.u64 	%rd559, %rd185, 52;
	cvt.u32.u64 	%r885, %rd559;
	and.b32 	%r297, %r885, 2047;
	setp.eq.b32 	%p368, %r297, 0;
	@%p368 bra 	$L__BB27_620;
	and.b64 	%rd186, %rd185, 4503599627370495;
	setp.eq.b32 	%p367, %r1396, 12;
	selp.b32 	%r298, 11, 8, %p367;
	selp.b32 	%r300, 31744, 32640, %p367;
	setp.ne.b32 	%p369, %r297, 2047;
	@%p369 bra 	$L__BB27_621;
	setp.eq.b64 	%p370, %rd186, 0;
	add.s32 	%r886, %r298, -2;
	mov.b32 	%r887, 1;
	shl.b32 	%r888, %r887, %r886;
	selp.b32 	%r889, 0, %r888, %p370;
	or.b32 	%r890, %r889, %r300;
	or.b32 	%r891, %r890, %r296;
	cvt.u16.u32 	%rs27, %r891;
	bra.uni 	$L__BB27_631;
$L__BB27_620:
	cvt.u16.u32 	%rs27, %r296;
	bra.uni 	$L__BB27_631;
$L__BB27_621:
	selp.b32 	%r892, -14, -126, %p367;
	add.s32 	%r301, %r297, -1023;
	or.b64 	%rd188, %rd186, 4503599627370496;
	setp.ge.s32 	%p371, %r301, %r892;
	@%p371 bra 	$L__BB27_627;
	and.b64 	%rd189, %rd187, 32768;
	selp.b32 	%r902, 28, -81, %p367;
	sub.s32 	%r302, %r902, %r301;
	setp.gt.s32 	%p379, %r302, 0;
	@%p379 bra 	$L__BB27_624;
	bra.uni 	$L__BB27_623;
$L__BB27_624:
	setp.gt.u32 	%p380, %r302, 63;
	mov.b64 	%rd908, 0;
	@%p380 bra 	$L__BB27_626;
	shr.u64 	%rd573, %rd188, %r302;
	mov.b64 	%rd574, -1;
	shl.b64 	%rd575, %rd574, %r302;
	not.b64 	%rd576, %rd575;
	and.b64 	%rd577, %rd188, %rd576;
	add.s32 	%r903, %r302, -1;
	mov.b64 	%rd578, 1;
	shl.b64 	%rd579, %rd578, %r903;
	setp.gt.u64 	%p381, %rd577, %rd579;
	setp.eq.b64 	%p382, %rd577, %rd579;
	and.b64 	%rd580, %rd573, 1;
	setp.ne.b64 	%p383, %rd580, 0;
	and.pred 	%p384, %p382, %p383;
	or.pred 	%p385, %p381, %p384;
	selp.b64 	%rd581, 1, 0, %p385;
	add.s64 	%rd908, %rd573, %rd581;
	bra.uni 	$L__BB27_626;
$L__BB27_627:
	selp.b32 	%r299, 15, 127, %p367;
	sub.s32 	%r893, 53, %r298;
	shr.u64 	%rd560, %rd188, %r893;
	mov.b64 	%rd561, -1;
	shl.b64 	%rd562, %rd561, %r893;
	not.b64 	%rd563, %rd562;
	and.b64 	%rd564, %rd185, %rd563;
	sub.s32 	%r894, 52, %r298;
	mov.b64 	%rd565, 1;
	shl.b64 	%rd566, %rd565, %r894;
	setp.gt.u64 	%p372, %rd564, %rd566;
	setp.eq.b64 	%p373, %rd564, %rd566;
	and.b64 	%rd567, %rd560, 1;
	setp.ne.b64 	%p374, %rd567, 0;
	and.pred 	%p375, %p373, %p374;
	or.pred 	%p376, %p372, %p375;
	selp.b64 	%rd568, 1, 0, %p376;
	add.s64 	%rd190, %rd560, %rd568;
	shl.b64 	%rd191, %rd565, %r298;
	setp.eq.b64 	%p377, %rd190, %rd191;
	add.s32 	%r895, %r297, -1022;
	selp.b32 	%r303, %r895, %r301, %p377;
	setp.le.s32 	%p378, %r303, %r299;
	@%p378 bra 	$L__BB27_629;
	or.b32 	%r1437, %r296, %r300;
	bra.uni 	$L__BB27_630;
$L__BB27_629:
	selp.b32 	%r896, 1, 0, %p377;
	shr.u64 	%rd569, %rd190, %r896;
	add.s32 	%r897, %r303, %r299;
	add.s32 	%r898, %r298, -1;
	shl.b32 	%r899, %r897, %r898;
	shl.b64 	%rd570, %rd561, %r898;
	not.b64 	%rd571, %rd570;
	and.b64 	%rd572, %rd569, %rd571;
	cvt.u32.u64 	%r900, %rd572;
	or.b32 	%r901, %r899, %r900;
	or.b32 	%r1437, %r901, %r296;
$L__BB27_630:
	cvt.u16.u32 	%rs27, %r1437;
	bra.uni 	$L__BB27_631;
$L__BB27_623:
	neg.s32 	%r904, %r302;
	shl.b64 	%rd908, %rd188, %r904;
$L__BB27_626:
	or.b64 	%rd582, %rd908, %rd189;
	cvt.u16.u64 	%rs27, %rd582;
$L__BB27_631:
	setp.ne.b32 	%p386, %r1396, 13;
	cvt.u32.u16 	%r304, %rs27;
	@%p386 bra 	$L__BB27_633;
	shl.b32 	%r1440, %r304, 16;
	bra.uni 	$L__BB27_639;
$L__BB27_633:
	cvt.s32.s16 	%r905, %rs27;
	and.b32 	%r1440, %r905, -2147483648;
	bfe.u32 	%r305, %r304, 10, 5;
	setp.eq.b32 	%p387, %r305, 31;
	@%p387 bra 	$L__BB27_637;
	and.b32 	%r306, %r304, 1023;
	setp.ne.b32 	%p388, %r305, 0;
	@%p388 bra 	$L__BB27_638;
	setp.eq.b32 	%p389, %r306, 0;
	@%p389 bra 	$L__BB27_639;
	clz.b32 	%r908, %r306;
	xor.b32 	%r909, %r908, 31;
	sub.s32 	%r910, 9, %r909;
	shl.b32 	%r911, %r304, %r910;
	shl.b32 	%r912, %r909, 23;
	shl.b32 	%r913, %r911, 14;
	and.b32 	%r914, %r913, 8372224;
	add.s32 	%r915, %r912, %r1440;
	add.s32 	%r916, %r915, %r914;
	add.s32 	%r1440, %r916, 864026624;
	bra.uni 	$L__BB27_639;
$L__BB27_637:
	shl.b32 	%r906, %r304, 13;
	or.b32 	%r907, %r1440, %r906;
	or.b32 	%r1440, %r907, 2139095040;
	bra.uni 	$L__BB27_639;
$L__BB27_638:
	shl.b32 	%r917, %r305, 23;
	shl.b32 	%r918, %r306, 13;
	or.b32 	%r919, %r917, %r918;
	add.s32 	%r920, %r919, %r1440;
	add.s32 	%r1440, %r920, 939524096;
$L__BB27_639:
	and.pred 	%p1, %p364, %p365;
	div.rn.f32 	%r1439, %r1426, %r1418;
	@%p366 bra 	$L__BB27_662;
	cvt.f64.f32 	%rd192, %r1439;
	shr.u64 	%rd194, %rd192, 48;
	cvt.u32.u64 	%r921, %rd194;
	and.b32 	%r307, %r921, 32768;
	shr.u64 	%rd583, %rd192, 52;
	cvt.u32.u64 	%r922, %rd583;
	and.b32 	%r308, %r922, 2047;
	setp.eq.b32 	%p391, %r308, 0;
	@%p391 bra 	$L__BB27_643;
	and.b64 	%rd193, %rd192, 4503599627370495;
	setp.eq.b32 	%p390, %r1396, 12;
	selp.b32 	%r309, 11, 8, %p390;
	selp.b32 	%r311, 31744, 32640, %p390;
	setp.ne.b32 	%p392, %r308, 2047;
	@%p392 bra 	$L__BB27_644;
	setp.eq.b64 	%p393, %rd193, 0;
	add.s32 	%r923, %r309, -2;
	mov.b32 	%r924, 1;
	shl.b32 	%r925, %r924, %r923;
	selp.b32 	%r926, 0, %r925, %p393;
	or.b32 	%r927, %r926, %r311;
	or.b32 	%r928, %r927, %r307;
	cvt.u16.u32 	%rs28, %r928;
	bra.uni 	$L__BB27_654;
$L__BB27_643:
	cvt.u16.u32 	%rs28, %r307;
	bra.uni 	$L__BB27_654;
$L__BB27_644:
	selp.b32 	%r929, -14, -126, %p390;
	add.s32 	%r312, %r308, -1023;
	or.b64 	%rd195, %rd193, 4503599627370496;
	setp.ge.s32 	%p394, %r312, %r929;
	@%p394 bra 	$L__BB27_650;
	and.b64 	%rd196, %rd194, 32768;
	selp.b32 	%r939, 28, -81, %p390;
	sub.s32 	%r313, %r939, %r312;
	setp.gt.s32 	%p402, %r313, 0;
	@%p402 bra 	$L__BB27_647;
	bra.uni 	$L__BB27_646;
$L__BB27_647:
	setp.gt.u32 	%p403, %r313, 63;
	mov.b64 	%rd909, 0;
	@%p403 bra 	$L__BB27_649;
	shr.u64 	%rd597, %rd195, %r313;
	mov.b64 	%rd598, -1;
	shl.b64 	%rd599, %rd598, %r313;
	not.b64 	%rd600, %rd599;
	and.b64 	%rd601, %rd195, %rd600;
	add.s32 	%r940, %r313, -1;
	mov.b64 	%rd602, 1;
	shl.b64 	%rd603, %rd602, %r940;
	setp.gt.u64 	%p404, %rd601, %rd603;
	setp.eq.b64 	%p405, %rd601, %rd603;
	and.b64 	%rd604, %rd597, 1;
	setp.ne.b64 	%p406, %rd604, 0;
	and.pred 	%p407, %p405, %p406;
	or.pred 	%p408, %p404, %p407;
	selp.b64 	%rd605, 1, 0, %p408;
	add.s64 	%rd909, %rd597, %rd605;
	bra.uni 	$L__BB27_649;
$L__BB27_650:
	selp.b32 	%r310, 15, 127, %p390;
	sub.s32 	%r930, 53, %r309;
	shr.u64 	%rd584, %rd195, %r930;
	mov.b64 	%rd585, -1;
	shl.b64 	%rd586, %rd585, %r930;
	not.b64 	%rd587, %rd586;
	and.b64 	%rd588, %rd192, %rd587;
	sub.s32 	%r931, 52, %r309;
	mov.b64 	%rd589, 1;
	shl.b64 	%rd590, %rd589, %r931;
	setp.gt.u64 	%p395, %rd588, %rd590;
	setp.eq.b64 	%p396, %rd588, %rd590;
	and.b64 	%rd591, %rd584, 1;
	setp.ne.b64 	%p397, %rd591, 0;
	and.pred 	%p398, %p396, %p397;
	or.pred 	%p399, %p395, %p398;
	selp.b64 	%rd592, 1, 0, %p399;
	add.s64 	%rd197, %rd584, %rd592;
	shl.b64 	%rd198, %rd589, %r309;
	setp.eq.b64 	%p400, %rd197, %rd198;
	add.s32 	%r932, %r308, -1022;
	selp.b32 	%r314, %r932, %r312, %p400;
	setp.le.s32 	%p401, %r314, %r310;
	@%p401 bra 	$L__BB27_652;
	or.b32 	%r1438, %r307, %r311;
	bra.uni 	$L__BB27_653;
$L__BB27_652:
	selp.b32 	%r933, 1, 0, %p400;
	shr.u64 	%rd593, %rd197, %r933;
	add.s32 	%r934, %r314, %r310;
	add.s32 	%r935, %r309, -1;
	shl.b32 	%r936, %r934, %r935;
	shl.b64 	%rd594, %rd585, %r935;
	not.b64 	%rd595, %rd594;
	and.b64 	%rd596, %rd593, %rd595;
	cvt.u32.u64 	%r937, %rd596;
	or.b32 	%r938, %r936, %r937;
	or.b32 	%r1438, %r938, %r307;
$L__BB27_653:
	cvt.u16.u32 	%rs28, %r1438;
	bra.uni 	$L__BB27_654;
$L__BB27_646:
	neg.s32 	%r941, %r313;
	shl.b64 	%rd909, %rd195, %r941;
$L__BB27_649:
	or.b64 	%rd606, %rd909, %rd196;
	cvt.u16.u64 	%rs28, %rd606;
$L__BB27_654:
	setp.ne.b32 	%p409, %r1396, 13;
	cvt.u32.u16 	%r315, %rs28;
	@%p409 bra 	$L__BB27_656;
	shl.b32 	%r1439, %r315, 16;
	bra.uni 	$L__BB27_662;
$L__BB27_656:
	cvt.s32.s16 	%r942, %rs28;
	and.b32 	%r1439, %r942, -2147483648;
	bfe.u32 	%r316, %r315, 10, 5;
	setp.eq.b32 	%p410, %r316, 31;
	@%p410 bra 	$L__BB27_660;
	and.b32 	%r317, %r315, 1023;
	setp.ne.b32 	%p411, %r316, 0;
	@%p411 bra 	$L__BB27_661;
	setp.eq.b32 	%p412, %r317, 0;
	@%p412 bra 	$L__BB27_662;
	clz.b32 	%r945, %r317;
	xor.b32 	%r946, %r945, 31;
	sub.s32 	%r947, 9, %r946;
	shl.b32 	%r948, %r315, %r947;
	shl.b32 	%r949, %r946, 23;
	shl.b32 	%r950, %r948, 14;
	and.b32 	%r951, %r950, 8372224;
	add.s32 	%r952, %r949, %r1439;
	add.s32 	%r953, %r952, %r951;
	add.s32 	%r1439, %r953, 864026624;
	bra.uni 	$L__BB27_662;
$L__BB27_660:
	shl.b32 	%r943, %r315, 13;
	or.b32 	%r944, %r1439, %r943;
	or.b32 	%r1439, %r944, 2139095040;
	bra.uni 	$L__BB27_662;
$L__BB27_661:
	shl.b32 	%r954, %r316, 23;
	shl.b32 	%r955, %r317, 13;
	or.b32 	%r956, %r954, %r955;
	add.s32 	%r957, %r956, %r1439;
	add.s32 	%r1439, %r957, 939524096;
$L__BB27_662:
	@%p1 bra 	$L__BB27_664;
	mov.b32 	%r959, 16;
	atom.global.or.b32 %r958, [%rd881], %r959;
$L__BB27_664:
	abs.f32 	%r1387, %r1440;
	setp.ne.f32 	%p671, %r1387, 0f7F800000;
	abs.f32 	%r1388, %r1439;
	setp.ne.f32 	%p672, %r1388, 0f7F800000;
	and.pred 	%p673, %p671, %p672;
	@%p673 bra 	$L__BB27_666;
	setp.eq.b32 	%p674, %r319, 4;
	ld.local.b32 	%r1391, [%rd2];
	setp.eq.f32 	%p675, %r1391, 0f00000000;
	ld.local.b32 	%r1392, [%rd2+4];
	setp.eq.f32 	%p676, %r1392, 0f00000000;
	selp.b32 	%r1393, 8, 16, %p676;
	selp.b32 	%r1394, %r1393, 16, %p675;
	selp.b32 	%r1390, %r1394, 16, %p674;
	atom.global.or.b32 %r1389, [%rd881], %r1390;
$L__BB27_666:
	st.param.b32 	[func_retval0+4], %r1439;
	st.param.b32 	[func_retval0], %r1440;
	ret;
}
)QPTX";
        return result;
    }();
    return code;
}
