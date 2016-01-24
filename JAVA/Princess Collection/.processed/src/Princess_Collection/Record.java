package Princess_Collection;

import java.util.*;

class Record{

	private int[] Deck = new int[4];
	private int DeckCount = 0;
	private int DeckHP = 0;
	private int DeckMP = 0;
	private int DectNum = 0;
	public GameData data;
	public DeckData DeckSelf;
	public DeckDataOpp DeckOpp;

	public int Turn;

	private Random rdm;
	public Event[] EventStack;
	public int EventStackTop;
	private int AILoc;
	public int[] Damage = new int[4];
	public int TotalDamage;
	public int TempHP;

	Record(GameData d) {
		data = d;
	}
	
	public class Event {
		public int Speed;
		public int Skill;
		public int Caster;
		public int CasterLoc;
		public int TargetAmount;
		public int[] Target;
		public boolean Self;
		public boolean Buff;
		
		Event(int s, int sk, int c, int n, int ta, int[] t, boolean sf, boolean bf){
			Speed = s;
			Skill = sk;
			Caster = c;
			CasterLoc = n;
			TargetAmount = ta;
			Target = t;
			Self = sf;
			Buff = bf;
		}
	}
	
	public class DeckData {
		public int[] Card = new int[4];
		public boolean[] CardDone = new boolean[4];
		public int MaxHP;
		public int HP;
		public int MaxMP;
		public int MP;
		public int TempMP;
		
		DeckData(int[] c, int mh, int mm){
			Card = c;
			MaxHP = mh;
			HP = mh;
			MaxMP = mm;
			MP = 0;
			TempMP = 0;
			for(int i = 0; i < 4; i++){
				CardDone[i] = false;
			}
		}
	}
	
	public class DeckDataOpp extends DeckData{
		public int DeckAI;
		public int Target;

		DeckDataOpp(int[] c, int mh, int mm, int ai) {
			super(c, mh, mm);
			DeckAI = ai;
			Target = -1;
		}
	}
	
	public void init(){
		for (int i = 0; i < 4; i++) Deck[i] = -1;
		DeckCount = 0;
		DectNum = 0;
		DeckHP = 0;
		DeckMP = 0;
		rdm = new Random();
	}
	
	public void EventInit(){
		for (int i = 0; i < 4; i++) Damage[i] = 0;
		TotalDamage = 0;
	}
	
	public void TurnInit(){
		for(int i = 0; i < 4; i++) DeckSelf.CardDone[i] = false;
		Turn++;
		EventInit();
	}
	
	public void CalcDamage(){
		if (!EventStack[EventStackTop].Buff){
			int sk = EventStack[EventStackTop].Skill;
			for (int i = 0; i < 4; i ++) {
				if (EventStack[EventStackTop].Target[i] != -1) {
					int c;
					if (EventStack[EventStackTop].Self) c = DeckOpp.Card[EventStack[EventStackTop].Target[i]];
					else c = DeckSelf.Card[EventStack[EventStackTop].Target[i]];
					int atk;
					if (data.Skill[sk].Attribute == GameData.Atb.BEAT) {
						atk = (int) (data.Skill[sk].Root + data.Card[EventStack[EventStackTop].Caster].ATK * data.Skill[sk].Value);
						if (data.Card[c].Attribute == GameData.Atb.BEAT) atk = (int) (atk * 0.5);
					}
					else {
						atk = (int) (data.Skill[sk].Root + data.Card[c].INT * data.Skill[sk].Value);
						if (data.Card[c].Attribute == GameData.Atb.BEAT) atk = (int) (atk * 1.25);
						else if ((data.Card[c].Attribute == GameData.Atb.DARK && data.Skill[sk].Attribute == GameData.Atb.LIGHT)
								|| (data.Card[c].Attribute == GameData.Atb.LIGHT && data.Skill[sk].Attribute == GameData.Atb.DARK)
								|| (data.Card[c].Attribute == GameData.Atb.FIRE && data.Skill[sk].Attribute == GameData.Atb.TUNDER)
								|| (data.Card[c].Attribute == GameData.Atb.TUNDER && data.Skill[sk].Attribute == GameData.Atb.FIRE)){
							atk = (int) (atk * 2.0);
						}
					}
					Damage[EventStack[EventStackTop].Target[i]] = atk;
					TotalDamage += atk;
				}
			}
		} else {
			for (int i = 0; i < 4; i ++) {
				if (EventStack[EventStackTop].Target[i] != -1) {
					Damage[EventStack[EventStackTop].Target[i]] = -2;
				}
			}
		}
		if (EventStack[EventStackTop].Self) TempHP = DeckOpp.HP - TotalDamage;
		else TempHP = DeckSelf.HP - TotalDamage;
		
		if (TempHP < 0) TempHP = 0;
	}
	
	public void AddEvent(int sk, int c, int ta, int[] t, int n){
		int s = data.Card[c].SPD + (rdm.nextInt() % 5);
		EventStack[++EventStackTop] = new Event(s, sk, c, n, ta, t, true, data.Model[data.Skill[sk].Model].Buff);
		DeckSelf.CardDone[n] = true;
		DeckSelf.TempMP -= data.Skill[sk].Cast;
	}
	
