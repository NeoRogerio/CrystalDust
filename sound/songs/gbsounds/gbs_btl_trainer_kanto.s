	.include "MPlayDef.s"
	.include "GBCEngineDefs.s"

	.equ	gbs_btl_trainer_kanto_grp, voicegroup000
	.equ	gbs_btl_trainer_kanto_pri, 0
	.equ	gbs_btl_trainer_kanto_rev, 0
	.equ	gbs_btl_trainer_kanto_mvl, 127
	.equ	gbs_btl_trainer_kanto_key, 0
	.equ	gbs_btl_trainer_kanto_tbs, 1
	.equ	gbs_btl_trainer_kanto_exg, 0
	.equ	gbs_btl_trainer_kanto_cmp, 1


	.section .rodata
	.align 1

gbs_btl_trainer_kanto_track_0:
	.byte	KEYSH , gbs_btl_trainer_kanto_key+0
	.byte	TEMPO , GBP_TEMPO_BPM*gbs_btl_trainer_kanto_tbs/2
	.byte	GBP , 0x00
	.byte GBP_TEMPO
	.byte NONOTE0
	.byte GBP_Fs2
	.byte GBP_MVOL
	.byte GBP_Fs7
	.byte GBP_KEYSH
	.byte GBP_C11
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_As3
	.byte GBP_MOD
	.byte GBP_C2
	.byte GBP_Cs4
	.byte GBP_DUTYC
	.byte NONOTE1
	.byte NONOTE0
	.byte OCT3
	.byte GBP_A0
	.byte GBP_Gs0
	.byte GBP_G0
	.byte GBP_Gs0
	.byte GBP_G0
	.byte GBP_Fs0
	.byte GBP_F0
	.byte GBP_Fs0
	.byte GBP_F0
	.byte GBP_E0
	.byte GBP_Ds0
	.byte GBP_E0
	.byte GBP_Ds0
	.byte GBP_D0
	.byte GBP_Cs0
	.byte GBP_D0
	.byte GBP_Cs0
	.byte GBP_C0
	.byte OCT2
	.byte GBP_B0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_B0
	.byte GBP_As0
	.byte GBP_A0
	.byte GBP_As0
	.byte GBP_A0
	.byte GBP_Gs0
	.byte GBP_G0
	.byte GBP_Gs0
	.byte GBP_G0
	.byte GBP_Fs0
	.byte GBP_G0
	.byte GBP_DUTYC
	.byte NONOTE2
	.byte GBP_STYLE
	.byte GBP_As1
	.byte OCT3
	.byte GBP_Ds1
	.byte OCT1
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT3
	.byte GBP_C1
	.byte OCT1
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT3
	.byte GBP_Ds1
	.byte NONOTE1
	.byte OCT2
	.byte GBP_As1
	.byte OCT3
	.byte GBP_C1
	.byte NONOTE1
	.byte GBP_Ds1
	.byte NONOTE1
	.byte OCT2
	.byte GBP_Ds0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_Fs0
	.byte NONOTE0
	.byte OCT3
	.byte GBP_C1
	.byte OCT1
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT3
	.byte GBP_C1
	.byte OCT1
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT3
	.byte GBP_Ds1
	.byte NONOTE1
	.byte OCT2
	.byte GBP_As1
	.byte OCT3
	.byte GBP_C1
	.byte NONOTE1
	.byte GBP_Ds1
	.byte NONOTE1
	.byte GBP_Ds0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_G0
	.byte NONOTE0
	.byte GBP_STYLE
	.byte GBP_As3
	.byte GBP_Ds1
	.byte NONOTE3
	.byte GBP_F1
	.byte NONOTE3
	.byte GBP_Fs1
	.byte NONOTE1
	.byte GBP_Ds1
	.byte GBP_F1
	.byte NONOTE1
	.byte GBP_Fs1
	.byte NONOTE1
	.byte GBP_Ds1
	.byte GBP_F1
	.byte GBP_Fs1
