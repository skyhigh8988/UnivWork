package Princess_Collection;

import javax.microedition.lcdui.*;
import javax.microedition.lcdui.game.GameCanvas;
import java.io.IOException;

public class Graphic extends GameCanvas implements Runnable {
	
	//TESTTING
	private int  Mode = 1;
	
	//PATH
	public class Path {
		private static final String PathTitle = "/TITLE.png";
		private static final String PathTBackGround = "/bg/BG_";
		private static final String PathCardSmall = "/cards/CARD_S_";
		private static final String PathCardLarge = "/cards/CARD_L_";
		private static final String PathCardReverse = "/cards/CARD_R_";
		private static final String PathStuff = "/stuff/STUFF_";
		private static final String PathStage = "/stage/STAGE_";
		private static final String PathStand = "/stand/STAND_";
	}
	
	//STRINGS
	private static final String[] OptionTitle = {"Start", "Option", "Exit"};
	public static final String[] Target = {"自身", "敵方單體", "敵方貫通", "敵方全體", "我方單體", "我方全體"};
	
	//SCREEN
	public class Screen {
		public static final int TITLE = 0;
		public static final int STAGE_SELECT = 1;
		public static final int CARD_SELECT = 2;
		public static final int CARD_DETAIL = 3;
		public static final int CARD_PLACE = 4;
		public static final int BATTLE_FIELD = 5;
		public static final int LOADING = 6;
		public static final int BATTLE_ATTCK = 7;
		public static final int REPORT = 8;
	}
	private int screen;
	private int lastscreen;
	
	//POSITION
	public static class Position {
		public final static int[][] PosSelf = {{60, 23}, {141, 23}, {60, 133}, {141, 133}, {349, 23}, {268, 23}, {349, 133}, {268, 133}};
		public final static int[][] PosOpp = {{349, 23}, {268, 23}, {349, 133}, {268, 133}};
	}
	
	//CLASS
	private Main main;
	private Record record;
	
	//COLOR
	private static final int ColorUnselect = 0x91b4d7;
	private static final int ColorSelect = 0xffffff;
	private static final int[] ColorHealth = {0x2e2e2e, 0xd75635, 0xf1d32f, 0x26cb64, 0x318ae5, 0x318ae5};
	private static final int[] ColorEffect = {0x00cccc, 0xff3300, 0x0099ff, 0xffffcc, 0x333333, 0x66ff66, 0xcc66ff};
	private Font f;

	//NAVIGATION
	private int NavSelect1 = 0;
	private int NavSelect2 = 0;
	private int NavPage = 0;
	private int OptSelect = 0;
	private int CardSelect = 0;
	private int TempSelect = 0;
	private int[] TargetSelect = new int[4];
	
	//BATTLE FLOW
	public class Flow {
		public static final int STANDBY = 0;
		public static final int SKILLSELECT = 1;
		public static final int TARGETSELEST = 2;
		public static final int BATTLE = 3;
	}
	private int flow = 0;
	
	//ANIME VARIBLE
	private boolean anime = false;
	private boolean flag = false;
	private int Step = 0;
	private int Frame = 0;
	private int State = 0; 
	
	//IMAGES
	private Image[] CardList = new Image[65];
	private boolean[] CardUsed = new boolean[65]; 
	
	private Image img = null, bg = null, stuff1 = null, stuff2 = null, temp = null;
	private Image MaskBlack = null, MaskRed = null, MaskGreen = null;
	private Image[] DeckSelf = new Image[4];
	private Image[] DeckOpp = new Image[4];
	private Image[] StandSelf = new Image[4];
	private Image[] StandOpp = new Image[4];
	
	//THREAD
	private Thread thread;

	public Graphic(Main m, Record r) {
		super(false);
		setFullScreenMode(true);
		
		main = m;
		record = r;
	}

    public void init() {
    	record.init();
    	
    	screen = Screen.TITLE;
    	try {
    		img = Image.createImage(Path.PathTitle);
    		bg = Image.createImage(Path.PathTBackGround + "00.png");
    	} catch (IOException e) { }
    	
    	NavSelect1 = 0;
    	repaint();
    }
    
    public void destroy() {
        hideNotify();
    }
    
    public void callKey(int k) {
    	keyPressed(getKeyCode(k));
    }

    protected void keyRepeated(int keyCode) {
        int action = getGameAction(keyCode);
        switch (action) {
        case Canvas.LEFT:
        case Canvas.RIGHT:
        case Canvas.UP:
        case Canvas.DOWN:
            keyPressed(keyCode);
            break;
        default:
            break;
        }
    }
    