	public void RemoveEvent(){
		DeckSelf.CardDone[EventStack[EventStackTop].CasterLoc] = false;
		DeckSelf.TempMP += data.Skill[EventStack[EventStackTop].Skill].Cast;
		EventStack[EventStackTop--] = null;
	}
	
	public void AIEvent(){
		for (int i = 0; i < 4; i++) {
			int sk = data.AI[DeckOpp.DeckAI].Skill.charAt(AILoc) - 48;
			if (sk != 4) {
				if (sk == 3) sk = (rdm.nextInt() >>> 1) % 1;
				int c = DeckOpp.Card[i];
				sk = data.Card[c].Skill[sk];
				
				int ta = getTargetAmount(sk);
				int[] t = new int[4];
				for(int j = ta; j < 4; j++) t[j] = -1;
				t[0] = data.AI[DeckOpp.DeckAI].Target.charAt(AILoc) - 48;
				
				if (t[0] == 5) {
					if (DeckOpp.Target == -1) DeckOpp.Target = (rdm.nextInt() >>> 1) % 4;
					t[0] = DeckOpp.Target;
				} else if (t[0] == 4) t[0] = (rdm.nextInt() >>> 1) % 4;
				
				switch (ta){
				case 1:
					break;
				case 2:
					if (t[0] == 0 || t[0] == 1) {
						t[0] = 0;
						t[1] = 1;
					} else if (t[0] == 2 || t[0] == 3) {
						t[0] = 2;
						t[1] = 3;
					}
					break;
				case 4:
					t[0] = 0;
					t[1] = 1;
					t[2] = 2;
					t[3] = 3;
					break;
				}
				
				int s = data.Card[c].SPD + (rdm.nextInt() % 5);
				EventStack[++EventStackTop] = new Event(s, sk, c, i, ta, t, false, data.Model[data.Skill[sk].Model].Buff);
			}
			AILoc++;
			if (AILoc == data.AI[DeckOpp.DeckAI].Skill.length()) AILoc = 0;
		}
		
		Event temp = null;
		for (int i = 0; i < EventStackTop + 1; i++){
			for (int j = i; j < EventStackTop + 1; j++){
				if (EventStack[j].Speed < EventStack[i].Speed) {
					temp = EventStack[j];
					EventStack[j] = EventStack[i];
					EventStack[i] = temp;
				}
			}
		}
	}
	
	public void DeckSelfInit(){
		DeckSelf = new DeckData(Deck, DeckHP, DeckMP);
		Turn = 0;
		EventStackTop = -1;
		EventStack = new Event[8];
		for (int i = 0; i < 8; i++) EventStack[i] = null;
		for (int i = 0; i < 4; i++) Damage[i] = 0;
		TotalDamage = 0;
	}
	
	public void DeckOppInit(int ai){
		int hp = 0, mp = 0;
		for (int i = 0; i < 4; i++) hp += data.Card[data.AI[ai].Deck[i]].HP;

		mp = data.AI[ai].MP;
		DeckOpp = new DeckDataOpp(data.AI[ai].Deck, hp, mp, ai);
		AILoc = 0;
	}
	
	public void setDeck(int pos, int card){
		
		if (Deck[pos] != -1) removeDeck(pos);
		
		if (DectNum > 0){
			boolean same = false;
			for (int i = 0; i < 4; i++){
				if (Deck[i] != -1 && data.Card[card].Group == data.Card[Deck[i]].Group) same = true;
			}
			if (!same && DeckMP > 6) DeckMP -= 3;
		} else {
			DeckMP = 12;
		}
		
		Deck[pos] = card;
		DeckCount += data.Card[card].DeckCount;
		DeckHP += data.Card[card].HP;
		DectNum++;
		
	}
	
	public void removeDeck(int pos){

		boolean empty = true;
		boolean same = false;
		for (int i = 0; i < 4; i++){
			if (Deck[i] != -1 && i != pos){
				empty = false;
				if (data.Card[Deck[pos]].Group == data.Card[Deck[i]].Group){
					same = true;
				}
			}
		}
		if (empty) DeckMP = 0;
		else if (!same) DeckMP += 3;
		
		DeckCount -= data.Card[Deck[pos]].DeckCount;
		DeckHP -= data.Card[Deck[pos]].HP;
		Deck[pos] = -1;
		DectNum--;
	}

	public int getDeck(int pos){
		return Deck[pos];
	}

	public int getDectNum(){
		return DectNum;
	}
	
	public int getDeckCount(){
		return DeckCount;
	}

	public int getDeckHP(){
		return DeckHP;
	}
	
	public int getDeckMP(){
		return DeckMP;
	}
	
	public int getTarget(int s) {
		return data.Model[data.Skill[s].Model].TargetAmount;
	}

	public int getTargetAmount(int s) {
		switch(getTarget(s)){
		case 0:
		case 1:
		case 4:
			return 1;
		case 2:
			return 2;
		case 3: 
		case 5:
			return 4;
		}
		return 0;
	}
}