gbs_btl_trainer_kanto_track_0_goto_0:
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_As7
	.byte GBP_Ds3
	.byte NONOTE1
	.byte GBP_C9
	.byte NONOTE3
	.byte GBP_Ds1
	.byte GBP_C1
	.byte OCT2
	.byte GBP_G0
	.byte OCT3
	.byte GBP_C0
	.byte GBP_Ds0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_Ds0
	.byte NONOTE0
	.byte GBP_Cs7
	.byte GBP_F7
	.byte GBP_Gs7
	.byte OCT4
	.byte GBP_Cs3
	.byte GBP_Cs0
	.byte OCT3
	.byte GBP_Gs0
	.byte GBP_F0
	.byte GBP_Cs0
	.byte GBP_Ds3
	.byte NONOTE1
	.byte GBP_C9
	.byte NONOTE3
	.byte GBP_Ds1
	.byte GBP_C1
	.byte OCT2
	.byte GBP_G0
	.byte OCT3
	.byte GBP_C0
	.byte GBP_Ds0
	.byte NONOTE0
	.byte GBP_D0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_Ds5
	.byte GBP_D5
	.byte GBP_C1
	.byte NONOTE1
	.byte NONOTE1
	.byte GBP_D1
	.byte NONOTE3
	.byte GBP_F1
	.byte NONOTE1
	.byte GBP_Gs1
	.byte GBP_G0
	.byte GBP_Fs0
	.byte OCT2
	.byte GBP_Gs0
	.byte GBP_F0
	.byte GBP_C0
	.byte GBP_Gs0
	.byte OCT3
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_C0
	.byte OCT2
	.byte GBP_Gs0
	.byte GBP_F0
	.byte NONOTE4
	.byte OCT3
	.byte GBP_Ds7
	.byte GBP_D3
	.byte OCT2
	.byte GBP_F0
	.byte GBP_A0
	.byte OCT3
	.byte GBP_C0
	.byte GBP_Ds0
	.byte GBP_D3
	.byte OCT2
	.byte GBP_D3
	.byte OCT3
	.byte GBP_F3
	.byte OCT2
	.byte GBP_D3
	.byte NONOTE3
	.byte GBP_D3
	.byte NONOTE3
	.byte GBP_D3
	.byte GBP_Gs0
	.byte GBP_F0
	.byte GBP_C0
	.byte GBP_Gs0
	.byte OCT3
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_C0
	.byte OCT2
	.byte GBP_Gs0
	.byte GBP_F0
	.byte NONOTE4
	.byte OCT3
	.byte GBP_Ds7
	.byte GBP_D3
	.byte OCT2
	.byte GBP_F0
	.byte GBP_A0
	.byte OCT3
	.byte GBP_C0
	.byte GBP_Ds0
	.byte GBP_D3
	.byte OCT2
	.byte GBP_D3
	.byte NONOTE3
	.byte GBP_D3
	.byte GBP_As0
	.byte OCT3
	.byte GBP_D0
	.byte GBP_F0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_D1
	.byte OCT3
	.byte GBP_F1
	.byte GBP_D1
	.byte OCT2
	.byte GBP_As1
	.byte GBP_D1
	.byte OCT3
	.byte GBP_D1
	.byte GBP_STYLE
	.byte GBP_F7
	.byte GBP_C0
	.byte GBP_Cs0
	.byte GBP_D0
	.byte GBP_Ds0
	.byte GBP_E0
	.byte GBP_Ds0
	.byte GBP_D0
	.byte GBP_Cs0
	.byte GBP_C0
	.byte NONOTE2
	.byte GBP_Ds3
	.byte GBP_FRDEL
	.byte NONOTE6
	.byte GBP_F7
	.byte GBP_Ds0
	.byte NONOTE0
	.byte GBP_Ds0
	.byte NONOTE0
	.byte GBP_Ds0
	.byte NONOTE6
	.byte GBP_Ds0
	.byte NONOTE0
	.byte GBP_Ds0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_G0
	.byte NONOTE2
	.byte GBP_G0
	.byte NONOTE2
	.byte OCT3
	.byte GBP_C7
	.byte GBP_STYLE
	.byte GBP_Fs7
	.byte GBP_Cs1
	.byte GBP_D1
	.byte GBP_Ds1
	.byte GBP_E1
	.byte GBP_F1
	.byte GBP_E1
	.byte GBP_Ds1
	.byte GBP_D1
	.byte GBP_Cs1
	.byte NONOTE5
	.byte GBP_E7
	.byte GBP_E0
	.byte NONOTE0
	.byte GBP_E0
	.byte NONOTE0
	.byte GBP_E0
	.byte NONOTE6
	.byte GBP_E0
	.byte NONOTE0
	.byte GBP_E0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_Gs0
	.byte NONOTE2
	.byte GBP_Gs0
	.byte NONOTE2
	.byte OCT3
	.byte GBP_Cs7
	.byte GBP_STYLE
	.byte GBP_G7
	.byte GBP_D1
	.byte GBP_Ds1
	.byte GBP_E1
	.byte GBP_F1
	.byte GBP_Fs1
	.byte GBP_F1
	.byte GBP_E1
	.byte GBP_Ds1
	.byte GBP_D1
	.byte NONOTE5
	.byte GBP_F7
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE6
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_A0
	.byte NONOTE2
	.byte GBP_A0
	.byte NONOTE2
	.byte OCT3
	.byte GBP_D7
	.byte GBP_STYLE
	.byte GBP_Gs7
	.byte GBP_Ds1
	.byte GBP_E1
	.byte GBP_F1
	.byte GBP_Fs1
	.byte GBP_G1
	.byte GBP_Fs1
	.byte GBP_F1
	.byte GBP_E1
	.byte GBP_Ds1
	.byte NONOTE5
	.byte GBP_Fs7
	.byte GBP_STYLE
	.byte GBP_A7
	.byte GBP_Gs7
	.byte GBP_As7
	.byte GBP_STYLE
	.byte GBP_As7
	.byte OCT4
	.byte GBP_D7
	.byte GBP_D1
	.byte NONOTE5
	.byte OCT3
	.byte GBP_As1
	.byte GBP_Fs1
	.byte GBP_Ds1
	.byte OCT2
	.byte GBP_As1
	.byte OCT3
	.byte GBP_Fs1
	.byte GBP_Ds1
	.byte OCT2
	.byte GBP_As1
	.byte GBP_Fs1
	.byte OCT3
	.byte GBP_Gs1
	.byte NONOTE1
	.byte GBP_Ds11
	.byte GBP_STYLE
	.byte GBP_As1
	.byte OCT5
	.byte GBP_C1
	.byte GBP_C1
	.byte GBP_C7
	.byte GBP_C1
	.byte GBP_C1
	.byte GBP_C3
	.byte GBP_C3
	.byte GBP_C3
	.byte GBP_C3
	.byte GBP_STYLE
	.byte GBP_As7
	.byte OCT3
	.byte GBP_As1
	.byte GBP_Fs1
	.byte GBP_Ds1
	.byte OCT2
	.byte GBP_As1
	.byte OCT3
	.byte GBP_Fs1
	.byte GBP_Ds1
	.byte OCT2
	.byte GBP_As1
	.byte GBP_Fs1
	.byte OCT3
	.byte GBP_Fs1
	.byte NONOTE1
	.byte GBP_B3
	.byte GBP_As3
	.byte GBP_Gs3
	.byte GBP_Fs3
	.byte GBP_F3
	.byte GBP_Ds3
	.byte GBP_D3
	.byte GBP_Ds7
	.byte GBP_Fs7
	.byte OCT4
	.byte GBP_C7
	.byte GBP_Ds7
	.byte OCT3
	.byte GBP_Cs15
	.byte GBP_Cs1
	.byte NONOTE1
	.byte GBP_Ds1
	.byte NONOTE1
	.byte GBP_F1
	.byte NONOTE1
	.byte OCT2
	.byte GBP_Gs1
	.byte NONOTE1
	.byte OCT3
	.byte GBP_F1
	.byte GBP_Fs1
	.byte GBP_F1
	.byte GBP_Ds1
	.byte GBP_F1
	.byte GBP_STYLE
	.byte GBP_F7
	.byte GBP_E0
	.byte GBP_D0
	.byte GBP_C0
	.byte OCT2
	.byte GBP_B0
	.byte GBP_A0
	.byte GBP_G0
	.byte GBP_STYLE
	.byte GBP_A1
	.byte OCT3
	.byte GBP_Cs1
	.byte OCT1
	.byte GBP_G1
	.byte GBP_G1
	.byte OCT3
	.byte GBP_Cs1
	.byte OCT1
	.byte GBP_G1
	.byte GBP_G1
	.byte GBP_STYLE
	.byte GBP_As7
	.byte OCT3
	.byte GBP_D3
	.byte GBP_JUMPC
	.byte NONOTE0
	.int gbs_btl_trainer_kanto_track_0_goto_0

