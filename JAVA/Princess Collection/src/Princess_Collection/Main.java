package Princess_Collection;

import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;
import javax.microedition.lcdui.*;

public class Main extends MIDlet implements CommandListener {

	Display display;
	private Graphic canvas;
	private Record record;
	private GameData data;
	
	//SONY
	//private Command undoCommand = new Command("取消", Command.CANCEL, 1);
    //private Command DetailCommand = new Command("資訊", Command.BACK, 2);
    //private Command OkCommand = new Command("確認", Command.OK, 3);
	
	//SUN
	//private Command undoCommand = new Command("取消", Command.BACK, 1);
    //private Command DetailCommand = new Command("資訊", Command.CANCEL, 2);
	//private Command OkCommand = null;
	
	public Main() {
		display = Display.getDisplay(this);
        data = new GameData();
		record = new Record(data);
        canvas = new Graphic(this, record);
        
        canvas.init();
        //canvas.addCommand(undoCommand);
        //canvas.addCommand(DetailCommand);
        //canvas.addCommand(OkCommand);
        //canvas.setCommandListener(this);
	}

	protected void destroyApp(boolean arg0) throws MIDletStateChangeException {
        display.setCurrent(null);
        canvas.destroy();
	}

	protected void pauseApp() {
	}

	protected void startApp() throws MIDletStateChangeException {
        display.setCurrent(canvas);
	}

	public void commandAction(Command c, Displayable s) {
		//if (c == undoCommand) canvas.callKey(Canvas.GAME_A);
		//else if (c == DetailCommand) canvas.callKey(Canvas.GAME_B);
		//else if (c == OkCommand) canvas.callKey(Canvas.FIRE);
	}

}