    protected void keyPressed(int keyCode) {
    	int action = getGameAction(keyCode);
    	
    	System.out.println(getKeyName(keyCode));
    	
    	if(!anime) {
			switch(screen) {
			case Screen.TITLE:
		        switch (action) {
		        case Canvas.DOWN:
		        	if (NavSelect1 < 2) NavSelect1++;
		            break;
		        case Canvas.UP:
		        	if (NavSelect1 > 0) NavSelect1--;
		            break;
		        case Canvas.FIRE:
		        	switch (NavSelect1) {
		        	case 0:
		        		
		        		img = null;
		        		NavSelect1 = 0;
		        		screen = Screen.STAGE_SELECT;
		            	try {
		            		bg = Image.createImage(Path.PathTBackGround + "00.png");
		            		stuff1 = null;
		            		img = Image.createImage(Path.PathStage + "01.png");
		            		stuff2 = Function.FadeImage(Image.createImage(Path.PathStage + "02.png"), 0xFF, -0x90);
		            	} catch (IOException e) { }
		            	
		        		break;
		        	case 1:
		        		
		        		break;
		        	case 2:
		        		main.notifyDestroyed();
		        	}
		            break;
		        default:
		            return;
		        }
		        repaint();
		        break;
			case Screen.STAGE_SELECT:
				switch (action) {
				case Canvas.UP:
					if (NavSelect1 > 0) {
						NavSelect1--;
		            	try {
		            		if (NavSelect1 < 1) stuff1 = null;
		            		else stuff1 = Function.FadeImage(Image.createImage(Path.PathStage + Function.AddZero(NavSelect1, 2) + ".png"), -0x90, 0xFF);
		            		img = Image.createImage(Path.PathStage + Function.AddZero(NavSelect1 + 1, 2) + ".png");
		            		stuff2 = Function.FadeImage(Image.createImage(Path.PathStage + Function.AddZero(NavSelect1 + 2, 2) + ".png"), 0xFF, -0x90);
		            	} catch (IOException e) { }
					}
					break;
					
				case Canvas.DOWN:
					if (NavSelect1 < 23) {
						NavSelect1++;
		            	try {
		            		stuff1 = Function.FadeImage(Image.createImage(Path.PathStage + Function.AddZero(NavSelect1, 2) + ".png"), -0x90, 0xFF);
		            		img = Image.createImage(Path.PathStage + Function.AddZero(NavSelect1 + 1, 2) + ".png");
		            		if (NavSelect1 > 22) stuff2 = null;
		            		else stuff2 = Function.FadeImage(Image.createImage(Path.PathStage + Function.AddZero(NavSelect1 + 2, 2) + ".png"), 0xFF, -0x90);
		            	} catch (IOException e) { }
					}
					break;
					
				case Canvas.GAME_B:
					break;
					
				case Canvas.FIRE:
	        		record.DeckOppInit(NavSelect1);
	        		
					img = null;
	        		NavPage = 0;
	        		NavSelect1 = 0;
	        		NavSelect2 = 0;
	        		OptSelect = 0;
	        		CardSelect = -1;
	        		screen = Screen.LOADING;
	        		
	        		for (int i = 0; i < 4; i++) DeckSelf[i] = null;
	        		
	        		anime = true;
					Step = 0;
					thread = new Thread(this, "loading");
					thread.start();
					
					break;
					
		        default:
		        	return;
				}
				repaint();
				break;
				
			case Screen.CARD_SELECT:
				switch (action) {
				case Canvas.UP:
					if (NavSelect2 > 0) {
						NavSelect2--;
						OptSelect -= 6;
					}
					else if (NavPage > 0) {
						NavPage--;
						OptSelect -= 6;
					}
					break;
					
				case Canvas.DOWN:
					if (NavSelect2 < 4 && OptSelect < 59) {
						NavSelect2++;
						OptSelect += 6;
					}
					else if (NavPage < 6) {
						NavPage++;
						if (OptSelect < 59) OptSelect += 6;
						else NavSelect2--;
					}
					break;
					
				case Canvas.LEFT:
					if (NavSelect1 > 0) {
						NavSelect1--;
						OptSelect--;
					}
					break;
					
				case Canvas.RIGHT:
					if (NavSelect1 < 5 && OptSelect < 64) {
						NavSelect1++;
						OptSelect++;
					} else {
						screen = Screen.CARD_PLACE;
						NavSelect1 = 0;
					}
					break;
					
				case Canvas.GAME_B:
				case Canvas.GAME_D:
					screen = Screen.CARD_DETAIL;
					lastscreen = Screen.CARD_SELECT;
					CardSelect = OptSelect;
					try {
			    		img = Image.createImage(Path.PathCardLarge + Function.AddZero(CardSelect, 3)+ ".png");
			    	} catch (IOException e) { }

					Step = 0;
					State = 1;
					break;
					
				case Canvas.FIRE:
					if(!(CardUsed[OptSelect] || record.data.Card[OptSelect].DeckCount > 9 - record.getDeckCount() || (record.getDectNum() == 3 && record.data.Card[OptSelect].DeckCount > 8 - record.getDeckCount()) || (record.getDectNum() == 2 && record.data.Card[OptSelect].DeckCount > 7 - record.getDeckCount()) || record.getDectNum() == 4)) {
						CardUsed[OptSelect] = true;
						screen = Screen.CARD_PLACE;
						try {
		            		bg = Image.createImage(Path.PathTBackGround + "01.png");
		            		img = Function.AlphaImage(Image.createImage(Path.PathCardSmall + Function.AddZero(OptSelect, 3) + ".png"), 0x90000000);
		            	} catch (IOException e) { }
		            	NavSelect1 = 0;
		            	CardSelect = OptSelect;
					}
					break;
					
		        default:
		            return;
				}
				repaint();
				break;
				
			case Screen.CARD_PLACE:
				switch (action) {
				case Canvas.UP:
					if (NavSelect1 > 1) NavSelect1 -= 2;
					break;
					
				case Canvas.DOWN:
					if (NavSelect1 < 2) NavSelect1 += 2;
					else if(record.getDectNum() == 4) NavSelect1 = 4;
					break;
					
				case Canvas.LEFT:
					if (NavSelect1 == 1 || NavSelect1 == 3) NavSelect1--;
					else if (NavSelect1 != 4) {
						screen = Screen.CARD_SELECT;
						NavSelect1 = 5;
						
						if (NavSelect2 == 4 && NavPage == 6) NavSelect1 = 4;
						if (CardSelect != -1){
							img = null;
							CardUsed[CardSelect] = false;
							CardSelect = -1;
							OptSelect = NavSelect1 + NavSelect2 * 6 + NavPage * 6;
						}
					}
					break;
					
				case Canvas.RIGHT:
					if (NavSelect1 == 0 || NavSelect1 == 2) NavSelect1++;
					break;
					
				case Canvas.GAME_B:
				case Canvas.GAME_D:
					if (NavSelect1 != 4 && record.getDeck(NavSelect1) != -1 && CardSelect == -1){
						
						screen = Screen.CARD_DETAIL;
						lastscreen = Screen.CARD_PLACE;
						CardSelect = record.getDeck(NavSelect1);
						try {
				    		img = Image.createImage(Path.PathCardLarge + Function.AddZero(CardSelect, 3)+ ".png");
				    	} catch (IOException e) { }

						Step = 0;
						State = 1;
					}

					break;
					
				case Canvas.GAME_A:
				case Canvas.GAME_C:
					
					if (CardSelect != -1){
						screen = Screen.CARD_SELECT;
						img = null;
						CardUsed[CardSelect] = false;
						CardSelect = -1;
						NavSelect1 = OptSelect % 6;;
					}

					break;
					
				case Canvas.FIRE:
					if (CardSelect != -1) {
						
						try {
							DeckSelf[NavSelect1] = Image.createImage(Path.PathCardSmall + Function.AddZero(CardSelect, 3) + ".png");
						} catch (IOException e) { }
	
						int tmp = record.getDeck(NavSelect1);
						record.setDeck(NavSelect1, CardSelect);

						if (tmp == -1) {
							
							CardSelect = -1;
							img = null;
							
							if (record.getDectNum() == 4) NavSelect1 = 4;
							else{
								anime = true;
								Step = 5;
								thread = new Thread(this, "delay");
								thread.start();
							}
						}
						else {
							
							try {
								img = Function.AlphaImage(Image.createImage(Path.PathCardSmall + Function.AddZero(tmp, 3) + ".png"), 0x90000000);
							} catch (IOException e) { }
							
							CardSelect = tmp;
						}
						
					} else if(record.getDectNum() == 4 && NavSelect1 == 4) {
						NavPage = 0;
						NavSelect1 = 0;
						OptSelect = 0;
						record.DeckSelfInit();
						CardSelect = record.DeckSelf.Card[0];
						
						screen = Screen.LOADING;
						anime = true;
		            	Step = 0;
		            	thread = new Thread(this, "loading2");
		            	thread.start();
		            	
					} else if(record.getDeck(NavSelect1) != -1) {
						
						CardSelect = record.getDeck(NavSelect1);
						
						try {
							img = Function.AlphaImage(Image.createImage(Path.PathCardSmall + Function.AddZero(CardSelect, 3) + ".png"), 0x90000000);
						} catch (IOException e) { }
						
						record.removeDeck(NavSelect1);
						DeckSelf[NavSelect1] = null;
					}
					break;
					
		        default:
		            return;
				}
				repaint();
				break;
				
			case Screen.CARD_DETAIL:
				switch (action) {
				case Canvas.GAME_B:
				case Canvas.GAME_D:
				case Canvas.FIRE:
					anime = true;
					Step = 0;
					Frame = 0;
					thread = new Thread(this, "reverse");
					thread.start();
					break;
				case Canvas.GAME_A:
				case Canvas.GAME_C:
					img = null;
					if (lastscreen != Screen.BATTLE_FIELD) CardSelect = -1;
					screen = lastscreen;
					repaint();
					break;
		        default:
		            return;
		        }
				break;
				
			case Screen.BATTLE_FIELD:
				switch (action) {
				case Canvas.UP:
					if (flow == Flow.STANDBY || (flow == Flow.TARGETSELEST && record.getTarget(OptSelect) != 0)){
						if(NavSelect1 == 2 || NavSelect1 == 3) {
							NavSelect1 -= 2;
							CardSelect = record.DeckSelf.Card[NavSelect1];
							if(record.getTarget(OptSelect) == 4) TargetSelect[0] = NavSelect1;
						} else if(NavSelect1 == 6 || NavSelect1 == 7) {
							NavSelect1 -= 2;
							CardSelect = record.DeckOpp.Card[NavSelect1 - 4];
							if(record.getTarget(OptSelect) == 1) TargetSelect[0] = NavSelect1 - 4;
							else if(record.getTarget(OptSelect) == 2) {
								TargetSelect[0] = 0;
								TargetSelect[1] = 1;
							}
						} else if (NavSelect1 == 8) {
							NavSelect1 = 2;
							CardSelect = record.DeckSelf.Card[2];
						}
					} else if (flow == Flow.SKILLSELECT) {
						if(NavSelect2 == 1) {
							NavSelect2 = 0;
							OptSelect = record.data.Card[CardSelect].Skill[0];
						}
					}
					
					break;
					
				case Canvas.DOWN:
					if (flow == Flow.STANDBY || (flow == Flow.TARGETSELEST && record.getTarget(OptSelect) != 0)){
						if(NavSelect1 == 0 || NavSelect1 == 1) {
							NavSelect1 += 2;
							CardSelect = record.DeckSelf.Card[NavSelect1];
							if(record.getTarget(OptSelect) == 4) TargetSelect[0] = NavSelect1;
						} else if(NavSelect1 == 4 || NavSelect1 == 5) {
							NavSelect1 += 2;
							CardSelect = record.DeckOpp.Card[NavSelect1 - 4];
							if(record.getTarget(OptSelect) == 1) TargetSelect[0] = NavSelect1 - 4;
							else if(record.getTarget(OptSelect) == 2) {
								TargetSelect[0] = 2;
								TargetSelect[1] = 3;
							}
						} else if (flow != Flow.TARGETSELEST && (NavSelect1 == 2 || NavSelect1 == 3)) {
							NavSelect1 = 8;
							CardSelect = -1;
						}
					} else if (flow == Flow.SKILLSELECT) {
						if(NavSelect2 == 0) {
							NavSelect2 = 1;
							OptSelect = record.data.Card[CardSelect].Skill[1];
						}
					}
					
					break;
					
				case Canvas.LEFT:
					if (flow == Flow.STANDBY || (flow == Flow.TARGETSELEST && record.getTarget(OptSelect) != 0)){
						if(NavSelect1 == 1 || NavSelect1 == 3) {
							NavSelect1--;
							CardSelect = record.DeckSelf.Card[NavSelect1];
							if(record.getTarget(OptSelect) == 1) TargetSelect[0] = NavSelect1;
						} else if(NavSelect1 == 4 || NavSelect1 == 6) {
							NavSelect1++;
							CardSelect = record.DeckOpp.Card[NavSelect1 - 4];
							if(record.getTarget(OptSelect) == 1) TargetSelect[0] = NavSelect1 - 4;
						} else if(flow != Flow.TARGETSELEST && (NavSelect1 == 5 || NavSelect1 == 7)) {
							NavSelect1 -= 4;
							CardSelect = record.DeckSelf.Card[NavSelect1];

							anime = true;
							Step = 0;
							thread = new Thread(this, "toBack");
							thread.start();
						}
					}
					break;
					
				case Canvas.RIGHT:
					if (flow == Flow.STANDBY || (flow == Flow.TARGETSELEST && record.getTarget(OptSelect) != 0)){
						if(NavSelect1 == 0 || NavSelect1 == 2) {
							NavSelect1++;
							CardSelect = record.DeckSelf.Card[NavSelect1];
							if(record.getTarget(OptSelect) == 1) TargetSelect[0] = NavSelect1;
						} else if(NavSelect1 == 5 || NavSelect1 == 7) {
							NavSelect1--;
							CardSelect = record.DeckOpp.Card[NavSelect1 - 4];
							if(record.getTarget(OptSelect) == 1) TargetSelect[0] = NavSelect1 - 4;
						} else if(flow != Flow.TARGETSELEST && (NavSelect1 == 1 || NavSelect1 == 3)) {
							NavSelect1 += 4;
							CardSelect = record.DeckOpp.Card[NavSelect1 - 4];

							anime = true;
							Step = 0;
							thread = new Thread(this, "toFront");
							thread.start();
						}
					}
					break;
					
				case Canvas.GAME_B:
				case Canvas.GAME_D:
					if (NavSelect1 != 8 && flow == Flow.STANDBY){
						screen = Screen.CARD_DETAIL;
						lastscreen = Screen.BATTLE_FIELD;

						try {
				    		img = Image.createImage(Path.PathCardLarge + Function.AddZero(CardSelect, 3)+ ".png");
				    	} catch (IOException e) { }

						Step = 0;
						State = 1;
					}
					break;
					
				case Canvas.GAME_A:
				case Canvas.GAME_C:
					if (flow == Flow.SKILLSELECT) {
						flow = Flow.STANDBY;
					} else if (flow == Flow.TARGETSELEST) {
						flow = Flow.SKILLSELECT;
						NavSelect1 = TempSelect;
						CardSelect = record.DeckSelf.Card[NavSelect1];
						if (!record.data.Model[record.data.Skill[OptSelect].Model].Buff){
							anime = true;
							Step = 0;
							thread = new Thread(this, "toBack");
							thread.start();
						}
					} else if (flow == Flow.STANDBY){
						if (record.EventStackTop > -1) {
							record.RemoveEvent();
						} else {
							//SYSTEM MENU
						}
					}
					break;
					
				case Canvas.FIRE:
					if (flow == Flow.STANDBY) {
						if (NavSelect1 == 8) {
							flow = Flow.BATTLE;
							record.AIEvent();

							anime = true;
							Step = 0;
							State = 0;
							thread = new Thread(this, "toOpp");
							thread.start();
							
						} else if (NavSelect1 < 4 && !record.DeckSelf.CardDone[NavSelect1]){
							NavSelect2 = 0;
							flow = Flow.SKILLSELECT;
							OptSelect = record.data.Card[CardSelect].Skill[0];
						}
					} else if (flow == Flow.SKILLSELECT && record.data.Skill[OptSelect].Cast <= record.DeckSelf.TempMP) {
						flow = Flow.TARGETSELEST;
						TempSelect = NavSelect1;
						
						for (int i = 0; i < 4; i++) TargetSelect[i] = -1;
						if (record.getTarget(OptSelect) == 0 || record.getTarget(OptSelect) == 4) TargetSelect[0] = NavSelect1;
						else if (record.getTarget(OptSelect) == 3 || record.getTarget(OptSelect) == 5) {
							for (int i = 0; i < 4; i++) TargetSelect[i] = i;
						} else if (record.getTarget(OptSelect) == 1){
							TargetSelect[0] = 1;
						} else if (record.getTarget(OptSelect) == 2){
							TargetSelect[0] = 0;
							TargetSelect[1] = 1;
						}
						
						if (!record.data.Model[record.data.Skill[OptSelect].Model].Buff){
							NavSelect1 = 5;
							anime = true;
							Step = 0;
							thread = new Thread(this, "toFront");
							thread.start();
						}
					} else if (flow == Flow.TARGETSELEST) {
						flow = Flow.STANDBY;
						NavSelect1 = TempSelect;
						CardSelect = record.DeckSelf.Card[NavSelect1];
						record.DeckSelf.CardDone[NavSelect1] = true;
						
						int ta = 4;
						int[] t = new int[4];
						for (int i = 0; i < 4; i++) t[i] = -1;
						for (int i = 0; i < 4; i++) {
							if(TargetSelect[i] != -1) t[i] = TargetSelect[i];
							else {
								ta = i;
								break;
							}
						}
						record.AddEvent(OptSelect, CardSelect, ta, t, NavSelect1);
						
						if (!record.data.Model[record.data.Skill[OptSelect].Model].Buff){
							anime = true;
							Step = 0;
							thread = new Thread(this, "toBack");
							thread.start();
						}
					}
					break;
					
		        default:
		            return;
				}
				repaint();
				break;

			case Screen.REPORT:
				init();
			}
    	}
    }
    