gbs_btl_trainer_kanto_track_1:
	.byte	KEYSH , gbs_btl_trainer_kanto_key+0
	.byte	GBP , 0x01
	.byte GBP_KEYSH
	.byte GBP_C11
	.byte GBP_MOD
	.byte NONOTE6
	.byte GBP_D6
	.byte GBP_DUTYC
	.byte NONOTE1
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte OCT6
	.byte OCT3
	.byte GBP_As3
	.byte GBP_As3
	.byte GBP_As3
	.byte GBP_As3
	.byte GBP_As3
	.byte GBP_As3
	.byte GBP_As3
	.byte GBP_G0
	.byte GBP_Gs0
	.byte GBP_G0
	.byte GBP_Fs0
	.byte GBP_DUTYC
	.byte NONOTE3
	.byte GBP_STYLE
	.byte GBP_F2
gbs_btl_trainer_kanto_track_1_goto_0:
	.byte OCT2
	.byte GBP_G0
	.byte GBP_Gs0
	.byte GBP_G0
	.byte GBP_Fs0
	.byte GBP_JUMPC
	.byte NONOTE14
	.int gbs_btl_trainer_kanto_track_1_goto_0
	.byte GBP_G0
	.byte GBP_Gs0
	.byte GBP_G0
	.byte GBP_F0
	.byte GBP_Ds0
	.byte GBP_D0
	.byte GBP_C0
	.byte OCT1
	.byte GBP_B0
	.byte GBP_STYLE
	.byte OCT0
	.byte GBP_DUTYC
	.byte NONOTE2
	.byte GBP_C1
	.byte OCT2
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT1
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT0
	.byte GBP_As1
	.byte OCT1
	.byte GBP_As0
	.byte NONOTE0
	.byte OCT0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_A1
	.byte OCT1
	.byte GBP_A0
	.byte NONOTE0
	.byte OCT0
	.byte GBP_A0
	.byte NONOTE0
	.byte GBP_Gs1
	.byte OCT1
	.byte GBP_Gs0
	.byte NONOTE0
	.byte OCT0
	.byte GBP_Gs0
	.byte NONOTE0
	.byte GBP_G0
	.byte GBP_B0
	.byte OCT1
	.byte GBP_D0
	.byte GBP_F0
	.byte GBP_G0
	.byte GBP_B0
	.byte OCT2
	.byte GBP_D0
	.byte GBP_F0
