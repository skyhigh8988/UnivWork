package Princess_Collection;

import javax.microedition.lcdui.*;

public class Function {

	public static Image ZoomImage(Image src, int desW, int desH) {
		System.gc();
		Image desImg = null;
		int srcW = src.getWidth();

		int srcH = src.getHeight();

		int[] srcBuf = new int[srcW * srcH]; 

		src.getRGB(srcBuf, 0, srcW, 0, 0, srcW, srcH); 

		int[] tabY = new int[desH]; 
		int[] tabX = new int[desW]; 
		int sb = 0; 
		int db = 0; 
		int tems = 0; 
		int temd = 0; 
		int distance = srcH > desH ? srcH : desH; 
		
		for (int i = 0; i <= distance; i++) { 

			tabY[db] = sb; 
			tems += srcH; 
			temd += desH; 
			if (tems > distance) { 
				tems -= distance; 
				sb++; 
			} 
			
			if (temd > distance) { 
				temd -= distance; 
				db++; 
			} 
		} 
		
		sb = 0; 
		db = 0; 
		tems = 0; 
		temd = 0; 
		distance = srcW > desW ? srcW : desW; 
		
		for (int i = 0; i <= distance; i++) { 

			tabX[db] = (short) sb; tems += srcW; 
			temd += desW; 
			if (tems > distance) { 
				tems -= distance; 
				sb++;
			} 
			
			if (temd > distance) { 
				temd -= distance; 
				db++; 
			} 
		} 
		

		int[] desBuf = new int[desW * desH]; 
		int dx = 0; 
		int dy = 0; 
		int sy = 0; 
		int oldy = -1; 
		
		for (int i = 0; i < desH; i++) { 
			if (oldy == tabY[i]) { 
				System.arraycopy(desBuf, dy - desW, desBuf, dy, desW);
			} else { 
				dx = 0;
				for (int j = 0; j < desW; j++) { 
					desBuf[dy + dx] = srcBuf[sy + tabX[j]]; 
					dx++;
				}
				sy += (tabY[i] - oldy) * srcW;
			} 
			oldy = tabY[i];
			dy += desW;
		}


		desImg = Image.createRGBImage(desBuf, desW, desH, true);
		return desImg;
	}
	
	public static Image AlphaImage(Image src, int aph) {

		int[] data = new int[src.getWidth() * src.getHeight()];
		src.getRGB(data, 0, src.getWidth(), 0, 0, src.getWidth(), src.getHeight());
		int len = data.length;
		for(int i = 0; i < len; i++) {
			data[i] = data[i] + aph;
		}
		
		return Image.createRGBImage(data, src.getWidth(), src.getHeight(), true);
	}

	public static Image FadeImage(Image src, int aph1, int aph2) {

		int w = src.getWidth(), h = src.getHeight();
		int[] data = new int[w * h];
		src.getRGB(data, 0, w, 0, 0, w, h);
		
		int len = data.length;
		
		if (aph1 > aph2){
			for(int i = 0, aph = aph1; i < len; i++, aph = (int)(aph1 - ((aph1 - aph2) / (double)h) * (int)(i / w))) {
				if(aph < 0x05) aph = 0x05;
				else if(aph > 0xff) aph = 0xff;
				
				if(data[i] == 0xFFFFFF) data[i] = 0x00FFFFFF;
				else data[i] = data[i] + aph * 0x1000000;
			}
		} else if (aph1 < aph2){
			for(int i = 0, aph = aph1; i < len; i++, aph = (int)(aph1 + ((aph2 - aph1) / (double)h) * (int)(i / w))) {
				if(aph < 0x05) aph = 0x05;
				else if(aph > 0xff) aph = 0xff;
				if(data[i] == 0xFFFFFF) data[i] = 0x00FFFFFF;
				else data[i] = data[i] + aph * 0x1000000;
			}
		} else {
			for(int i = 0, aph = aph1; i < len; i++) {
				data[i] = data[i] + aph * 0x1000000;
			}
		}
		
		return Image.createRGBImage(data, src.getWidth(), src.getHeight(), true);
	}
	
	public static String AddZero (int src, int len) {
		String res = src + "";
		for (int i = 0, j = 10; i < len - 1; i++, j *= 10) {
			if (src < j) res = "0" + res;
		}
		return res;
	}
	
	public static Image CreatRect (int w, int h, int c, int a){
		if (a > 0xFF) a = 0xFF;
		else if (a < 0x00) a = 0x01;
		int[] data = new int[w * h];
		for (int i = 0; i < w * h; i++) data[i] = c + a * 0x1000000;
		return Image.createRGBImage(data, w, h, true);
	}
}