	public void run() {
		
		//LOADING
		while (thread != null && thread.getName().equals("loading")) {
			
			try {
				if (Step < 65) {
					CardList[Step] = Function.ZoomImage(Image.createImage(Path.PathCardSmall + Function.AddZero(Step, 3) + ".png"), 30, 42);
	    			CardUsed[Step] = false;
				} else if (Step == 66 ) stuff1 = Image.createImage(Path.PathStuff + "01.png");
				else if (Step == 67) stuff2 = Image.createImage(Path.PathStuff + "02.png");
				else if (Step == 68) MaskBlack = Function.CreatRect(71, 100, 0x000000, 0x70);
				else if (Step == 69) MaskRed = Function.CreatRect(71, 100, 0xff0000, 0x00);
				else if (Step == 70) MaskGreen = Function.CreatRect(71, 100, 0x66ff33, 0x00);
				else if (Step == 71) bg = Image.createImage(Path.PathTBackGround + "02.png");
				else if (Step == 72) {
		        	screen = Screen.CARD_SELECT;
		        	anime = false;
		        	thread = null;
				}
			
			} catch (IOException e) { }
			
			Step++;
			repaint();
			
			try {
				Thread.sleep(1);
			} catch (InterruptedException e) { }
		}

		//LOADING2
		while (thread != null && thread.getName().equals("loading2")) {
			
			try {
				if (Step == 0) {
					for (int i = 0; i < CardList.length; i++) CardList[i] = null;
				} else if (Step == 1 ) {
					img = null;
					stuff1 = null;
	    	        stuff2 = null;
				} else if (Step < 6) {
					DeckOpp[Step - 2] = Image.createImage(Path.PathCardSmall + Function.AddZero(record.DeckOpp.Card[Step - 2], 3) + ".png");
				} else if (Step < 10) {
					StandSelf[Step - 6] = Image.createImage(Path.PathStand + Function.AddZero(record.DeckSelf.Card[Step - 6], 3) + ".png");
				} else if (Step < 14) {
					StandOpp[Step - 10] = Image.createImage(Path.PathStand + Function.AddZero(record.DeckOpp.Card[Step - 10], 3) + ".png");
				} else if (Step == 14) {
					bg = Image.createImage(Path.PathTBackGround + "03.png");
				} else if (Step == 72) {
		        	screen = Screen.BATTLE_FIELD;
					flow = Flow.STANDBY;
		        	flag = true;
	            	Step = 0;
	            	thread = new Thread(this, "toFront");
	            	thread.start();
				}
			} catch (IOException e) { }
			
			Step++;
			repaint();
			
			try {
				Thread.sleep(1);
			} catch (InterruptedException e) { }
		}
		
		//CARD REVERSE
		while (thread != null && thread.getName().equals("reverse")) {
			
			if (Step == 0) {
				try {
					if (State == 1) {
						temp = Image.createImage(Path.PathCardLarge + Function.AddZero(CardSelect, 3)+ ".png");
					} else {
						temp = Image.createImage(Path.PathCardReverse + Function.AddZero(CardSelect, 3)+ ".png");
					}
				} catch (IOException e1) { }
				
			} else if (Step == 10) {
				try {
					if (State == 1) {
						temp = Image.createImage(Path.PathCardReverse + Function.AddZero(CardSelect, 3)+ ".png");
					} else {
						temp = Image.createImage(Path.PathCardLarge + Function.AddZero(CardSelect, 3)+ ".png");
					}
				} catch (IOException e1) { }
				
			} else if (Step == 20) {
				State *= -1;
				img = temp;
				temp = null;
				thread = null;
				anime = false;
				
				repaint();
				return;
			}

			int w = (int)(195 * ((10 - Frame) / 10.0));
			if (w == 0) w = 1;
			img = Function.ZoomImage(temp, w, 275);
			
			if (Step < 10) Frame++;
			else Frame--;
			Step++;

			try {
				Thread.sleep(10);
			} catch (InterruptedException e) { }

			repaint();
		}

		//DELAY
		while (thread != null && thread.getName().equals("delay")) {
			
			Step--;
			
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) { }
			
			if (Step < 0) {
				thread = null;
				anime = false;
				screen = Screen.CARD_SELECT;
				NavSelect1 = OptSelect % 6;
				repaint();
			}
		}
		
		while (thread != null && thread.getName().equals("toFront")) {
			NavPage += 5;
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) { }
			