gbs_btl_trainer_kanto_track_1_goto_1:
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte OCT0
	.byte OCT1
	.byte GBP_C0
	.byte GBP_C0
	.byte OCT2
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT1
	.byte GBP_G0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT1
	.byte GBP_C1
	.byte GBP_B0
	.byte NONOTE0
	.byte GBP_G0
	.byte NONOTE0
	.byte GBP_B0
	.byte NONOTE0
	.byte GBP_C1
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_G0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_C1
	.byte GBP_A0
	.byte NONOTE0
	.byte GBP_Gs0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT1
	.byte GBP_Cs0
	.byte GBP_Cs0
	.byte GBP_Gs0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_Cs1
	.byte OCT1
	.byte GBP_Cs1
	.byte GBP_Gs0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_C1
	.byte OCT1
	.byte GBP_Cs1
	.byte GBP_Gs0
	.byte NONOTE0
	.byte GBP_As1
	.byte GBP_Cs0
	.byte GBP_Cs0
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_Gs1
	.byte OCT2
	.byte GBP_Cs0
	.byte NONOTE0
	.byte GBP_F1
	.byte GBP_Gs0
	.byte NONOTE0
	.byte GBP_As1
	.byte OCT1
	.byte GBP_C0
	.byte GBP_C0
	.byte OCT2
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT1
	.byte GBP_G0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT1
	.byte GBP_C1
	.byte GBP_B0
	.byte NONOTE0
	.byte GBP_G0
	.byte NONOTE0
	.byte GBP_B0
	.byte NONOTE0
	.byte GBP_C1
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_G0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_C1
	.byte GBP_A0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_A0
	.byte NONOTE0
	.byte OCT0
	.byte GBP_As0
	.byte GBP_As0
	.byte OCT1
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_As1
	.byte OCT0
	.byte GBP_As1
	.byte OCT1
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_A1
	.byte OCT0
	.byte GBP_As1
	.byte OCT1
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_Gs1
	.byte OCT0
	.byte GBP_As0
	.byte GBP_As0
	.byte OCT1
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_G1
	.byte GBP_As0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_D1
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_As1
	.byte OCT0
	.byte GBP_F1
	.byte OCT1
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE0
	.byte OCT0
	.byte GBP_F1
	.byte OCT1
	.byte GBP_E0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_E0
	.byte NONOTE0
	.byte OCT0
	.byte GBP_F1
	.byte OCT1
	.byte GBP_Ds0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_Ds0
	.byte NONOTE0
	.byte OCT0
	.byte GBP_F1
	.byte OCT1
	.byte GBP_D0
	.byte NONOTE0
	.byte GBP_Ds0
	.byte GBP_C0
	.byte OCT0
	.byte GBP_As0
	.byte GBP_A0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_F3
	.byte OCT0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_Fs3
	.byte OCT0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_G3
	.byte OCT0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_Gs3
	.byte OCT0
	.byte GBP_F1
	.byte OCT1
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE0
	.byte OCT0
	.byte GBP_F1
	.byte OCT1
	.byte GBP_E0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_E0
	.byte NONOTE0
	.byte OCT0
	.byte GBP_F1
	.byte OCT1
	.byte GBP_Ds0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_Ds0
	.byte NONOTE0
	.byte OCT0
	.byte GBP_F1
	.byte OCT1
	.byte GBP_D0
	.byte NONOTE0
	.byte GBP_Ds0
	.byte GBP_C0
	.byte OCT0
	.byte GBP_As0
	.byte GBP_A0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_F3
	.byte OCT0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_Fs3
	.byte OCT0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_G3
	.byte OCT0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_Gs3
	.byte GBP_MOD
	.byte GBP_C2
	.byte GBP_Cs4
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_Fs8
	.byte OCT3
	.byte GBP_G15
	.byte GBP_STYLE
	.byte GBP_Fs7
	.byte GBP_G15
	.byte GBP_FRDEL
	.byte NONOTE6
	.byte GBP_G8
	.byte GBP_Gs15
	.byte GBP_STYLE
	.byte GBP_G7
	.byte GBP_Gs14
	.byte GBP_G0
	.byte GBP_Gs6
	.byte GBP_A0
	.byte GBP_As2
	.byte GBP_A0
	.byte GBP_Gs7
	.byte GBP_G3
	.byte GBP_F5
	.byte NONOTE1
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_Gs8
	.byte GBP_A15
	.byte GBP_STYLE
	.byte GBP_Gs7
	.byte GBP_A15
	.byte GBP_STYLE
	.byte GBP_A7
	.byte GBP_As15
	.byte GBP_STYLE
	.byte OCT0
	.byte OCT4
	.byte GBP_D7
	.byte GBP_F7
	.byte GBP_MOD
	.byte NONOTE4
	.byte GBP_D6
	.byte OCT1
	.byte GBP_As3
	.byte GBP_Ds3
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_STYLE
	.byte GBP_FRDEL
	.byte GBP_Gs5
	.byte GBP_STYLE
	.byte OCT0
	.byte GBP_Gs15
	.byte GBP_As3
	.byte GBP_Ds3
	.byte GBP_Ds0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_Ds13
	.byte OCT1
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_Ds1
	.byte NONOTE1
	.byte GBP_FRDEL
	.byte NONOTE6
	.byte OCT0
	.byte OCT1
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_C1
	.byte NONOTE1
	.byte GBP_C1
	.byte NONOTE1
	.byte OCT2
	.byte GBP_Gs7
	.byte OCT3
	.byte GBP_F1
	.byte GBP_Fs1
	.byte GBP_F1
	.byte GBP_Ds1
	.byte GBP_F1
	.byte NONOTE1
	.byte GBP_Ds1
	.byte NONOTE1
	.byte OCT2
	.byte GBP_F1
	.byte NONOTE1
	.byte GBP_Fs1
	.byte NONOTE1
	.byte GBP_Gs1
	.byte NONOTE1
	.byte GBP_Cs1
	.byte NONOTE1
	.byte GBP_Gs1
	.byte GBP_As1
	.byte GBP_Gs1
	.byte GBP_Fs1
	.byte GBP_Gs1
	.byte GBP_STYLE
	.byte GBP_Fs2
	.byte GBP_G0
	.byte GBP_F0
	.byte GBP_E0
	.byte GBP_D0
	.byte GBP_C0
	.byte OCT1
	.byte GBP_B0
	.byte GBP_STYLE
	.byte GBP_B1
	.byte OCT2
	.byte GBP_B1
	.byte OCT0
	.byte GBP_Fs0
	.byte NONOTE0
	.byte GBP_Fs0
	.byte NONOTE0
	.byte OCT2
	.byte GBP_B1
	.byte OCT0
	.byte GBP_Fs0
	.byte NONOTE0
	.byte GBP_Fs0
	.byte NONOTE0
	.byte GBP_STYLE
	.byte OCT0
	.byte OCT2
	.byte GBP_B3
	.byte GBP_JUMPC
	.byte NONOTE0
	.int gbs_btl_trainer_kanto_track_1_goto_1

