package Princess_Collection;

class GameData {

	public CardData[] Card;
	public AIData[] AI;
	public SkillData[] Skill;
	public SkillModel[] Model;
			
	public static class Atb {
		public static final int BEAT = 0;
		public static final int FIRE = 1;
		public static final int TUNDER = 2;
		public static final int LIGHT = 3;
		public static final int DARK = 4;
		public static final int BUFF = 5;
		public static final int DEBUFF = 6;
	}
	
	public static class Pty {
		public static final int NONE = 0;
		public static final int STR = 1;
		public static final int SPD = 2;
		public static final int ATK = 3;
		public static final int INT = 4;
	}
	
	public static class Gup {
		public static final int TOHEARTH2 = 0;
		public static final int UTAWARERUMONO = 1;
		public static final int TEARSTOTIARA = 2;
		public static final int KUSARI = 3;
		public static final int FULLANI = 4;
	}
	
	GameData(){
		Card = new CardData[65];
				
		Card[0] = new CardData(400, 10, 62, 51, 1, false, Atb.LIGHT, Gup.TOHEARTH2, 4, 6, 0, 1);
		Card[1] = new CardData(700, 90, 66, 18, 3, true, Atb.BEAT, Gup.TOHEARTH2, 5, 2, 2, 3);
		Card[2] = new CardData(600, 78, 23, 55, 2, true, Atb.BEAT, Gup.TOHEARTH2, 3, 5, 4, 5);
		Card[3] = new CardData(400, 18, 70, 80, 1, false, Atb.TUNDER, Gup.TOHEARTH2, 2, 2, 6, 7);
		Card[4] = new CardData(500, 72, 13, 41, 1, true, Atb.BEAT, Gup.TOHEARTH2, 2, 2, 8, 9);
		Card[5] = new CardData(300, 12, 88, 78, 1, false, Atb.TUNDER, Gup.TOHEARTH2, 4, 3, 10, 11);
		Card[6] = new CardData(500, 61, 71, 84, 2, false, Atb.DARK, Gup.TOHEARTH2, 3, 3, 12, 13);
		Card[7] = new CardData(600, 30, 84, 23, 2, true, Atb.LIGHT, Gup.TOHEARTH2, 3, 3, 14, 15);
		Card[8] = new CardData(700, 66, 78, 70, 3, true, Atb.DARK, Gup.TOHEARTH2, 6, 6, 16, 17);
		Card[9] = new CardData(300, 18, 57, 71, 1, false, Atb.LIGHT, Gup.TOHEARTH2, 2, 2, 18, 19);
		Card[10] = new CardData(500, 60, 75, 34, 2, true, Atb.FIRE, Gup.TOHEARTH2, 2, 4, 20, 21);
		Card[11] = new CardData(600, 79, 31, 54, 2, true, Atb.BEAT, Gup.TOHEARTH2, 4, 6, 22, 23);
		Card[12] = new CardData(600, 78, 66, 45, 2, true, Atb.BEAT, Gup.TOHEARTH2, 3, 4, 24, 25);
		Card[13] = new CardData(800, 81, 31, 10, 3, true, Atb.BEAT, Gup.TOHEARTH2, 4, 2, 26, 27);
		Card[14] = new CardData(400, 30, 62, 65, 1, false, Atb.FIRE, Gup.TOHEARTH2, 2, 6, 28, 29);
		Card[15] = new CardData(500, 61, 27, 53, 1, true, Atb.BEAT, Gup.TOHEARTH2, 2, 4, 30, 31);
		Card[16] = new CardData(300, 10, 68, 28, 1, false, Atb.FIRE, Gup.TOHEARTH2, 2, 4, 32, 33);
		Card[17] = new CardData(600, 20, 70, 40, 2, false, Atb.TUNDER, Gup.TOHEARTH2, 4, 6, 34, 35);
		Card[18] = new CardData(400, 12, 62, 42, 1, false, Atb.DARK, Gup.TOHEARTH2, 2, 6, 36, 37);
		
		Card[19] = new CardData(300, 18, 65, 64, 1, false, Atb.LIGHT, Gup.UTAWARERUMONO, 6, 2, 38, 39);
		Card[20] = new CardData(700, 60, 28, 31, 1, true, Atb.BEAT, Gup.UTAWARERUMONO, 2, 2, 40, 41);
		Card[21] = new CardData(500, 76, 76, 63, 2, true, Atb.BEAT, Gup.UTAWARERUMONO, 2, 3, 42, 43);
		Card[22] = new CardData(400, 68, 32, 50, 1, false, Atb.BEAT, Gup.UTAWARERUMONO, 2, 2, 44, 45);
		Card[23] = new CardData(400, 68, 32, 50, 1, false, Atb.BEAT, Gup.UTAWARERUMONO, 2, 2, 46, 47);
		Card[24] = new CardData(500, 78, 13, 92, 2, true, Atb.BEAT, Gup.UTAWARERUMONO, 2, 4, 48, 49);
		Card[25] = new CardData(700, 98, 25, 10, 3, true, Atb.BEAT, Gup.UTAWARERUMONO, 4, 2, 50, 51);
		Card[26] = new CardData(600, 73, 41, 77, 3, true, Atb.BEAT, Gup.UTAWARERUMONO, 2, 2, 52, 53);
		Card[27] = new CardData(500, 17, 84, 19, 2, false, Atb.LIGHT, Gup.UTAWARERUMONO, 2, 4, 54, 55);
		Card[28] = new CardData(300, 12, 76, 50, 1, false, Atb.DARK, Gup.UTAWARERUMONO, 2, 2, 56, 57);
		Card[29] = new CardData(300, 22, 94, 12, 3, false, Atb.DARK, Gup.UTAWARERUMONO, 4, 6, 58, 59);
		Card[30] = new CardData(800, 84, 10, 23, 2, true, Atb.BEAT, Gup.UTAWARERUMONO, 4, 1, 60, 61);
		Card[31] = new CardData(600, 71, 80, 50, 2, true, Atb.BEAT, Gup.UTAWARERUMONO, 4, 2, 62, 63);
		Card[32] = new CardData(100, 10, 78, 33, 1, false, Atb.LIGHT, Gup.UTAWARERUMONO, 4, 8, 64, 65);
		Card[33] = new CardData(500, 72, 56, 66, 2, true, Atb.BEAT, Gup.UTAWARERUMONO, 3, 4, 66, 67);
		
		Card[34] = new CardData(700, 81, 88, 32, 3, true, Atb.BEAT, Gup.TEARSTOTIARA, 2, 3, 68, 69);
		Card[35] = new CardData(300, 10, 71, 51, 1, false, Atb.TUNDER, Gup.TEARSTOTIARA, 2, 3, 70, 71);
		Card[36] = new CardData(700, 77, 69, 50, 2, true, Atb.BEAT, Gup.TEARSTOTIARA, 2, 1, 72, 73);
		Card[37] = new CardData(500, 74, 40, 36, 2, true, Atb.BEAT, Gup.TEARSTOTIARA, 2, 2, 74, 75);
		Card[38] = new CardData(500, 69, 76, 77, 2, true, Atb.BEAT, Gup.TEARSTOTIARA, 4, 6, 76, 77);
		Card[39] = new CardData(500, 43, 88, 24, 2, false, Atb.TUNDER, Gup.TEARSTOTIARA, 3, 2, 78, 79);
		Card[40] = new CardData(500, 35, 73, 45, 1,	false, Atb.DARK, Gup.TEARSTOTIARA, 6, 3, 80, 81);
		Card[41] = new CardData(400, 21, 78, 88, 1, false, Atb.DARK, Gup.TEARSTOTIARA, 4, 3, 82, 83);
		Card[42] = new CardData(300, 13, 73, 67, 1, false, Atb.TUNDER, Gup.TEARSTOTIARA, 6, 4, 84, 85);
		Card[43] = new CardData(400, 21, 77, 27, 1, false, Atb.LIGHT, Gup.TEARSTOTIARA, 2, 2, 86, 87);
		Card[44] = new CardData(400, 23, 60, 31, 1, false, Atb.LIGHT, Gup.TEARSTOTIARA, 2, 2, 88, 89);
		Card[45] = new CardData(500, 50, 50, 50, 1, false, Atb.LIGHT, Gup.TEARSTOTIARA, 4, 4, 90, 91);
		Card[46] = new CardData(600, 73, 40, 31, 2, true, Atb.BEAT, Gup.TEARSTOTIARA, 2, 6, 92, 93);
		
		Card[47] = new CardData(500, 27, 63, 82, 2, false, Atb.FIRE, Gup.KUSARI, 2, 6, 94, 95);
		Card[48] = new CardData(400, 43, 61, 50, 2, false, Atb.TUNDER, Gup.KUSARI, 4, 2, 96, 97);
		Card[49] = new CardData(400, 57, 59, 61, 2, false, Atb.TUNDER, Gup.KUSARI, 2, 4, 98, 99);
		Card[50] = new CardData(400, 27, 59, 49, 1, false, Atb.FIRE, Gup.KUSARI, 2, 6, 100, 101);
		Card[51] = new CardData(400, 40, 49, 91, 1, true, Atb.TUNDER, Gup.KUSARI, 4, 1, 102, 103);
		Card[52] = new CardData(600, 66, 70, 52, 2, true, Atb.FIRE, Gup.KUSARI, 2, 2, 104, 105);
		Card[53] = new CardData(800, 79, 66, 13, 3, false, Atb.BEAT, Gup.KUSARI, 7, 9, 106, 107);
		Card[54] = new CardData(500, 61, 51, 50, 1, true, Atb.BEAT, Gup.KUSARI, 2, 2, 108, 109);
		Card[55] = new CardData(700, 70, 54, 71, 2, true, Atb.BEAT, Gup.KUSARI, 2, 2, 110, 111);
		
		Card[56] = new CardData(300, 61, 43, 22, 1, true, Atb.BEAT, Gup.FULLANI, 2, 4, 112, 113);
		Card[57] = new CardData(500, 22, 71, 27, 2, false, Atb.LIGHT, Gup.FULLANI, 4, 4, 114, 115);
		Card[58] = new CardData(600, 73, 30, 50, 3, true, Atb.BEAT, Gup.FULLANI, 2, 6, 116, 117);
		Card[59] = new CardData(500, 30, 73, 40, 3, true, Atb.LIGHT, Gup.FULLANI, 2, 4, 118, 119);
		Card[60] = new CardData(300, 33, 69, 60, 2, false, Atb.TUNDER, Gup.FULLANI, 2, 4, 120, 121);
		Card[61] = new CardData(400, 61, 63, 30, 1, true, Atb.FIRE, Gup.FULLANI, 2, 2, 121, 122);
		Card[62] = new CardData(300, 20, 82, 53, 2, false, Atb.DARK, Gup.FULLANI, 6, 8, 123, 124);
		Card[63] = new CardData(700, 86, 30, 65, 3, true, Atb.BEAT, Gup.FULLANI, 2, 4, 125, 126);
		Card[64] = new CardData(600, 61, 89, 40, 3, true, Atb.DARK, Gup.FULLANI, 9, 9, 127, 128);
	
		AI = new AIData[24];

		AI[0] = new AIData(14, 7, 16, 3, "044103040000", "444055555555", 12);
		AI[1] = new AIData(28, 33, 19, 30, "4040104040400040", "4444044444444444", 12);
		
		for (int i = 2; i < 24; i++){
			AI[i] = new AIData(14, 7, 16, 3, "044103040000", "444055555555", 12);
		}
		
		Skill = new SkillData[130];

		Skill[0] = new SkillData(0, "治癒之光", Atb.BUFF, 2, 80, Pty.NONE, "使我軍HP回復", "", 4, 1);
		Skill[1] = new SkillData(0, "直傳的美味", Atb.BUFF, 3, 90, Pty.NONE, "使我軍HP大幅回復", "", 6, 1);
		Skill[2] = new SkillData(1, "鐵爪", Atb.BEAT, 1.5, 80, Pty.NONE, "給予敵方單體強力擊屬性攻擊", "", 5, 0);
		Skill[3] = new SkillData(5, "淑女的端莊", Atb.BUFF, 0, 0, Pty.INT, "使我方全體智力和腕力上升", "自身智力越高效果時間越長", 2, 1);		
		Skill[4] = new SkillData(1, "必殺電磁YOYO", Atb.BEAT, 1, 30, Pty.NONE, "給予敵方一人擊屬性傷害並提高自身腕力", "自身智力越高效果時間越長", 3, 1);
		Skill[5] = new SkillData(3, "腳踏車突擊", Atb.BEAT, 1.25, 10, Pty.NONE, "給予敵方全體擊屬性傷害", "", 5, 0);
		Skill[6] = new SkillData(1, "特效藥飲品", Atb.BEAT, 1, 30, Pty.NONE, "給予敵方一人擊屬性傷害", "有機率使其麻痺", 2, 1);
		Skill[7] = new SkillData(1, "班長之雷", Atb.TUNDER, 1, 20, Pty.NONE, "給予敵方一人雷屬性傷害", "", 2, 0);
		Skill[8] = new SkillData(1, "肘擊", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性傷害", "", 2, 0);
		Skill[9] = new SkillData(0, "集氣", Atb.BUFF, 0, 0, Pty.NONE, "使下回合自身攻擊力上升", "", 2, 1);
		Skill[10] = new SkillData(3, "當機", Atb.TUNDER, 0.8, 500, Pty.NONE, "給予敵方全體雷屬性傷害", "低機率使擊屬性以外之技能封印", 4, 0);
		Skill[11] = new SkillData(5, "超頻", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體智力上升", "自身智力越高效果時間越長", 3, 1);
		Skill[12] = new SkillData(1, "探測棒", Atb.BEAT, 1, 60, Pty.NONE, "給予敵方一人擊屬性傷害", "", 3, 1);
		Skill[13] = new SkillData(1, "鍊金術實驗", Atb.DARK, 1, 20, Pty.NONE, "給予敵方一人闇屬性傷害", "有機率使其中毒", 3, 1);
		Skill[14] = new SkillData(1, "露～☆", Atb.LIGHT, 1, 40, Pty.NONE, "給予敵方一人光屬性傷害", "", 3, 1);
		Skill[15] = new SkillData(1, "露～露露、露～", Atb.TUNDER, 1, 40, Pty.NONE, "給予敵方一人雷屬性傷害", "", 3, 1);
		Skill[16] = new SkillData(3, "蠑螈", Atb.FIRE, 1.5, 0, Pty.NONE, "給予敵方全體炎屬性傷害", "", 6, 1);
		Skill[17] = new SkillData(3, "水母", Atb.DARK, 1.25, 0, Pty.NONE, "給予敵方全體闇屬性傷害並使其速度下降", "敵方智力越低效果時間越長", 6, 1);
		Skill[18] = new SkillData(4, "守護之歌", Atb.BUFF, 0, 0, Pty.NONE, "使我方一人擊屬性耐性上升", "自身智力越高效果時間越長", 2, 1);
		Skill[19] = new SkillData(4, "毀滅之歌", Atb.BUFF, 0, 0, Pty.NONE, "使我方一人腕力上升", "自身智力越高效果時間越長", 2, 1);
		Skill[20] = new SkillData(1, "渦輪推進", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性傷害", "", 2, 0);
		Skill[21] = new SkillData(1, "過熱", Atb.FIRE, 1.25, 40, Pty.NONE, "給予敵方一人強力炎屬性傷害", "", 4, 1);
		Skill[22] = new SkillData(3, "紙板重壓", Atb.BEAT, 1, 10, Pty.NONE, "給予敵方全體擊屬性傷害", "", 4, 0);
		Skill[23] = new SkillData(3, "紙板重壓改", Atb.BEAT, 1.5, 10, Pty.NONE, "給予敵方全體強力擊屬性傷害", "", 6, 0);
		Skill[24] = new SkillData(3, "來回耳光", Atb.BEAT, 1, 0, Pty.NONE, "給予敵方全體擊屬性傷害", "", 3, 0);
		Skill[25] = new SkillData(1, "處罰", Atb.BEAT, 1, 70, Pty.NONE, "給予敵方一人強力擊屬性傷害", "有機率使其中毒", 4, 0);
		Skill[26] = new SkillData(1, "熊吉攻擊", Atb.BEAT, 1, 80, Pty.NONE, "給予敵方一人強力擊屬性傷害", "", 4, 0);
		Skill[27] = new SkillData(0, "充電", Atb.BUFF, 0, 0, Pty.NONE, "自身擊屬性之耐性上升", "自身智力越高效果時間越長", 2, 1);
		Skill[28] = new SkillData(1, "大阪燒鍋鏟", Atb.FIRE, 1, 20, Pty.NONE, "給予敵方一人火屬性傷害", "並提高自身智力", 2, 0);
		Skill[29] = new SkillData(3, "雙倍大阪燒鍋鏟", Atb.FIRE, 1.25, 0, Pty.NONE, "給予敵方全體火屬性傷害", "", 6, 0);
		Skill[30] = new SkillData(1, "身體重壓", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性傷害", "", 2, 0);
		Skill[31] = new SkillData(3, "二重三明治", Atb.BEAT, 1, 10, Pty.NONE, "給予敵方全體擊屬性傷害", "", 4, 0);
		Skill[32] = new SkillData(1, "火球術", Atb.FIRE, 1, 20, Pty.NONE, "給予敵方一人火屬性傷害", "", 2, 1);
		Skill[33] = new SkillData(3, "火焰之舞", Atb.FIRE, 1, 0, Pty.NONE, "給予敵方全體火屬性傷害", "", 4, 1);
		Skill[34] = new SkillData(3, "小麻踢擊", Atb.TUNDER, 1, 0, Pty.NONE, "給予敵方全體雷屬性傷害", "", 4, 0);
		Skill[35] = new SkillData(3, "鑽頭蹴", Atb.TUNDER, 1.25, 0, Pty.NONE, "給予敵方全體擊屬性傷害", "低機率使其麻痺", 6, 0);
		Skill[36] = new SkillData(1, "必殺飄移", Atb.DARK, 1, 20, Pty.NONE, "給予敵方一人闇屬性傷害", "", 2, 1);
		Skill[37] = new SkillData(3, "可疑的眼光", Atb.DARK, 1, 0, Pty.NONE, "給予敵方全體闇屬性傷害使其全屬性之耐性下降", "目標智力越低效果時間越長", 6, 1);
		Skill[38] = new SkillData(4, "藥術", Atb.BUFF, 0, 0, Pty.NONE, "使我軍HP大幅回復", "", 6, 1);
		Skill[39] = new SkillData(1, "毒術", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性傷害", "高機率使其中毒", 4, 1);
		Skill[40] = new SkillData(1, "猛虎之咬", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性傷害", "", 2, 0);
		Skill[41] = new SkillData(4, "咆哮", Atb.BEAT, 0, 0, Pty.NONE, "使我方一人異常狀態回復", "智力些微上升", 2, 1);
		Skill[42] = new SkillData(1, "秘傳之鐵扇", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性傷害", "低機率使其中毒", 2, 0);
		Skill[43] = new SkillData(5, "進軍之大號令", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體腕力與智力上升", "自身智力越高效果時間越長", 3, 1);
		Skill[44] = new SkillData(1, "狙擊", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性傷害", "", 2, 0);
		Skill[45] = new SkillData(1, "狙擊(愚)", Atb.BEAT, 1, 0, Pty.NONE, "給予敵方一人擊屬性傷害使其智力下降", "無法格擋，目標智力越低效果時間越長", 2, 0);
		Skill[46] = new SkillData(1, "狙擊", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性傷害", "", 2, 0);
		Skill[47] = new SkillData(1, "狙擊(破)", Atb.BEAT, 1, 0, Pty.NONE, "給予敵方一人擊屬性傷害使其擊屬性耐性下降", "無法格擋，目標智力越低效果時間越長", 2, 0);
		Skill[48] = new SkillData(1, "武刀流", Atb.BEAT, 1, 20, Pty.NONE, "給予敵方一人擊屬性傷害使其速度下降", "目標智力越低效果時間越長", 2, 0);
		Skill[49] = new SkillData(3, "雙亂舞", Atb.BEAT, 1, 1000, Pty.NONE, "給予敵方全體擊屬性傷害", "", 4, 0);
		Skill[50] = new SkillData(1, "剛劍之一擊", Atb.BEAT, 1, 80, Pty.NONE, "給予敵方一人強力擊屬性傷害", "", 4, 0);
		Skill[51] = new SkillData(0, "腕力累積", Atb.BUFF, 0, 0, Pty.NONE, "下回合自身攻擊力上升", "", 2, 1);
		Skill[52] = new SkillData(2, "白刃一閃", Atb.BEAT, 1, 10, Pty.NONE, "藉著貫通兩名敵方給予擊屬性傷害", "", 2, 0);
		Skill[53] = new SkillData(1, "刀背打擊", Atb.TUNDER, 1, 20, Pty.NONE, "給予敵方一人雷屬性傷害", "低機率使其麻痺", 2, 0);
		Skill[54] = new SkillData(1, "戒律之光", Atb.LIGHT, 1, 20, Pty.NONE, "給予敵方一人光屬性傷害", "", 2, 1);
		Skill[55] = new SkillData(5, "大神之信仰", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體異常狀態回復", "", 4, 1);
		Skill[56] = new SkillData(1, "戒律之闇", Atb.DARK, 1, 20, Pty.NONE, "給予敵方一人闇屬性傷害", "", 2, 1);
		Skill[57] = new SkillData(0, "黑羽之畏懼", Atb.BUFF, 0, 0, Pty.NONE, "下回合自身智力上升", "", 2, 1);
		Skill[58] = new SkillData(3, "淨化之黑炎", Atb.DARK, 0.8, 0, Pty.NONE, "給予敵方全體闇屬性傷害使其光屬性之耐性下降", "目標智力越低效果時間越長", 4, 1);
		Skill[59] = new SkillData(1, "始祖之力", Atb.DARK, 1.25, 30, Pty.NONE, "給予敵方一人強力闇屬性傷害使其全屬性之耐性下降", "目標智力越低效果時間越長", 6, 1);
		Skill[60] = new SkillData(2, "擊槍之刺", Atb.BEAT, 1, 20, Pty.NONE, "藉著貫通兩名敵方給予擊屬性傷害", "", 4, 0);
		Skill[61] = new SkillData(0, "精神集中", Atb.BUFF, 0, 0, Pty.NONE, "自身之全屬性之耐性大幅上升", "自身智力越高效果時間越長", 1, 1);
		Skill[62] = new SkillData(2, "擊槍之刺", Atb.BEAT, 1, 20, Pty.NONE, "藉著貫通兩名敵方給予擊屬性傷害", "", 4, 0);
		Skill[63] = new SkillData(5, "鼓舞", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體腕力上升", "自身智力越高效果時間越長", 2, 1);
		Skill[64] = new SkillData(1, "睡夢之邀請", Atb.LIGHT, 1, 30, Pty.NONE, "給予敵方一人光屬性傷害使其有機率睡眠", "目標智力越低效果時間越長", 4, 1);
		Skill[65] = new SkillData(3, "睡夢之呼吸", Atb.DEBUFF, 0, 0, Pty.NONE, "使敵方全體有機率睡眠", "目標智力越低效果時間越長", 8, 1);
		Skill[66] = new SkillData(2, "穿透之鞭", Atb.BEAT, 1, 15, Pty.NONE, "藉著貫通兩名敵方給予擊屬性傷害", "", 3, 0);
		Skill[67] = new SkillData(1, "劇毒之鞭", Atb.BEAT, 1, 60, Pty.NONE, "給予敵方一人擊屬性傷害", "使其有機率中毒", 4, 1);
		Skill[68] = new SkillData(1, "神破斬", Atb.DARK, 1, 30, Pty.NONE, "給予敵方一人闇屬性傷害", "", 2, 0);
		Skill[69] = new SkillData(5, "魔之干涉", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體智力上升", "自身智力越高效果時間越長", 3, 1);
		Skill[70] = new SkillData(0, "魔力增強", Atb.BUFF, 0, 0, Pty.NONE, "固定回合內我軍魔力增加", "自身智力越高效果時間越長", 6, 1);
		Skill[71] = new SkillData(3, "世界樹", Atb.TUNDER, 1, 0, Pty.NONE, "給予敵方全體雷屬性傷害", "低機率使擊屬性以外之技能封印", 4, 1);
		Skill[72] = new SkillData(1, "金剛斬", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性傷害", "", 2, 0);
		Skill[73] = new SkillData(0, "捨身", Atb.BUFF, 0, 0, Pty.NONE, "確實格擋對於自身後方的攻擊", "自身智力越高效果時間越長", 1, 1);
		Skill[74] = new SkillData(1, "魂之一矢", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性傷害", "無法格擋", 2, 0);
		Skill[75] = new SkillData(1, "忘卻之矢", Atb.BEAT, 1, 20, Pty.NONE, "給予敵方一人擊屬性傷害", "有機率使擊屬性以外之技能封印，無法格擋", 2, 0);
		Skill[76] = new SkillData(2, "貴光斬", Atb.BEAT, 1, 20, Pty.NONE, "藉著貫通兩名敵方給予擊屬性傷害", "", 4, 0);
		Skill[77] = new SkillData(1, "狂暴", Atb.BEAT, 1.5, 90, Pty.NONE, "給予敵方一人強力擊屬性傷害", "我軍HP些微回復", 6, 0);
		Skill[78] = new SkillData(5, "堅固化之守護", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體全耐性上升", "自身智力越高效果時間越長", 3, 1);
		Skill[79] = new SkillData(1, "阿斯托拉", Atb.LIGHT, 1, 20, Pty.NONE, "給予敵方一人雷屬性傷害", "", 2, 0);
		Skill[80] = new SkillData(1, "妖精的搖籃曲", Atb.DARK, 1.25, 60, Pty.NONE, "給予敵方一人闇屬性傷害使其有機率睡眠", "目標智力越低效果時間越長", 6, 1);
		Skill[81] = new SkillData(5, "狂熱之輪舞曲", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體腕力與智力提高,全耐性下降", "自身智力越高效果時間越長", 3, 1);
		Skill[82] = new SkillData(1, "妖精之塵", Atb.DARK, 1, 40, Pty.NONE, "給予敵方一人闇屬性傷害低機率使其睡眠", "目標智力越低效果時間越長", 4, 1);
		Skill[83] = new SkillData(3, "魔法狩獵", Atb.DEBUFF, 0, 0, Pty.NONE, "敵軍魔力下降", "", 3, 0);
		Skill[84] = new SkillData(3, "妖精射擊", Atb.TUNDER, 1.25, 20, Pty.NONE, "給予敵方全體雷屬性傷害", "低機率使其中毒", 6, 0);
		Skill[85] = new SkillData(3, "爆碎", Atb.TUNDER, 1, 1000, Pty.NONE, "予敵方全體雷屬性傷害", "", 4, 0);
		Skill[86] = new SkillData(4, "治癒之手", Atb.BUFF, 0, 0, Pty.NONE, "使我軍HP少量回復", "", 2, 1);
		Skill[87] = new SkillData(5, "背水之陣", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體腕力提高,智力下降", "自身智力越高效果時間越長", 2, 1);
		Skill[88] = new SkillData(4, "治癒之手", Atb.BUFF, 0, 0, Pty.NONE, "使我軍HP少量回復", "", 2, 1);
		Skill[89] = new SkillData(5, "記憶術", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體封印狀態解除", "自身智力越高效果時間越長", 2, 1);
		Skill[90] = new SkillData(1, "毒之秘術", Atb.LIGHT, 1, 30, Pty.NONE, "給予敵方一人光屬性傷害", "有機率中毒", 4, 1);
		Skill[91] = new SkillData(1, "忘卻之秘術", Atb.LIGHT, 1, 0, Pty.NONE, "給予敵方一人光屬性傷害", "高機率擊屬性以外之技能封印", 4, 1);
		Skill[92] = new SkillData(1, "騎士道精神", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性傷害", "", 2, 0);
		Skill[93] = new SkillData(3, "Misuterion", Atb.BEAT, 1.25, 20, Pty.NONE, "給予敵方全體擊屬性傷害", "使其擊屬性耐性下降", 6, 0);
		Skill[94] = new SkillData(1, "絕望之炎", Atb.FIRE, 1, 0, Pty.NONE, "給予敵方一人炎屬性傷害", "我軍HP越少威力越高", 2, 1);
		Skill[95] = new SkillData(5, "緊縛的喊叫", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體腕力與智力提高", "敵軍魔力越少效果越高", 6, 1);
		Skill[96] = new SkillData(1, "緊縛之麻痺", Atb.LIGHT, 1, 30, Pty.NONE, "給予敵方一人雷屬性傷害有機率使其麻痺", "敵軍魔力越少麻痺機率越高", 4, 1);
		Skill[97] = new SkillData(5, "虛榮", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體智力提高,全耐性下降", "自身智力越高效果時間越長", 2, 1);
		Skill[98] = new SkillData(0, "絕望的閃光", Atb.BUFF, 0, 0, Pty.NONE, "使自身的智力提高，我軍的HP越少效果越高", "自身智力越高效果時間越長", 2, 1);
		Skill[99] = new SkillData(3, "寶特瓶炸彈", Atb.TUNDER, 1, 500, Pty.NONE, "使敵方全體造成雷屬性攻擊", "", 4, 1);
		Skill[100] = new SkillData(1, "絕望之炎", Atb.FIRE, 1, 0, Pty.NONE, "給予敵方一人炎屬性攻擊", "我軍的HP越少威力越高", 2, 1);
		Skill[101] = new SkillData(4, "絆", Atb.BUFF, 0, 0, Pty.NONE, "固定回合內我軍魔力增加", "自身智力越高效果時間越長", 6, 1);
		Skill[102] = new SkillData(3, "PUPPY叔叔", Atb.BUFF, 0, 0, Pty.NONE, "使自身的全屬性之耐性大幅提高", "自身智力越高效果時間越長", 4, 1);
		Skill[103] = new SkillData(3, "捨身", Atb.BUFF, 0, 0, Pty.NONE, "確實格擋對於自身後方的攻擊", "自身智力越高效果時間越長", 1, 1);
		Skill[104] = new SkillData(1, "打火機", Atb.FIRE, 1, 20, Pty.NONE, "給予敵方一人炎屬性攻擊", "", 2, 1);
		Skill[105] = new SkillData(0, "決死的守護", Atb.BUFF, 0, 0, Pty.NONE, "使自身的擊屬性耐性大幅提高", "自身智力越高效果時間越長", 2, 1);
		Skill[106] = new SkillData(1, "突刺", Atb.BEAT, 2, 100, Pty.NONE, "給予敵方一人強力擊屬性攻擊", "", 7, 0);
		Skill[107] = new SkillData(3, "切割", Atb.BEAT, 1.5, 30, Pty.NONE, "給予敵方全體擊屬性攻擊", "", 9, 0);
		Skill[108] = new SkillData(1, "玻璃棒", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性攻擊", "無法格擋", 2, 0);
		Skill[109] = new SkillData(5, "緊急避難", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體的速度提高", "自身智力越高效果時間越長", 2, 1);
		Skill[110] = new SkillData(1, "菜刀", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方一人擊屬性攻擊", "", 2, 0);
		Skill[111] = new SkillData(0, "絕望的守護", Atb.BUFF, 0, 0, Pty.NONE, "使自身的擊屬性耐性提高，我軍的HP越少效果越高", "自身智力越高效果時間越長", 2, 1);
		Skill[112] = new SkillData(1, "力量攻擊", Atb.BEAT, 1, 20, Pty.NONE, "給予敵方一人擊屬性攻擊並使其全屬性耐性下降", "目標智力越低效果時間越長", 2, 1);
		Skill[113] = new SkillData(3, "力量之風", Atb.BEAT, 1, 500, Pty.NONE, "給予敵方全體擊屬性攻擊", "", 4, 1);
		Skill[114] = new SkillData(1, "淨化術", Atb.LIGHT, 1, 20, Pty.NONE, "給予敵方一人光屬性攻擊", "消除其屬性上升效果", 4, 1);
		Skill[115] = new SkillData(1, "閃光術", Atb.LIGHT, 1, 60, Pty.NONE, "給予敵方一人強力光屬性攻擊", "", 4, 0);
		Skill[116] = new SkillData(0, "強化", Atb.BUFF, 0, 0, Pty.NONE, "下回合自身攻擊力上升", "", 2, 1);
		Skill[117] = new SkillData(3, "突擊斬", Atb.BEAT, 1.25, 10, Pty.NONE, "給予敵方全體強力擊屬性攻擊", "", 6, 0);
		Skill[118] = new SkillData(4, "防護術", Atb.BUFF, 0, 0, Pty.NONE, "使我方一人全屬性耐性提高", "自身智力越高效果時間越長", 2, 1);
		Skill[119] = new SkillData(5, "治療術", Atb.BUFF, 0, 0, Pty.NONE, "使我方全體異常狀態回復", "", 4, 1);
		Skill[120] = new SkillData(1, "落雷術", Atb.LIGHT, 1, 20, Pty.NONE, "給予敵方單體雷屬性攻擊", "", 2, 0);
		Skill[121] = new SkillData(3, "火花", Atb.LIGHT, 0.8, 10, Pty.NONE, "給予敵方全體雷屬性攻擊", "", 4, 0);
		Skill[122] = new SkillData(1, "火焰之咬", Atb.FIRE, 1, 20, Pty.NONE, "給予敵方單體炎屬性攻擊", "低機率使其麻痺", 2, 0);
		Skill[123] = new SkillData(3, "火息術", Atb.FIRE, 0.5, 0, Pty.NONE, "給予敵方全體炎屬性攻擊", "", 2, 1);
		Skill[124] = new SkillData(1, "暗影之觸", Atb.DARK, 1.25, 20, Pty.NONE, "給予敵方單體強力闇屬性攻擊", "", 6, 1);
		Skill[125] = new SkillData(3, "詛咒", Atb.DARK, 1.5, 10, Pty.NONE, "給予敵方全體強力闇屬性攻擊", "一定的機率使其中毒", 8, 1);
		Skill[126] = new SkillData(1, "致命一擊", Atb.BEAT, 1, 40, Pty.NONE, "給予敵方單體擊屬性攻擊並使其腕力下降", "目標智力越低效果時間越長", 2, 0);
		Skill[127] = new SkillData(3, "力量知識", Atb.BEAT, 1, 0, Pty.NONE, "給予敵方全體擊屬性攻擊並使其腕力下降", "目標智力越低效果時間越長", 4, 1);
		Skill[128] = new SkillData(3, "暗影閃光", Atb.DARK, 1.25, 50, Pty.NONE, "給予敵方單體闇屬性攻擊", "消除其屬性上升", 9, 0);
		Skill[129] = new SkillData(3, "重力", Atb.DARK, 1, 50, Pty.NONE, "給予敵方單體闇屬性攻擊", "使其全屬性下降", 9, 1);
		
		
		Model = new SkillModel[6];
		Model[0] = new SkillModel(0, true);
		Model[1] = new SkillModel(1, false);
		Model[2] = new SkillModel(2, false);
		Model[3] = new SkillModel(3, false);
		Model[4] = new SkillModel(4, true);
		Model[5] = new SkillModel(5, true);
	}

	public class CardData {
		
		public int HP;
		public int ATK;
		public int INT;
		public int SPD;
		public int DeckCount;
		public boolean Guard;
		public int Attribute;
		public int Group;
		public int SkillCost[] = new int[2];
		public int Skill[] = new int[2];
		
		CardData(int hp, int atk, int inte, int spd, int dc, boolean gd, int a, int g, int sc1, int sc2, int s1, int s2){
			HP = hp;
			ATK = atk;
			INT = inte;
			SPD = spd;
			DeckCount = dc;
			Guard = gd;
			Attribute = a;
			Group = g;
			SkillCost[0] = sc1;
			SkillCost[1] = sc2;
			Skill[0] = s1;
			Skill[1] = s2;
		}
	}
	
	public class SkillData {
		public int Model;
		public String Name;
		public int Attribute;
		public double Value;
		public int Root;
		public int Source;
		public String[] Comment = new String[2];
		public int Cast;
		public int Effect;
		
		SkillData(int m, String n, int a, double v, int r, int s, String c1, String c2, int c, int e) {
			Model = m;
			Name = n;
			Attribute = a;
			Value = v;
			Root = r;
			Source = s;
			Comment[0] = c1;
			Comment[1] = c2;
			Cast = c;
			Effect = e;
		}
	}
	
	public class SkillModel{
		public int TargetAmount;
		public boolean Buff;
		
		SkillModel(int ta, boolean b){
			TargetAmount = ta;
			Buff = b;
		}
	}
	
	public class AIData {
		
		public int[] Deck = new int[4];
		public String Skill;
		public String Target;
		public int MP;
		
		AIData (int d1, int d2, int d3, int d4, String s, String t, int mp){
			Deck[0] = d1;
			Deck[1] = d2;
			Deck[2] = d3;
			Deck[3] = d4;
			Skill = s;
			Target = t;
			MP = mp;
		}
	}

}