			if (NavPage > 239) {
				NavPage = 239;
				
				if (flag){
					Step++;
					if(Step > 10){
						Step = 0;
						thread = new Thread(this, "toBack");
						thread.start();
					}
				} else {
					thread = null;
					anime = false;
				}
			}
			repaint();
		}

		while (thread != null && thread.getName().equals("toBack")) {
			NavPage -= 5;
			
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) { }
			
			if (NavPage < 0) {
				NavPage = 0;

				if (flag){
					Step++;
					if(Step > 5){
						flag = false;
						Step = 0;
						thread = new Thread(this, "getMana");
						thread.start();
					}
				} else {
					thread = null;
					anime = false;
				}
			}
			repaint();
		}

		while (thread != null && thread.getName().equals("toCenter")) {
			NavPage += 5;
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) { }
			
			if (NavPage > 119) {
				NavPage = 119;
								
				Step = 0;
				Frame = 0;
				State = 1;
				thread = new Thread(this, "Caster");
				thread.start();
			} else repaint();
		}

		while (thread != null && thread.getName().equals("toCenter2")) {
			NavPage -= 5;
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) { }
			
			if (NavPage < 119) {
				NavPage = 119;
								
				Step = 0;
				Frame = 0;
				State = 1;
				thread = new Thread(this, "Caster");
				thread.start();
			} else repaint();
		}
		
		while (thread != null && thread.getName().equals("toOpp")) {
			
			if (State == 0 && record.EventStack[record.EventStackTop].Self) {
				Step = 0;
				record.DeckSelf.TempMP = record.DeckSelf.MP;
				thread = new Thread(this, "UseMana");
				thread.start();
				
			} else {
				
				NavPage += 5;
				try {
					Thread.sleep(10);
				} catch (InterruptedException e) { }
				
				if (NavPage > 239) {
					NavPage = 239;
					
					Step = 0;
					if (State == 0) {
						record.DeckSelf.TempMP = record.DeckSelf.MP;
						thread = new Thread(this, "UseMana");
					} else {
						Frame = 20;
						record.CalcDamage();
						screen = Screen.BATTLE_FIELD;
						thread = new Thread(this, "Damage");
					}
					thread.start();
				} else repaint();
			}
		}

		while (thread != null && thread.getName().equals("toSelf")) {
						
			if (State == 0 && !record.EventStack[record.EventStackTop].Self) {
				Step = 0;
				thread = new Thread(this, "UseMana");
				thread.start();
				
			} else {

				NavPage -= 5;
				try {
					Thread.sleep(10);
				} catch (InterruptedException e) { }
				
				if (NavPage < 0) {
					NavPage = 0;
					
					Step = 0;
					if (State == 0) {
						record.DeckSelf.TempMP = record.DeckSelf.MP;
						thread = new Thread(this, "UseMana");
					} else {
						Frame = 20;
						record.CalcDamage();
						screen = Screen.BATTLE_FIELD;
						thread = new Thread(this, "Damage");
					}
				} else repaint();
			}
		}
		
		while (thread != null && thread.getName().equals("Caster")) {
			Step++;
			if (Step < 100) {
				Frame += 2;
				repaint();
			}
			else if (Step == 100) {
				State = 2;
				if (record.EventStack[record.EventStackTop].Buff) stuff1 = Function.CreatRect(100, 20, 0x9fd3ff, 0x40);
    	        else stuff1 = Function.CreatRect(100, 20, 0xff99cc, 0x40);
				repaint();
			}
			
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) { }
			
			if (Step > 250) {
				Step = 0;
				State = 3;
				Frame = 0;
				stuff1 = null;
				thread = new Thread(this, "Target");
				thread.start();
			}
		}

		while (thread != null && thread.getName().equals("Target")) {
			
			if (Step == 0 &&record.EventStack[record.EventStackTop].Buff && record.EventStack[record.EventStackTop].TargetAmount == 1 && record.EventStack[record.EventStackTop].Target[0] == record.EventStack[record.EventStackTop].CasterLoc) Step = 100;
			
			if (Step < 100) {
				Frame +=2;
				repaint();
			} else if (Step == 100) {
					State = 4;
					Frame = 0;
					if (record.data.Skill[record.EventStack[record.EventStackTop].Skill].Effect == 0)
						stuff1 = Function.CreatRect(240, 295, ColorEffect[record.data.Skill[record.EventStack[record.EventStackTop].Skill].Attribute], 100);
					else if (record.data.Skill[record.EventStack[record.EventStackTop].Skill].Effect == 1)
						stuff1 = Function.CreatRect(240, 295, ColorEffect[record.data.Skill[record.EventStack[record.EventStackTop].Skill].Attribute], 10);
					repaint();
			} else if (Step <= 250 && Step % 10 == 0) {
				Frame++;
				repaint();
			}
			else if (Step <= 400 && Step % 10 == 0) {
				Frame--;
				repaint();
			}
			
			Step++;
			
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) { }
			
			if (Step > 500) {
				stuff1 = null;
				Step = 0;
				State = 5;
				Frame = 0;
				if ((record.EventStack[record.EventStackTop].Self && record.EventStack[record.EventStackTop].Buff) || (!record.EventStack[record.EventStackTop].Self && !record.EventStack[record.EventStackTop].Buff)) 
					thread = new Thread(this, "toSelf");
				else thread = new Thread(this, "toOpp");
				thread.start();
			}
		}

		while (thread != null && thread.getName().equals("UseMana")) {
			
			Step++;
			if (Step % 3 == 0 && Step <= record.data.Skill[record.EventStack[record.EventStackTop].Skill].Cast * 3) {
				if (record.EventStack[record.EventStackTop].Self) {
					record.DeckSelf.MP--;
					record.DeckSelf.TempMP = record.DeckSelf.MP;
				}
				else record.DeckOpp.MP--;
				repaint();
				
			} else if (Step == record.data.Skill[record.EventStack[record.EventStackTop].Skill].Cast * 3 + 20) {
				Step = 0;
				State = 0;
				screen = Screen.BATTLE_ATTCK;
				if (NavPage < 119) thread = new Thread(this, "toCenter");
				else thread = new Thread(this, "toCenter2");
				thread.start();
			}
			
			try {
				Thread.sleep(50);
			} catch (InterruptedException e) { }
		}
		
		while (thread != null && thread.getName().equals("Damage")) {
			
			if (Step <= 60){
				if (Step <= 15) Frame += 3;
				else if (Step > 30) Frame -= 2;

				if (Step % 3 == 0) {
					if (record.EventStack[record.EventStackTop].Buff) stuff1 = Function.AlphaImage(MaskGreen, Frame * 0x1000000);
					else stuff1 = Function.AlphaImage(MaskRed, Frame * 0x1000000);
				}
			} else stuff1 = null;

			Step++;
			repaint();
			
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) { }
			
			if (record.EventStack[record.EventStackTop].Self) {
				if (record.DeckOpp.HP > record.TempHP) record.DeckOpp.HP -= 3;

				if (record.DeckOpp.HP <= record.TempHP) {
					record.DeckOpp.HP = record.TempHP;
					
					if (Step > 90){
						
						if (record.DeckOpp.HP == 0) {
							flag = true;
							State = 6;
							Step = 0;

				    		img = StandSelf[record.EventStack[record.EventStackTop].CasterLoc];
					    	
							thread = new Thread(this, "End");
							thread.start();
							
						} else if (record.EventStackTop > 0) {
							record.EventInit();
							record.EventStackTop--;
							Step = 0;
							State = 0;
							thread = new Thread(this, "toSelf");
							thread.start();
							
						} else {
							flow = Flow.STANDBY;
							record.TurnInit();
							NavSelect1 = 0;
							CardSelect = record.DeckSelf.Card[0];
							OptSelect = 0;
							Step = 0;
							flag = true;
							thread = new Thread(this, "toBack");
							thread.start();
						}
					}
				}
			} else {
				if (record.DeckSelf.HP > record.TempHP) record.DeckSelf.HP -= 3;
				
				if (record.DeckSelf.HP <= record.TempHP) {
					record.DeckSelf.HP = record.TempHP;
					
					if (Step > 130){

						if (record.DeckSelf.HP == 0) {

							flag = false;
							Step = 0;
							State = 6;

					    	img = StandOpp[record.EventStack[record.EventStackTop].CasterLoc];

					    	thread = new Thread(this, "End");
							thread.start();
							
						} else if (record.EventStackTop > 0) {
							record.EventInit();
							record.EventStackTop--;
							Step = 0;
							State = 0;
							thread = new Thread(this, "toOpp");
							thread.start();
						} else {
							flow = Flow.STANDBY;
							record.TurnInit();
							NavSelect1 = 0;
							CardSelect = record.DeckSelf.Card[0];
							OptSelect = 0;
							Step = 0;
							thread = new Thread(this, "getMana");
							thread.start();
						}
					}
				}
			}
		}
		
		while (thread != null && thread.getName().equals("getMana")) {
			Step++;
			if (Step % 3 == 0){
				if (record.DeckSelf.MP < record.DeckSelf.MaxMP) record.DeckSelf.MP++;
				if (record.DeckOpp.MP < record.DeckOpp.MaxMP) record.DeckOpp.MP++;
				record.DeckSelf.TempMP = record.DeckSelf.MP;
				repaint();
			}
			
			try {
				Thread.sleep(50);
			} catch (InterruptedException e) { }

			if (Step >= 24) {
				thread = null;
				anime = false;
				record.EventStackTop = -1;
				repaint();
			}
		}

		while (thread != null && thread.getName().equals("End")) {
			Step++;
			
			if (Step == 255) {
				screen = Screen.REPORT;

		    	try {
		    		bg = Image.createImage(Path.PathTBackGround + "00.png");
		    	} catch (IOException e) { }

				repaint();
			} else if (Step < 255 && Step % 10 == 0) {
				stuff1 = Function.CreatRect(240, 295, 0x000000, Step);
				repaint();
			} else if (Step < 350 && Step % 10 == 0) {
				stuff1 = Function.CreatRect(240, 295, 0x000000, 0xFF * 2 - Step);
				repaint();
			} else if (Step >= 350) {
				for(int i = 0; i < 4; i++) {
        			DeckOpp[i] = null;
        			StandSelf[i] = null;
        			StandOpp[i] = null;
        		}
		    	
				thread = null;
				anime = false;
				repaint();
			}
			
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) { }
		}
	}
	
	public void paint(Graphics g){
		
		int cx = getWidth() / 2;
		int cy = getHeight() / 2;
		int cl = Graphics.HCENTER | Graphics.VCENTER;
    	int c;
    	int bh;
    	String str;
		switch(screen) {
		case Screen.TITLE:
	    	
	    	//BACKGROUND
			g.setColor(0x000000);
	        g.fillRect(0, 0, getWidth(), getHeight());
	        if(bg != null) g.drawImage(bg, cx, cy, cl);
	    	
	        //TITLE
	        if(img != null) g.drawImage(img, cx, cy - 50, cl);
	        
	        //MENU
        	f = Font.getFont(Font.FACE_SYSTEM, Font.STYLE_BOLD, Font.SIZE_LARGE);
        	g.setFont(f);
	        g.setColor(NavSelect1 == 0 ? ColorSelect : ColorUnselect);
	        g.drawString(OptionTitle[0], cx - f.stringWidth(OptionTitle[0]) / 2, cy + 30, Graphics.LEFT | Graphics.TOP);
	        g.setColor(NavSelect1 == 1 ? ColorSelect : ColorUnselect);
	        g.drawString(OptionTitle[1], cx - f.stringWidth(OptionTitle[1]) / 2, cy + 50, Graphics.LEFT | Graphics.TOP);
	        g.setColor(NavSelect1 == 2 ? ColorSelect : ColorUnselect);
	        g.drawString(OptionTitle[2], cx - f.stringWidth(OptionTitle[2]) / 2, cy + 70, Graphics.LEFT | Graphics.TOP);
	        
	        break;
	        
		case Screen.STAGE_SELECT:

	    	//BACKGROUND
			g.setColor(0x000000);
	        g.fillRect(0, 0, getWidth(), getHeight());
	        if(bg != null) g.drawImage(bg, cx, cy, cl);
	    		        
	        //MENU
	        if(stuff1 != null) g.drawImage(stuff1, cx, cy - 130, cl);
	        if(img != null) g.drawImage(img, cx, cy, cl);
	        if(stuff2 != null) g.drawImage(stuff2, cx, cy + 130, cl);
	        
	        g.fillRect(0, 0, getWidth(), (getHeight() - 295) / 2);
	        g.fillRect(0, (getHeight() + 295) / 2, getWidth(), (getHeight() - 295) / 2);
	        
			break;
			
		case Screen.CARD_SELECT:

	    	//BACKGROUND
			g.setColor(0x000000);
	        g.fillRect(0, 0, getWidth(), getHeight());
	        if(bg != null) g.drawImage(bg, cx, cy, cl);
	    	
	        //DECKCOUNT BAR
	        for (int i = 0; i < 8; i++) {
		        if (record.getDeckCount() > i) {
		        	g.setColor(0xffcc66);
		        	g.fillRect(58 + i * 16, cy - 135, 10, 10);
		        	g.setColor(0xffffcc);
		        	g.drawRect(58 + i * 16, cy - 135, 10, 10);
		        }
		        else {
		        	g.setColor(0x251c16);
		        	g.fillRect(58 + i * 16, cy - 135, 10, 10);
		        	g.setColor(0x716357);
		        	g.drawRect(58 + i * 16, cy - 135, 10, 10);
		        }
	        }
	        
	        //CARD
	        for (int i = 0, j = 0, k = 0, t = NavPage * 6; i < 30; j = ++i / 6, k = i % 6, t = i + NavPage * 6) {
	        	if(t < 65 && CardList[t] != null){
		            g.drawImage(CardList[t], k * 34 + 20, cy - 145 + j * 48 + 30, Graphics.LEFT | Graphics.TOP);
		            if((CardUsed[t] || record.data.Card[t].DeckCount > 9 - record.getDeckCount() || (record.getDectNum() == 3 && record.data.Card[t].DeckCount > 8 - record.getDeckCount()) || (record.getDectNum() == 2 && record.data.Card[t].DeckCount > 7 - record.getDeckCount()) || record.getDectNum() == 4) && MaskBlack != null) {
		            	g.drawImage(MaskBlack, k * 34 + 20, cy - 145 + j * 48 + 30, Graphics.LEFT | Graphics.TOP);
		            }
		            if(NavSelect1 == k && NavSelect2 == j) {
		            	g.setColor(0xffc000);
		            	g.drawRoundRect(k * 34 + 20, cy - 145 + j * 48 + 30, 30, 42, 5, 5);
		            	g.drawRoundRect(k * 34 + 19, cy - 145 + j * 48 + 29, 32, 44, 7, 7);
		            }
		        }
	        }
	        
			break;
			
		case Screen.CARD_PLACE:

	    	//BACKGROUND
			g.setColor(0x000000);
	        g.fillRect(0, 0, getWidth(), getHeight());
	        if(bg != null) g.drawImage(bg, cx, cy, cl);
	    	
	        //CHAR
        	if(stuff1 != null) g.drawImage(stuff1, 215, cy - 145 + 105, Graphics.LEFT | Graphics.TOP);
        	if(stuff2 != null) g.drawImage(stuff2, 48, cy - 145 + 105, Graphics.LEFT | Graphics.TOP);
        	
        	//BAR
        	c = record.getDeckHP() / 500;
        	bh = record.getDeckHP() % 500 * 240 / 500;
        	if(c > 5) c = 5;
		    g.setColor(ColorHealth[c]);
        	g.fillRect(10, cy - 145 + 20, 17, 240);
		    g.setColor(ColorHealth[c + 1]);
        	g.fillRect(10, cy - 145 + 260 - bh, 17, bh);
		    g.setColor(0x232121);
        	g.drawRect(10, cy - 145 + 20, 17, 240);
        	g.drawRect(12, cy - 145 + 22, 13, 236);
		    g.setColor(0xc6b889);
        	g.drawRect(11, cy - 145 + 21, 15, 238);
        	str = record.getDeckHP() + "";
		    g.setColor(0xffffff);
	        g.drawString(str, 22 - f.stringWidth(str) / 2, cy - 145 + 265, Graphics.LEFT | Graphics.TOP);
	        
	        for(int i = 0; i < record.getDeckMP(); i++){
			    g.setColor(0xffc277);
		        g.fillArc(30, cy - 145 + 240 - i * 18, 14, 14, 0, 360);
			    g.setColor(0x482410);
		        g.drawArc(31, cy - 145 + 241 - i * 18, 12, 12, 0, 360);
			    g.setColor(0xfaf5ee);
		        g.drawArc(30, cy - 145 + 240 - i * 18, 14, 14, 0, 360);
	        }
        	
	        //BORDER
        	g.setColor(0x8d9caa);
        	for(int i = 0; i < 4; i++){
            	g.drawRoundRect(Position.PosSelf[i][0] - 1, cy - 145 + Position.PosSelf[i][1] - 1, 72, 101, 10, 10);
            	g.drawRoundRect(Position.PosSelf[i][0] - 2, cy - 145 + Position.PosSelf[i][1] - 2, 74, 103, 14, 14);
        		if(DeckSelf[i] != null) g.drawImage(DeckSelf[i], Position.PosSelf[i][0], cy - 145 + Position.PosSelf[i][1], Graphics.LEFT | Graphics.TOP);
        	}
        	
        	g.setColor(0xffc000);
        	if(img != null) g.drawImage(img, Position.PosSelf[NavSelect1][0], cy - 145 + Position.PosSelf[NavSelect1][1], Graphics.LEFT | Graphics.TOP);
        	if(!anime && NavSelect1 != 4) g.drawRoundRect(Position.PosSelf[NavSelect1][0] - 1, cy - 145 + Position.PosSelf[NavSelect1][1] - 1, 72, 101, 10, 10);
        	if(!anime && NavSelect1 != 4) g.drawRoundRect(Position.PosSelf[NavSelect1][0] - 2, cy - 145 + Position.PosSelf[NavSelect1][1] - 2, 74, 103, 14, 14);
        	
        	//FINISH
        	if (Mode == 0) f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_MEDIUM);
        	else f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_SMALL);
	        g.setFont(f);
        	if (record.getDectNum() == 4){
	        	if (NavSelect1 == 4) g.setColor(0xf789b7); 
	        	else g.setColor(0xffdf30);
	        	g.fillRoundRect(98, cy - 145 + 241, 80, 20, 15, 15);
	        	g.setColor(0xffffff);
	        	g.drawRoundRect(98, cy - 145 + 241, 80, 20, 15, 15);
	        	g.drawRoundRect(100, cy - 145 + 243, 76, 16, 13, 13);
	        	g.drawString("COMPLETE", 138 - f.stringWidth("COMPLETE") / 2, cy - 145 + 252 - f.getHeight() / 2, Graphics.LEFT | Graphics.TOP);
        	}else{
	        	g.setColor(0x806223);
	        	g.fillRoundRect(98, cy - 145 + 241, 80, 20, 15, 15);
	        	g.setColor(0x808080);
	        	g.drawRoundRect(98, cy - 145 + 241, 80, 20, 15, 15);
	        	g.drawRoundRect(100, cy - 145 + 243, 76, 16, 13, 13);
	        	g.drawString("COMPLETE", 138 - f.stringWidth("COMPLETE") / 2, cy - 145 + 252 - f.getHeight() / 2, Graphics.LEFT | Graphics.TOP);
        	}
	        
			break;
			
		case Screen.CARD_DETAIL:

	    	//BACKGROUND
			g.setColor(0x000000);
	        g.fillRect(0, 0, getWidth(), getHeight());
	        if(bg != null) g.drawImage(bg, cx, cy, cl);
	    	
			//CARD
	        if(img != null) g.drawImage(img, cx, cy, cl);
			break;
			
		case Screen.BATTLE_FIELD:

	    	//BACKGROUND
			g.setColor(0x000000);
	        g.fillRect(0, 0, getWidth(), getHeight());
	        if(bg != null) g.drawImage(bg, cx + 120 - NavPage, cy, cl);
	    	
	        //INTRODUCTION
	        if(!anime && flow == Flow.SKILLSELECT && MaskBlack != null) {
	        	g.drawImage(Function.ZoomImage(MaskBlack, 240, 42), 0, cy - 145 + 250, Graphics.LEFT | Graphics.TOP);
	        	g.setColor(0xffffff);
	        	if (Mode == 0) f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_MEDIUM);
	        	else f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_SMALL);
	        	g.setFont(f);
	        	str = record.data.Skill[OptSelect].Comment[0];
	        	g.drawString(str, cx - f.stringWidth(str) / 2 + 20, cy - 145 + 251, Graphics.LEFT | Graphics.TOP);
	        	str = record.data.Skill[OptSelect].Comment[1];
	        	g.drawString(str, cx - f.stringWidth(str) / 2 + 20, cy - 145 + 263, Graphics.LEFT | Graphics.TOP);
	        	str = "魔力：" + record.data.Card[CardSelect].SkillCost[NavSelect2] + "　對象：" + Target[record.getTarget(OptSelect)];
	        	g.drawString(str, cx - f.stringWidth(str) / 2 + 20, cy - 145 + 275, Graphics.LEFT | Graphics.TOP);
	        }
	        
	        f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_MEDIUM);
	        g.setFont(f);
	        
	        if (NavPage < 119){
	        	//SELF HP BAR
	        	c = record.DeckSelf.HP / 500;
	        	bh = record.DeckSelf.HP % 500 * 240 / 500;
	        	if(c > 5) c = 5;
			    g.setColor(ColorHealth[c]);
	        	g.fillRect(10 - NavPage, cy - 145 + 20, 17, 240);
			    g.setColor(ColorHealth[c + 1]);
	        	g.fillRect(10 - NavPage, cy - 145 + 260 - bh, 17, bh);
			    g.setColor(0x232121);
	        	g.drawRect(10 - NavPage, cy - 145 + 20, 17, 240);
	        	g.drawRect(12 - NavPage, cy - 145 + 22, 13, 236);
			    g.setColor(0xc6b889);
	        	g.drawRect(11 - NavPage, cy - 145 + 21, 15, 238);
	        	str = record.DeckSelf.HP + "";
			    g.setColor(0xffffff);
		        g.drawString(str, 22 - f.stringWidth(str) / 2 - NavPage, cy - 145 + 265, Graphics.LEFT | Graphics.TOP);
		        
		        //SELF MP BAR
		        for(int i = 0; i < record.DeckSelf.MaxMP; i++){
		        	if(i < record.DeckSelf.TempMP) g.setColor(0xffc277);
		        	else if(i < record.DeckSelf.MP) g.setColor(0xe7a5de);
		        	else g.setColor(0x251208);
			        g.fillArc(30 - NavPage, cy - 145 + 240 - i * 18, 14, 14, 0, 360);
				    g.setColor(0x482410);
			        g.drawArc(31 - NavPage, cy - 145 + 241 - i * 18, 12, 12, 0, 360);
				    g.setColor(0xfaf5ee);
			        g.drawArc(30 - NavPage, cy - 145 + 240 - i * 18, 14, 14, 0, 360);
		        }
	        } else {
	        	
	        	//OPP HP BAR
	        	c = record.DeckOpp.HP / 500;
	        	bh = record.DeckOpp.HP % 500 * 240 / 500;
	        	if(c > 5) c = 5;
			    g.setColor(ColorHealth[c]);
	        	g.fillRect(453 - NavPage, cy - 145 + 20, 17, 240);
			    g.setColor(ColorHealth[c + 1]);
	        	g.fillRect(453 - NavPage, cy - 145 + 260 - bh, 17, bh);
			    g.setColor(0x232121);
	        	g.drawRect(453 - NavPage, cy - 145 + 20, 17, 240);
	        	g.drawRect(455 - NavPage, cy - 145 + 22, 13, 236);
			    g.setColor(0xc6b889);
	        	g.drawRect(454 - NavPage, cy - 145 + 21, 15, 238);
	        	str = record.DeckOpp.HP + "";
			    g.setColor(0xffffff);
		        g.drawString(str, 458 - f.stringWidth(str) / 2 - NavPage, cy - 145 + 265, Graphics.LEFT | Graphics.TOP);
		        
		        //OPP MP BAR
		        for(int i = 0; i < record.DeckOpp.MaxMP; i++){
		        	if(i < record.DeckOpp.MP) g.setColor(0xffc277);
		        	else g.setColor(0x251208);
			        g.fillArc(434 - NavPage, cy - 145 + 240 - i * 18, 14, 14, 0, 360);
				    g.setColor(0x482410);
			        g.drawArc(435 - NavPage, cy - 145 + 241 - i * 18, 12, 12, 0, 360);
				    g.setColor(0xfaf5ee);
			        g.drawArc(434 - NavPage, cy - 145 + 240 - i * 18, 14, 14, 0, 360);
		        }
	        }

	        //CARD
	        f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_BOLD, Font.SIZE_LARGE);
	        g.setFont(f);
	        g.setColor(0xffffff);
	        int sc = -1;
        	for(int i = 0; i < 4; i++){
        		if (NavPage < 230 && DeckSelf[i] != null) {
        			if (flow != Flow.SKILLSELECT) {
        				g.drawImage(DeckSelf[i], Position.PosSelf[i][0] - NavPage, cy - 145 + Position.PosSelf[i][1], Graphics.LEFT | Graphics.TOP);
        				if (flow == Flow.STANDBY && record.DeckSelf.CardDone[i]) {
        					g.drawImage(MaskBlack, Position.PosSelf[i][0] - NavPage, cy - 145 + Position.PosSelf[i][1], Graphics.LEFT | Graphics.TOP);
        					g.drawString("OK", Position.PosSelf[i][0] - NavPage + 35 - f.stringWidth("OK") / 2, cy - 145 + Position.PosSelf[i][1] + 42, Graphics.LEFT | Graphics.TOP);
        				}
        				else if (flow == Flow.BATTLE && State == 5 && stuff1 != null) {
        					if (record.Damage[i] > 0){
        						g.drawImage(stuff1, Position.PosSelf[i][0] - NavPage, cy - 145 + Position.PosSelf[i][1], Graphics.LEFT | Graphics.TOP);
	        					str = record.Damage[i] + "";
	        					if (Step < 60) g.drawString(str, Position.PosSelf[i][0] - NavPage + 35 - f.stringWidth(str) / 2, cy - 145 + Position.PosSelf[i][1] + 50 - Step / 2, Graphics.LEFT | Graphics.TOP);
        					} else if (record.Damage[i] < -1){
        						g.drawImage(stuff1, Position.PosSelf[i][0] - NavPage, cy - 145 + Position.PosSelf[i][1], Graphics.LEFT | Graphics.TOP);
        					}
        				}
        				else if (flow == Flow.TARGETSELEST && record.getTarget(OptSelect) == 0 && NavSelect1 != i) g.drawImage(MaskBlack, Position.PosSelf[i][0] - NavPage, cy - 145 + Position.PosSelf[i][1], Graphics.LEFT | Graphics.TOP);
        			}
        			else if (NavSelect1 != i) g.drawImage(Function.AlphaImage(DeckSelf[i], 0x90000000), Position.PosSelf[i][0] - NavPage, cy - 145 + Position.PosSelf[i][1], Graphics.LEFT | Graphics.TOP);
        			else sc = i;
        		}
        		if (NavPage > 10 && DeckOpp[i] != null) {
        			g.drawImage(DeckOpp[i], Position.PosOpp[i][0] - NavPage, cy - 145 + Position.PosOpp[i][1], Graphics.LEFT | Graphics.TOP);
        			if (flow == Flow.BATTLE && State == 5 && stuff1 != null){
        				if (record.Damage[i] > 0) {
        					g.drawImage(stuff1, Position.PosOpp[i][0] - NavPage, cy - 145 + Position.PosOpp[i][1], Graphics.LEFT | Graphics.TOP);
            				str = record.Damage[i] + "";
            				if (Step < 60) g.drawString(str, Position.PosOpp[i][0] - NavPage + 35 - f.stringWidth(str) / 2, cy - 145 + Position.PosOpp[i][1] + 50 - Step / 2, Graphics.LEFT | Graphics.TOP);
        				} else if (record.Damage[i] < -1){
        					g.drawImage(stuff1, Position.PosOpp[i][0] - NavPage, cy - 145 + Position.PosOpp[i][1], Graphics.LEFT | Graphics.TOP);
        				}
        			}
        		}
        	}
        	
        	if(sc != -1) g.drawImage(DeckSelf[sc], cx + 15 - NavPage, cy - 30, cl);

        	//SELECT
        	g.setColor(0xffc000);
        	if(!anime && NavSelect1 != 8 && flow != Flow.SKILLSELECT) {
        		if (flow == Flow.STANDBY || record.getTarget(OptSelect) == 0 || record.getTarget(OptSelect) == 1 || record.getTarget(OptSelect) == 4) {
        			g.drawRoundRect(Position.PosSelf[NavSelect1][0] - 1 - NavPage, cy - 145 + Position.PosSelf[NavSelect1][1] - 1, 72, 101, 10, 10);
        			g.drawRoundRect(Position.PosSelf[NavSelect1][0] - 2 - NavPage, cy - 145 + Position.PosSelf[NavSelect1][1] - 2, 74, 103, 14, 14);
        		} else if (flow == Flow.TARGETSELEST && (record.getTarget(OptSelect) == 3 || record.getTarget(OptSelect) == 5)) {
        			for (int i = 0; i < 8; i++) {
	        			g.drawRoundRect(Position.PosSelf[i][0] - 1 - NavPage, cy - 145 + Position.PosSelf[i][1] - 1, 72, 101, 10, 10);
	        			g.drawRoundRect(Position.PosSelf[i][0] - 2 - NavPage, cy - 145 + Position.PosSelf[i][1] - 2, 74, 103, 14, 14);
        			}
        		} else if (flow == Flow.TARGETSELEST && record.getTarget(OptSelect) == 2){
        			if (NavSelect1 == 0 || NavSelect1 == 1 || NavSelect1 == 4 || NavSelect1 == 5){
	        			g.drawRoundRect(Position.PosSelf[0][0] - 1 - NavPage, cy - 145 + Position.PosSelf[0][1] - 1, 72, 101, 10, 10);
	        			g.drawRoundRect(Position.PosSelf[0][0] - 2 - NavPage, cy - 145 + Position.PosSelf[0][1] - 2, 74, 103, 14, 14);
	        			g.drawRoundRect(Position.PosSelf[1][0] - 1 - NavPage, cy - 145 + Position.PosSelf[1][1] - 1, 72, 101, 10, 10);
	        			g.drawRoundRect(Position.PosSelf[1][0] - 2 - NavPage, cy - 145 + Position.PosSelf[1][1] - 2, 74, 103, 14, 14);
	        			g.drawRoundRect(Position.PosSelf[4][0] - 1 - NavPage, cy - 145 + Position.PosSelf[4][1] - 1, 72, 101, 10, 10);
	        			g.drawRoundRect(Position.PosSelf[4][0] - 2 - NavPage, cy - 145 + Position.PosSelf[4][1] - 2, 74, 103, 14, 14);
	        			g.drawRoundRect(Position.PosSelf[5][0] - 1 - NavPage, cy - 145 + Position.PosSelf[5][1] - 1, 72, 101, 10, 10);
	        			g.drawRoundRect(Position.PosSelf[5][0] - 2 - NavPage, cy - 145 + Position.PosSelf[5][1] - 2, 74, 103, 14, 14);
        			} else {
	        			g.drawRoundRect(Position.PosSelf[2][0] - 1 - NavPage, cy - 145 + Position.PosSelf[2][1] - 1, 72, 101, 10, 10);
	        			g.drawRoundRect(Position.PosSelf[2][0] - 2 - NavPage, cy - 145 + Position.PosSelf[2][1] - 2, 74, 103, 14, 14);
	        			g.drawRoundRect(Position.PosSelf[3][0] - 1 - NavPage, cy - 145 + Position.PosSelf[3][1] - 1, 72, 101, 10, 10);
	        			g.drawRoundRect(Position.PosSelf[3][0] - 2 - NavPage, cy - 145 + Position.PosSelf[3][1] - 2, 74, 103, 14, 14);
	        			g.drawRoundRect(Position.PosSelf[6][0] - 1 - NavPage, cy - 145 + Position.PosSelf[6][1] - 1, 72, 101, 10, 10);
	        			g.drawRoundRect(Position.PosSelf[6][0] - 2 - NavPage, cy - 145 + Position.PosSelf[6][1] - 2, 74, 103, 14, 14);
	        			g.drawRoundRect(Position.PosSelf[7][0] - 1 - NavPage, cy - 145 + Position.PosSelf[7][1] - 1, 72, 101, 10, 10);
	        			g.drawRoundRect(Position.PosSelf[7][0] - 2 - NavPage, cy - 145 + Position.PosSelf[7][1] - 2, 74, 103, 14, 14);
        			}
        		}
        	}
        	
        	//TURN
        	if (NavSelect1 < 230){
        		if (Mode == 0) f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_MEDIUM);
	        	else f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_SMALL);
    	        g.setFont(f);
    	        g.setColor(0xffffff);
    	        str = "Turn " + Function.AddZero(record.Turn + 1, 2);
    	        g.drawString(str, cx - f.stringWidth(str) / 2 - NavPage, cy - 145 + 2, Graphics.LEFT | Graphics.TOP);
        	}

        	//FIN
        	if (flow == Flow.STANDBY && NavSelect1 < 230) {
        		
        		if (Mode == 0) f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_MEDIUM);
	        	else f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_SMALL);
    	        g.setFont(f);
    	        
            	if (NavSelect1 == 8) g.setColor(0xf7ce5e); 
            	else g.setColor(0xf1a092);
            	g.fillRoundRect(98 - NavPage, cy - 145 + 241, 80, 20, 15, 15);
            	g.setColor(0xffffff);
            	g.drawRoundRect(98 - NavPage, cy - 145 + 241, 80, 20, 15, 15);
            	g.drawRoundRect(100 - NavPage, cy - 145 + 243, 76, 16, 13, 13);
            	g.drawString("COMPLETE", 138 - f.stringWidth("COMPLETE") / 2 - NavPage, cy - 145 + 252 - f.getHeight() / 2, Graphics.LEFT | Graphics.TOP);
        	}
      	
        	//SKILL
        	else if (flow == Flow.SKILLSELECT && !anime){
        		if (Mode == 0) f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_MEDIUM);
	        	else f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_SMALL);
    	        g.setFont(f);
    	        
        		if (NavSelect2 == 0) {
        			g.setColor(0x5ca5d3); 
        			g.fillRoundRect(62, cy - 145 + 180, 150, 20, 15, 15);
            		g.setColor(0x505a6a);
            		g.fillRoundRect(62, cy - 145 + 215, 150, 20, 15, 15);
        		}
        		else {
        			g.setColor(0x505a6a);
        			g.fillRoundRect(62, cy - 145 + 180, 150, 20, 15, 15);
            		g.setColor(0x5ca5d3);
            		g.fillRoundRect(62, cy - 145 + 215, 150, 20, 15, 15);
        		}
        		g.setColor(0xffe21d);
        		g.drawRoundRect(62, cy - 145 + 180, 150, 20, 15, 15);
        		g.drawRoundRect(62, cy - 145 + 215, 150, 20, 15, 15);
        		
        		if (record.data.Card[CardSelect].SkillCost[0] > record.DeckSelf.TempMP) g.setColor(0x333333);
        		else g.setColor(0xffffff);
        		str = record.data.Skill[record.data.Card[CardSelect].Skill[0]].Name;
            	g.drawString(str, cx - f.stringWidth(str) / 2 + 20, cy - 145 + 182, Graphics.LEFT | Graphics.TOP);
        		if (record.data.Card[CardSelect].SkillCost[1] > record.DeckSelf.TempMP) g.setColor(0x333333);
        		else g.setColor(0xffffff);
        		str = record.data.Skill[record.data.Card[CardSelect].Skill[1]].Name;
            	g.drawString(str, cx - f.stringWidth(str) / 2 + 20, cy - 145 + 217, Graphics.LEFT | Graphics.TOP);
        	}
        	
        	if (State == 6 && stuff1 != null) g.drawImage(stuff1, cx, cy, cl);
        	
			break;

		case Screen.BATTLE_ATTCK:

	    	//BACKGROUND
			g.setColor(0x000000);
	        g.fillRect(0, 0, getWidth(), getHeight());
	        if(bg != null) g.drawImage(bg, cx + 120 - NavPage, cy, cl);
	        
	        //SELF
	        if (record.EventStack[record.EventStackTop].Self) {
		        if (State == 1) {
		        	if (StandSelf[record.EventStack[record.EventStackTop].CasterLoc] != null)
		        		g.drawImage(StandSelf[record.EventStack[record.EventStackTop].CasterLoc], cx - 200 + Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        } else if (State == 2) {
		        	if (StandSelf[record.EventStack[record.EventStackTop].CasterLoc] != null)
		        		g.drawImage(StandSelf[record.EventStack[record.EventStackTop].CasterLoc], cx, cy, Graphics.VCENTER | Graphics.HCENTER);
		        } else if (State == 3) {
		        	if (StandSelf[record.EventStack[record.EventStackTop].CasterLoc] != null)
		        		g.drawImage(StandSelf[record.EventStack[record.EventStackTop].CasterLoc], cx - Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        	
		        	//SELF BUFF
		        	if (record.EventStack[record.EventStackTop].Buff) {
		        		if (record.EventStack[record.EventStackTop].TargetAmount == 1 && StandSelf[record.EventStack[record.EventStackTop].Target[0]] != null)
			        		g.drawImage(StandSelf[record.EventStack[record.EventStackTop].Target[0]], cx - 200 + Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        		else if (record.EventStack[record.EventStackTop].TargetAmount == 4) {
		        			for (int i = 0; i < 4; i++){
		        				/*int x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2 + 170 - Frame;
	        					if (x < 0) x = 0;
	        					else if (x > StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60;
		        				g.drawImage(Image.createImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], x, 0, 60, 295, Sprite.TRANS_NONE), 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);*/
		        				g.setClip(i * 60, cy - 145, 60, 295);
		        				g.drawImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], 30 + i * 60 - 200 + Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        			}
		        			g.setClip(0, 0, getWidth(), getHeight());
		        		}
		        		
		        	//SELF ATK
		        	} else {
		        		if (record.EventStack[record.EventStackTop].TargetAmount == 1 && StandOpp[record.EventStack[record.EventStackTop].Target[0]] != null)
			        		g.drawImage(StandOpp[record.EventStack[record.EventStackTop].Target[0]], cx + 200 - Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        		else if (record.EventStack[record.EventStackTop].TargetAmount == 4) {
		        			for (int i = 0; i < 4; i++){
		        				if (StandOpp[record.EventStack[record.EventStackTop].Target[i]] != null){
		        					/*int x = StandOpp[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2 - 230 + Frame;
		        					if (x < 0) x = 0;
		        					else if (x > StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60;
		        					g.drawImage(Image.createImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], x, 0, 60, 295, Sprite.TRANS_NONE), 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);*/
		        					g.setClip(i * 60, cy - 145, 60, 295);
			        				g.drawImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], 30 + i * 60 + 200 - Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        				}
		        			}
	        				g.setClip(0, 0, getWidth(), getHeight());
		        		} else if (record.EventStack[record.EventStackTop].TargetAmount == 2) {
		        			for (int i = 0; i < 2; i++){
		        				if (StandOpp[record.EventStack[record.EventStackTop].Target[i]] != null){
		        					/*int x = StandOpp[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2 - 260 + Frame;
		        					if (x < 0) x = 0;
		        					else if (x > StandOpp[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60;
		        					g.drawImage(Image.createImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], x, 0, 120, 295, Sprite.TRANS_NONE), 60 + i * 120, cy, Graphics.VCENTER | Graphics.HCENTER);*/
		        					g.setClip(i * 120, cy - 145, 120, 295);
			        				g.drawImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], 60 + i * 120 + 200 - Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        				}
		        			}
	        				g.setClip(0, 0, getWidth(), getHeight());
		        		}
		        	}
		        } else if (State == 4) {
		        	
		        	//SELF BUFF
		        	if (record.EventStack[record.EventStackTop].Buff) {
		        		if (record.EventStack[record.EventStackTop].TargetAmount == 1 && StandSelf[record.EventStack[record.EventStackTop].Target[0]] != null)
			        		g.drawImage(StandSelf[record.EventStack[record.EventStackTop].Target[0]], cx, cy, Graphics.VCENTER | Graphics.HCENTER);
		        		else if (record.EventStack[record.EventStackTop].TargetAmount == 4) {
		        			for (int i = 0; i < 4; i++){
		        				if (StandOpp[record.EventStack[record.EventStackTop].Target[i]] != null){
		        					/*int x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2  - 30;
		        					if (x < 0) x = 0;
		        					else if (x > StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60;
		        					g.drawImage(Image.createImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], x, 0, 60, 295, Sprite.TRANS_NONE), 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);*/
		        					g.setClip(i * 60, cy - 145, 60, 295);
			        				g.drawImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);
		        				}
		        			}
	        				g.setClip(0, 0, getWidth(), getHeight());
		        		}
		        		
		        	//SELF ATK
		        	} else {
		        		if (record.EventStack[record.EventStackTop].TargetAmount == 1 && record.EventStack[record.EventStackTop].TargetAmount == 1 && StandOpp[record.EventStack[record.EventStackTop].Target[0]] != null)
			        		g.drawImage(StandOpp[record.EventStack[record.EventStackTop].Target[0]], cx, cy, Graphics.VCENTER | Graphics.HCENTER);
		        		else if (record.EventStack[record.EventStackTop].TargetAmount == 4) {
		        			for (int i = 0; i < 4; i++){
		        				if (StandOpp[record.EventStack[record.EventStackTop].Target[i]] != null){
		        					/*int x = StandOpp[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2 - 30;
		        					if (x < 0) x = 0;
		        					else if (x > StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60;
		        					g.drawImage(Image.createImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], x, 0, 60, 295, Sprite.TRANS_NONE), 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);*/
		        					g.setClip(i * 60, cy - 145, 60, 295);
			        				g.drawImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);
		        				}
		        			}
	        				g.setClip(0, 0, getWidth(), getHeight());
		        		} else if (record.EventStack[record.EventStackTop].TargetAmount == 2) {
		        			for (int i = 0; i < 2; i++){
		        				if (StandOpp[record.EventStack[record.EventStackTop].Target[i]] != null){
		        					/*int x = StandOpp[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2 - 60;
		        					if (x < 0) x = 0;
		        					else if (x > StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 120) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 120;
		        					g.drawImage(Image.createImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], x, 0, 120, 295, Sprite.TRANS_NONE), 60 + i * 120, cy, Graphics.VCENTER | Graphics.HCENTER);*/
		        					g.setClip(i * 120, cy - 145, 120, 295);
			        				g.drawImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], 60 + i * 120, cy, Graphics.VCENTER | Graphics.HCENTER);
		        				}
		        			}
	        				g.setClip(0, 0, getWidth(), getHeight());
		        		}
		        	}
		        }
		        
		    //OPP
	        } else {
		        if (State == 1) {
		        	if (StandOpp[record.EventStack[record.EventStackTop].CasterLoc] != null)
		        		g.drawImage(StandOpp[record.EventStack[record.EventStackTop].CasterLoc], cx + 200 - Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        } else if (State == 2) {
		        	if (StandOpp[record.EventStack[record.EventStackTop].CasterLoc] != null)
		        		g.drawImage(StandOpp[record.EventStack[record.EventStackTop].CasterLoc], cx, cy, Graphics.VCENTER | Graphics.HCENTER);
		        } else if (State == 3) {
		        	if (StandOpp[record.EventStack[record.EventStackTop].CasterLoc] != null)
		        		g.drawImage(StandOpp[record.EventStack[record.EventStackTop].CasterLoc], cx + Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        	
		        	// OPP BUFF
		        	if (record.EventStack[record.EventStackTop].Buff) {
		        		if (record.EventStack[record.EventStackTop].TargetAmount == 1 && StandOpp[record.EventStack[record.EventStackTop].Target[0]] != null)
			        		g.drawImage(StandOpp[record.EventStack[record.EventStackTop].Target[0]], cx + 200 - Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        		else if (record.EventStack[record.EventStackTop].TargetAmount == 4) {
		        			for (int i = 0; i < 4; i++){
		        				if (StandOpp[record.EventStack[record.EventStackTop].Target[i]] != null){
		        					/*int x = StandOpp[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2 - 230 + Frame;
		        					if (x < 0) x = 0;
		        					else if (x > StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60; 
		        					g.drawImage(Image.createImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], x, 0, 60, 295, Sprite.TRANS_NONE), 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);*/
		        					g.setClip(i * 60, cy - 145, 60, 295);
			        				g.drawImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], 30 + i * 60 + 200 - Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        				}
		        			}
	        				g.setClip(0, 0, getWidth(), getHeight());
		        		}
		        		
		        	//OPP ATK
		        	} else {
		        		if (record.EventStack[record.EventStackTop].TargetAmount == 1 && StandSelf[record.EventStack[record.EventStackTop].Target[0]] != null)
			        		g.drawImage(StandSelf[record.EventStack[record.EventStackTop].Target[0]], cx - 200 + Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        		else if (record.EventStack[record.EventStackTop].TargetAmount == 4) {
		        			for (int i = 0; i < 4; i++){
		        				if (StandSelf[record.EventStack[record.EventStackTop].Target[i]] != null){
			        				/*int x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2 + 170 - Frame;
		        					if (x < 0) x = 0;
		        					else if (x > StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60;
			        				g.drawImage(Image.createImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], x, 0, 60, 295, Sprite.TRANS_NONE), 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);*/
			        				g.setClip(i * 60, cy - 145, 60, 295);
			        				g.drawImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], 30 + i * 60 - 200 + Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        				}
		        			}
	        				g.setClip(0, 0, getWidth(), getHeight());
		        		} else if (record.EventStack[record.EventStackTop].TargetAmount == 2) {
		        			for (int i = 0; i < 2; i++){
		        				if (StandSelf[record.EventStack[record.EventStackTop].Target[i]] != null){
		        					/*int x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2 + 140 - Frame;
		        					if (x < 0) x = 0;
		        					else if (x > StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 120) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 120;
		        					g.drawImage(Image.createImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], x, 0, 120, 295, Sprite.TRANS_NONE), 60 + i * 120, cy, Graphics.VCENTER | Graphics.HCENTER);*/
			        				g.setClip(i * 120, cy - 145, 120, 295);
			        				g.drawImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], 60 + i * 120 - 200 + Frame, cy, Graphics.VCENTER | Graphics.HCENTER);
		        				}
		        			}
	        				g.setClip(0, 0, getWidth(), getHeight());
		        		}
		        	}
		        } else if (State == 4) {
		        	
		        	//OPP BUFF
		        	if (record.EventStack[record.EventStackTop].Buff) {
		        		if (record.EventStack[record.EventStackTop].TargetAmount == 1 && StandOpp[record.EventStack[record.EventStackTop].Target[0]] != null)
			        		g.drawImage(StandOpp[record.EventStack[record.EventStackTop].Target[0]], cx, cy, Graphics.VCENTER | Graphics.HCENTER);
		        		else if (record.EventStack[record.EventStackTop].TargetAmount == 4) {
		        			for (int i = 0; i < 4; i++){
		        				if (StandOpp[record.EventStack[record.EventStackTop].Target[i]] != null){
		        					/*int x = StandOpp[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2 - 30;
		        					if (x < 0) x = 0;
		        					else if (x > StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60;
		        					g.drawImage(Image.createImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], x, 0, 60, 295, Sprite.TRANS_NONE), 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);*/
		        					g.setClip(i * 60, cy - 145, 60, 295);
			        				g.drawImage(StandOpp[record.EventStack[record.EventStackTop].Target[i]], 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);
		        				}
		        			}
	        				g.setClip(0, 0, getWidth(), getHeight());
		        		}
		        		
		        	//OPP ATK
		        	} else {
		        		if (record.EventStack[record.EventStackTop].TargetAmount == 1 && StandSelf[record.EventStack[record.EventStackTop].Target[0]] != null)
			        		g.drawImage(StandSelf[record.EventStack[record.EventStackTop].Target[0]], cx, cy, Graphics.VCENTER | Graphics.HCENTER);
		        		else if (record.EventStack[record.EventStackTop].TargetAmount == 4) {
		        			for (int i = 0; i < 4; i++){
		        				if (StandSelf[record.EventStack[record.EventStackTop].Target[i]] != null){
		        					/*int x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2 - 30;
		        					if (x < 0) x = 0;
		        					else if (x > StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60;
			        				g.drawImage(Image.createImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], x, 0, 60, 295, Sprite.TRANS_NONE), 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);*/
		        					g.setClip(i * 60, cy - 145, 60, 295);
			        				g.drawImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], 30 + i * 60, cy, Graphics.VCENTER | Graphics.HCENTER);
		        				}
		        			}
	        				g.setClip(0, 0, getWidth(), getHeight());
		        		} else if (record.EventStack[record.EventStackTop].TargetAmount == 2) {
		        			for (int i = 0; i < 2; i++){
		        				if (StandSelf[record.EventStack[record.EventStackTop].Target[i]] != null){
		        					/*int x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() / 2 - 60;
		        					if (x < 0) x = 0;
		        					else if (x > StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60) x = StandSelf[record.EventStack[record.EventStackTop].Target[i]].getWidth() - 60;
		        					g.drawImage(Image.createImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], x, 0, 120, 295, Sprite.TRANS_NONE), 60 + i * 120, cy, Graphics.VCENTER | Graphics.HCENTER);*/
		        					g.setClip(i * 120, cy - 145, 120, 295);
			        				g.drawImage(StandSelf[record.EventStack[record.EventStackTop].Target[i]], 60 + i * 120, cy, Graphics.VCENTER | Graphics.HCENTER);
		        				}
		        			}
	        				g.setClip(0, 0, getWidth(), getHeight());
		        		}
		        	}
		        }
	        }
	        
	        if (State == 2) {
	        	if (Mode == 0) f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_MEDIUM);
	        	else f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_PLAIN, Font.SIZE_SMALL);
    	        g.setFont(f);
    	        if (stuff1 != null) g.drawImage(stuff1, cx, cy + 80, Graphics.VCENTER | Graphics.HCENTER);
    	        g.setColor(0xffffff);
	        	g.drawRect(70, cy - 145 + 214, 100, 20);
	        	
	        	str = record.data.Skill[record.EventStack[record.EventStackTop].Skill].Name;
	        	g.drawString(str, cx - f.stringWidth(str) / 2, cy - 145 + 217, Graphics.LEFT | Graphics.TOP);

	        	g.drawImage(Function.ZoomImage(MaskBlack, 240, 42), 0, cy - 145 + 250, Graphics.LEFT | Graphics.TOP);
	        	g.setColor(0xffffff);
	        	str = record.data.Skill[record.EventStack[record.EventStackTop].Skill].Comment[0];
	        	g.drawString(str, cx - f.stringWidth(str) / 2, cy - 145 + 251, Graphics.LEFT | Graphics.TOP);
	        	str = record.data.Skill[record.EventStack[record.EventStackTop].Skill].Comment[1];
	        	g.drawString(str, cx - f.stringWidth(str) / 2, cy - 145 + 263, Graphics.LEFT | Graphics.TOP);
	        	str = "魔力：" + record.data.Skill[record.EventStack[record.EventStackTop].Skill].Cast + "　對象：" + Target[record.getTarget(record.EventStack[record.EventStackTop].Skill)];
	        	g.drawString(str, cx - f.stringWidth(str) / 2, cy - 145 + 275, Graphics.LEFT | Graphics.TOP);
	        	
	        } else if (State == 4) {
	        	if (record.data.Skill[record.EventStack[record.EventStackTop].Skill].Effect == 0) {
	        		if (stuff1 != null && Step % 60 < 30 && Step < 450) g.drawImage(stuff1, cx, cy, cl);
	        	} else if (record.data.Skill[record.EventStack[record.EventStackTop].Skill].Effect == 1) {
	        		for (int i = 0; i < Frame && stuff1 != null && Step < 400; i++){
	        			g.drawImage(stuff1, cx, cy, cl);
	        		}
	        	}
	        }
	        break;

		case Screen.REPORT:

	    	//BACKGROUND
			g.setColor(0x000000);
	        g.fillRect(0, 0, getWidth(), getHeight());
	        if(bg != null) g.drawImage(bg, cx, cy, cl);
	        
	        if (img != null) g.drawImage(img, cx, cy, cl);
	        
	        g.drawImage(stuff1, cx, cy, cl);
		    
        	f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_BOLD, Font.SIZE_LARGE);
        	g.setFont(f);
		    if (flag) {
		    	g.setColor(0xffcc00);
		    	g.drawString("BATTLE CLEAR", cx - f.stringWidth("BATTLE CLEAR") / 2, cy - 10, Graphics.LEFT | Graphics.TOP);
		    } else {
		    	g.setColor(0x990000);
		    	g.drawString("BATTLE FAILED", cx - f.stringWidth("BATTLE FAILED") / 2, cy - 10, Graphics.LEFT | Graphics.TOP);
		    }

			break;
			
		case Screen.LOADING:
			
	    	//BACKGROUND
			g.setColor(0x000000);
	        g.fillRect(0, 0, getWidth(), getHeight());
	        
	        f = Font.getFont(Font.FACE_PROPORTIONAL, Font.STYLE_BOLD, Font.SIZE_LARGE);
        	g.setFont(f);
	    	g.setColor(0xffcc00);
		    g.drawString("LOADING...", cx - f.stringWidth("LOADING...") / 2, cy - 30, Graphics.LEFT | Graphics.TOP);
		    
		    g.setColor(0xffffff);
        	g.drawRect(cx - 38, cy + 10, 76, 11);
        	g.setColor(0xffcc00);
        	g.fillRect(cx - 36, cy + 12, Step, 8);
        	
		}
	}
}