gbs_btl_trainer_kanto_track_2:
	.byte	KEYSH , gbs_btl_trainer_kanto_key+0
	.byte	GBP , 0x02
	.byte GBP_KEYSH
	.byte GBP_C11
	.byte GBP_MOD
	.byte GBP_C2
	.byte GBP_Cs3
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_C5
	.byte OCT1
	.byte GBP_As0
	.byte OCT3
	.byte GBP_As0
	.byte OCT2
	.byte GBP_As1
	.byte OCT1
	.byte GBP_A0
	.byte OCT3
	.byte GBP_A0
	.byte OCT2
	.byte GBP_A1
	.byte OCT1
	.byte GBP_Gs0
	.byte OCT3
	.byte GBP_Gs0
	.byte OCT2
	.byte GBP_Gs1
	.byte OCT1
	.byte GBP_G0
	.byte OCT3
	.byte GBP_G0
	.byte OCT2
	.byte GBP_G1
	.byte OCT1
	.byte GBP_Fs0
	.byte OCT3
	.byte GBP_Fs0
	.byte OCT2
	.byte GBP_Fs1
	.byte OCT1
	.byte GBP_F0
	.byte OCT3
	.byte GBP_F0
	.byte OCT2
	.byte GBP_F1
	.byte OCT1
	.byte GBP_E0
	.byte OCT3
	.byte GBP_E0
	.byte OCT2
	.byte GBP_E1
	.byte GBP_D0
	.byte GBP_F0
	.byte GBP_B0
	.byte OCT3
	.byte GBP_D0
	.byte GBP_STYLE
	.byte GBP_C8
	.byte OCT5
	.byte GBP_C1
	.byte OCT2
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT4
	.byte GBP_F1
	.byte OCT2
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT4
	.byte GBP_Fs1
	.byte OCT3
	.byte GBP_C0
	.byte GBP_Ds0
	.byte OCT4
	.byte GBP_Ds1
	.byte GBP_F1
	.byte NONOTE1
	.byte GBP_Fs1
	.byte NONOTE1
	.byte OCT3
	.byte GBP_G0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_B0
	.byte NONOTE0
	.byte OCT4
	.byte GBP_Ds1
	.byte OCT2
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT4
	.byte GBP_F1
	.byte OCT2
	.byte GBP_C0
	.byte NONOTE0
	.byte GBP_C0
	.byte NONOTE0
	.byte OCT4
	.byte GBP_Fs1
	.byte OCT3
	.byte GBP_C0
	.byte GBP_Ds0
	.byte OCT4
	.byte GBP_Ds1
	.byte GBP_F1
	.byte NONOTE1
	.byte GBP_Fs1
	.byte NONOTE1
	.byte GBP_G0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_B0
	.byte NONOTE0
	.byte OCT5
	.byte GBP_C1
	.byte NONOTE3
	.byte GBP_D1
	.byte NONOTE3
	.byte GBP_Ds1
	.byte NONOTE1
	.byte GBP_C1
	.byte GBP_D1
	.byte NONOTE1
	.byte GBP_Ds1
	.byte NONOTE1
	.byte OCT4
	.byte GBP_G1
	.byte GBP_As1
	.byte GBP_B1
gbs_btl_trainer_kanto_track_2_goto_0:
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_C4
	.byte OCT5
	.byte GBP_C3
	.byte GBP_FRDEL
	.byte NONOTE6
	.byte GBP_C4
	.byte OCT4
	.byte GBP_B0
	.byte GBP_As0
	.byte GBP_A0
	.byte GBP_Gs0
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_C4
	.byte GBP_G9
	.byte NONOTE1
	.byte GBP_FRDEL
	.byte NONOTE6
	.byte GBP_C4
	.byte GBP_G0
	.byte GBP_Gs0
	.byte GBP_A0
	.byte GBP_As0
	.byte OCT5
	.byte GBP_C5
	.byte OCT4
	.byte GBP_A0
	.byte GBP_Gs0
	.byte GBP_G7
	.byte OCT5
	.byte GBP_C6
	.byte OCT4
	.byte GBP_B0
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_C4
	.byte OCT5
	.byte GBP_Cs15
	.byte GBP_Cs7
	.byte GBP_F3
	.byte GBP_Gs0
	.byte GBP_F0
	.byte GBP_Cs0
	.byte OCT4
	.byte GBP_Gs0
	.byte OCT5
	.byte GBP_C3
	.byte GBP_FRDEL
	.byte NONOTE6
	.byte GBP_C4
	.byte OCT4
	.byte GBP_B0
	.byte GBP_As0
	.byte GBP_A0
	.byte GBP_Gs0
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_C4
	.byte GBP_G9
	.byte NONOTE1
	.byte GBP_FRDEL
	.byte NONOTE6
	.byte GBP_C4
	.byte GBP_G0
	.byte GBP_Gs0
	.byte GBP_A0
	.byte GBP_As0
	.byte OCT5
	.byte GBP_C5
	.byte OCT4
	.byte GBP_A0
	.byte GBP_Gs0
	.byte GBP_G7
	.byte OCT5
	.byte GBP_C6
	.byte OCT4
	.byte GBP_B0
	.byte GBP_As15
	.byte GBP_As15
	.byte GBP_As12
	.byte GBP_B0
	.byte OCT5
	.byte GBP_C0
	.byte GBP_Cs0
	.byte GBP_D7
	.byte GBP_F1
	.byte GBP_D1
	.byte OCT4
	.byte GBP_As1
	.byte GBP_A1
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_C0
	.byte GBP_Gs10
	.byte GBP_STYLE
	.byte GBP_C4
	.byte GBP_C0
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_Gs0
	.byte NONOTE0
	.byte GBP_STYLE
	.byte GBP_C0
	.byte OCT5
	.byte GBP_C5
	.byte GBP_FRDEL
	.byte NONOTE6
	.byte GBP_C0
	.byte OCT4
	.byte GBP_B0
	.byte GBP_As0
	.byte GBP_A0
	.byte GBP_Gs0
	.byte GBP_Gs15
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_C0
	.byte GBP_As15
	.byte GBP_STYLE
	.byte GBP_Cs5
	.byte GBP_D0
	.byte OCT3
	.byte GBP_As0
	.byte GBP_F0
	.byte GBP_As0
	.byte OCT4
	.byte GBP_F0
	.byte GBP_D0
	.byte OCT3
	.byte GBP_As0
	.byte OCT4
	.byte GBP_D0
	.byte GBP_As0
	.byte GBP_F0
	.byte GBP_D0
	.byte GBP_F0
	.byte OCT5
	.byte GBP_D1
	.byte GBP_Cs0
	.byte GBP_C0
	.byte GBP_STYLE
	.byte GBP_C0
	.byte OCT4
	.byte GBP_Gs10
	.byte GBP_STYLE
	.byte GBP_C4
	.byte GBP_C0
	.byte GBP_F0
	.byte NONOTE0
	.byte GBP_Gs0
	.byte NONOTE0
	.byte GBP_STYLE
	.byte GBP_C0
	.byte OCT5
	.byte GBP_C6
	.byte GBP_FRDEL
	.byte NONOTE6
	.byte GBP_C0
	.byte GBP_Cs0
	.byte GBP_D0
	.byte GBP_FRDEL
	.byte NONOTE12
	.byte GBP_C0
	.byte GBP_Ds7
	.byte GBP_D11
	.byte GBP_Gs0
	.byte GBP_F0
	.byte GBP_STYLE
	.byte GBP_Cs5
	.byte OCT4
	.byte GBP_As0
	.byte GBP_F0
	.byte GBP_Gs0
	.byte GBP_Gs0
	.byte GBP_Gs0
	.byte NONOTE0
	.byte GBP_As0
	.byte NONOTE0
	.byte GBP_Gs1
	.byte GBP_G1
	.byte GBP_F1
	.byte GBP_Ds1
	.byte GBP_F1
	.byte GBP_STYLE
	.byte GBP_Cs4
	.byte OCT2
	.byte GBP_G0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_Ds0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_G0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_Ds0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_G0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_Ds0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_G0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_Ds0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_G0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_Ds0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_G0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_Ds0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_G0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_Ds0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_G0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_Ds0
	.byte OCT3
	.byte GBP_C0
	.byte OCT2
	.byte GBP_Gs0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_E0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_Gs0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_E0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_Gs0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_E0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_Gs0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_E0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_Gs0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_E0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_Gs0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_E0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_Gs0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_E0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_Gs0
	.byte OCT3
	.byte GBP_Cs0
	.byte OCT2
	.byte GBP_E0
	.byte OCT3
	.byte GBP_Cs0
	.byte GBP_STYLE
	.byte GBP_C4
	.byte OCT2
	.byte GBP_A0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_F0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_A0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_F0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_A0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_F0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_A0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_F0
	.byte OCT3
	.byte GBP_D0
	.byte GBP_STYLE
	.byte GBP_C5
	.byte OCT2
	.byte GBP_A0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_F0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_A0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_F0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_A0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_F0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_A0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_F0
	.byte OCT3
	.byte GBP_D0
	.byte GBP_STYLE
	.byte GBP_C5
	.byte OCT2
	.byte GBP_As0
	.byte OCT3
	.byte GBP_Ds0
	.byte OCT2
	.byte GBP_Fs0
	.byte OCT3
	.byte GBP_Ds0
	.byte OCT2
	.byte GBP_As0
	.byte OCT3
	.byte GBP_Ds0
	.byte OCT2
	.byte GBP_Fs0
	.byte OCT3
	.byte GBP_Ds0
	.byte OCT2
	.byte GBP_As0
	.byte OCT3
	.byte GBP_Ds0
	.byte OCT2
	.byte GBP_Fs0
	.byte OCT3
	.byte GBP_Ds0
	.byte OCT2
	.byte GBP_As0
	.byte OCT3
	.byte GBP_Ds0
	.byte OCT2
	.byte GBP_Fs0
	.byte OCT3
	.byte GBP_Ds0
	.byte GBP_STYLE
	.byte GBP_C4
	.byte OCT2
	.byte GBP_F0
	.byte GBP_Gs0
	.byte GBP_B0
	.byte OCT3
	.byte GBP_D0
	.byte OCT2
	.byte GBP_Gs0
	.byte GBP_B0
	.byte OCT3
	.byte GBP_D0
	.byte GBP_F0
	.byte OCT2
	.byte GBP_B0
	.byte OCT3
	.byte GBP_D0
	.byte GBP_F0
	.byte GBP_Gs0
	.byte GBP_D0
	.byte GBP_F0
	.byte GBP_Gs0
	.byte OCT4
	.byte GBP_D0
	.byte OCT5
	.byte GBP_Ds3
	.byte OCT4
	.byte GBP_As3
	.byte OCT5
	.byte GBP_Cs0
	.byte NONOTE0
	.byte GBP_C5
	.byte OCT3
	.byte GBP_C0
	.byte GBP_Ds0
	.byte GBP_Gs0
	.byte OCT4
	.byte GBP_C0
	.byte GBP_Ds0
	.byte GBP_Gs0
	.byte OCT5
	.byte GBP_C0
	.byte GBP_Ds0
	.byte GBP_Gs0
	.byte GBP_Ds0
	.byte GBP_C0
	.byte OCT4
	.byte GBP_Gs0
	.byte GBP_Ds0
	.byte GBP_C0
	.byte OCT3
	.byte GBP_Gs0
	.byte GBP_Ds0
	.byte OCT5
	.byte GBP_Ds3
	.byte OCT4
	.byte GBP_As3
	.byte GBP_B0
	.byte NONOTE0
	.byte OCT5
	.byte GBP_Fs11
	.byte GBP_F0
	.byte GBP_Fs0
	.byte GBP_Gs15
	.byte GBP_F7
	.byte GBP_Cs0
	.byte NONOTE0
	.byte GBP_Ds0
	.byte NONOTE0
	.byte GBP_F0
	.byte NONOTE0
	.byte OCT4
	.byte GBP_Gs0
	.byte NONOTE0
	.byte OCT5
	.byte GBP_F0
	.byte GBP_Fs0
	.byte GBP_F0
	.byte GBP_Ds0
	.byte GBP_F0
	.byte GBP_FRDEL
	.byte NONOTE6
	.byte GBP_Cs4
	.byte GBP_E0
	.byte GBP_D0
	.byte GBP_C0
	.byte OCT4
	.byte GBP_B0
	.byte GBP_A0
	.byte GBP_G0
	.byte GBP_STYLE
	.byte GBP_C4
	.byte GBP_G1
	.byte OCT2
	.byte GBP_G0
	.byte NONOTE0
	.byte GBP_G0
	.byte NONOTE0
	.byte OCT4
	.byte GBP_G1
	.byte OCT2
	.byte GBP_G0
	.byte NONOTE0
	.byte GBP_G0
	.byte NONOTE0
	.byte GBP_STYLE
	.byte GBP_C4
	.byte OCT4
	.byte GBP_G3
	.byte GBP_JUMPC
	.byte NONOTE0
	.int gbs_btl_trainer_kanto_track_2_goto_0



	.align 4
	.global gbs_btl_trainer_kanto_Header
gbs_btl_trainer_kanto_Header:
	.byte 0x03	@ NumTrks
	.byte 0x00	@ NumBlks
	.byte gbs_btl_trainer_kanto_pri @ Priority
	.byte gbs_btl_trainer_kanto_rev @ Reverb

	.int gbs_btl_trainer_kanto_grp

	.int gbs_btl_trainer_kanto_track_0
	.int gbs_btl_trainer_kanto_track_1
	.int gbs_btl_trainer_kanto_track_2
