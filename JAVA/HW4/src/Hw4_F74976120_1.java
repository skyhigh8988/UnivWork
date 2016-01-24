import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;

public class Hw4_F74976120_1 extends JFrame implements ActionListener
{	
	// 常數
	private static final String[] RecHeader = {"名稱", "電話", "住址"};
	
	// 全域變數
	private DefaultTableModel RecModel;
	private JTable RecTable;
	private boolean editflag = false, colflag = false, rowflag = false, goNext = true;
	
	public static void main(String[] args)
	{
		Hw4_F74976120_1 gui = new Hw4_F74976120_1();
		gui.setVisible(true);
	}
	
	public Hw4_F74976120_1()
	{
		// 視窗設定
		super("JAVA HW4 (Address Book) F74976120");
		setSize(800, 600);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		// 按鈕區域
		JPanel BtnPane = new JPanel();
		BtnPane.setBorder(BorderFactory.createEmptyBorder(10, 0, 5, 0));
		add(BtnPane, BorderLayout.NORTH);
		
		// 按鈕宣告
		JButton NewBtn = new JButton("新增");
		JButton DelBtn = new JButton("刪除");
		JButton OutBtn = new JButton("匯出");
		JButton InBtn = new JButton("匯入");
		
		// 按鈕觸發設定
		NewBtn.setActionCommand("NewRec");
		DelBtn.setActionCommand("DelRec");
		OutBtn.setActionCommand("Output");
		InBtn.setActionCommand("Input");
		NewBtn.addActionListener(this);
		DelBtn.addActionListener(this);
		OutBtn.addActionListener(this);
		InBtn.addActionListener(this);
		
		// 按鈕配置
		BtnPane.add(NewBtn);
		BtnPane.add(DelBtn);
		BtnPane.add(OutBtn);
		BtnPane.add(InBtn);
		
		// 表格宣告及設定
		RecModel = new DefaultTableModel(null, RecHeader);
		RecTable = new JTable(RecModel);
		RecTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		RecTable.getDefaultEditor(String.class).addCellEditorListener(new EditLis());
		RecTable.getSelectionModel().addListSelectionListener(new ListLis());
		RecTable.getColumnModel().addColumnModelListener(new ColLis());
		
		// 欄位設定
		TableColumn NameCol = RecTable.getColumnModel().getColumn(0);
		TableColumn TelCol = RecTable.getColumnModel().getColumn(1);
		TableColumn AdrsCol = RecTable.getColumnModel().getColumn(2);
		NameCol.setPreferredWidth(100);
		TelCol.setPreferredWidth(150);
		AdrsCol.setPreferredWidth(432);
		NameCol.setResizable(false);
		TelCol.setResizable(false);
		AdrsCol.setResizable(false);
		
		// 捲動視窗宣告及設定
		JScrollPane ScrPane = new JScrollPane(RecTable);
		ScrPane.setPreferredSize(new Dimension(700, 450));
		ScrPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		
		// 資料區域
		JPanel RecPane = new JPanel();
		RecPane.add(ScrPane, BorderLayout.CENTER);
		add(RecPane, BorderLayout.CENTER);
		
	}
	
	public void actionPerformed(ActionEvent e)
	{
		String actionCommand = e.getActionCommand();

		// 新增
		if(actionCommand.equals("NewRec"))
		{
			// 停止編輯
			goNext = false;
			if(RecTable.getCellEditor() != null) RecTable.getCellEditor().stopCellEditing();
			if(RecTable.getCellEditor() != null) return;
			
			// 新增行
			RecModel.addRow(new Object[]{"", "", ""});
			int row = RecModel.getRowCount() - 1;

			// 選取並進入編輯
			RecTable.changeSelection(row, 0, false, false);
			RecTable.editCellAt(row, 0);
			RecTable.getEditorComponent().requestFocusInWindow();
		}
		
		// 刪除
		else if(actionCommand.equals("DelRec"))
		{
			// 停止編輯
			if(RecTable.getCellEditor() != null) RecTable.getCellEditor().cancelCellEditing();
			
			// 刪除選取行
			int row[] = RecTable.getSelectedRows();
			for(int i = 0; i < row.length; i++) RecModel.removeRow(row[0]);
			
			// 選取下一行
			if(row.length > 0)
			{
				if(row[0] > RecTable.getRowCount() - 1) row[0]--;
				RecTable.changeSelection(row[0], 0, false, false);
			}
		}
		
		// 輸出檔案
		else if(actionCommand.equals("Output"))
		{
			// 停止編輯
			goNext = false;
			if(RecTable.getCellEditor() != null) RecTable.getCellEditor().stopCellEditing();
			if(RecTable.getCellEditor() != null) return;
			
			// 檔案選擇器宣告及設定
			JFileChooser Chooser = new JFileChooser();
			Chooser.setDialogTitle("匯出資料");
			Chooser.setCurrentDirectory(new File("."));
			
			// 顯示並取得回傳值
			int RtnVal = Chooser.showSaveDialog(this);
			
			// 回傳確認
		    if(RtnVal == JFileChooser.APPROVE_OPTION)
		    {
		    	// 檢查檔案存在與否
				while(Chooser.getSelectedFile().exists())
				{
					// 詢問覆蓋與否
					Object[] options = {"覆蓋", "重新命名", "取消"};
    				int n = JOptionPane.showOptionDialog(RecTable.getParent(), "檔案已存在!\n您想要取代該檔案嗎?", 
    						"檔案已存在", JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.WARNING_MESSAGE, null, options, options[1]);
    				
    				// 離開迴圈
    				if(n == JOptionPane.YES_OPTION) break;
    				
    				// 再次詢問路徑
    				else if(n == JOptionPane.NO_OPTION)
                    {
    					RtnVal = Chooser.showSaveDialog(this);
    					if(RtnVal != JFileChooser.APPROVE_OPTION) return;
                    }
    				
    				// 離開函式
                    else
                    {
                    	return;
                    }
				}
				
				// 匯出資料
		    	OutputData(Chooser.getSelectedFile());
		    }
		}
		
		// 匯入資料
		else if(actionCommand.equals("Input"))
		{
			// 檔案選擇器宣告及設定
			JFileChooser Chooser = new JFileChooser();
			Chooser.setDialogTitle("匯入資料");
			Chooser.setCurrentDirectory(new File("."));
			
			// 顯示並取得回傳值
			int RtnVal = Chooser.showOpenDialog(this);
			
			// 回傳確認
		    if(RtnVal == JFileChooser.APPROVE_OPTION)
		    {
		    	// 停止編輯
		    	if(RecTable.getCellEditor() != null) RecTable.getCellEditor().cancelCellEditing();
		    	
		    	// 匯入資料
		    	InputData(Chooser.getSelectedFile());
		    }
		    else
		    {
		    	// 尚在編輯則取回焦點
		    	if(RecTable.getCellEditor() != null) RecTable.getEditorComponent().requestFocusInWindow();
		    }
		}
	}
	
	private class ListLis implements ListSelectionListener
	{
		// 選取行改變時觸發
		public void valueChanged(ListSelectionEvent e) {
			
			// 仍在編輯狀態
			if(RecTable.getCellEditor() != null && !rowflag)
			{
				// 取得原選取行
				int source = RecTable.getSelectedRow();
				if(source == e.getFirstIndex()) source = e.getLastIndex();
				else source = e.getFirstIndex();
				
				// 防止重複觸發
				rowflag = true;
				
				// 還原選取行之改變
				RecTable.changeSelection(source, RecTable.getSelectedColumn(), false, false);
			}
			
			// 恢復正常觸發
			if(rowflag) rowflag = false;
		}
	}
	
	private class ColLis implements TableColumnModelListener
	{

		public void columnAdded(TableColumnModelEvent e) {}
		public void columnMarginChanged(ChangeEvent e) {}
		public void columnMoved(TableColumnModelEvent e) {}
		public void columnRemoved(TableColumnModelEvent e) {}

		// 選取欄改變時觸發
		public void columnSelectionChanged(ListSelectionEvent e)
		{
			// 仍在編輯狀態
			if(RecTable.getCellEditor() != null && !colflag)
			{
				// 取得原欄位
				int source = RecTable.getSelectedColumn();
				if(source == e.getFirstIndex()) source = e.getLastIndex();
				else source = e.getFirstIndex();
				
				// 防止重複觸發
				colflag = true;
				
				// 還原選取欄位之改變
				RecTable.changeSelection(RecTable.getSelectedRow(), source, false, false);
			}
			
			// 恢復正常觸發
			if(colflag) colflag = false;
		}
	}
	
	private class EditLis implements CellEditorListener
	{
		// 結束欄位編輯時觸發
	    public void editingStopped(ChangeEvent e)
	    {
	    	// 取得選取欄位位置以及內容並移除混淆字元
		    int row = RecTable.getSelectedRow(), col = RecTable.getSelectedColumn();
	    	String value = (RecTable.getValueAt(row, col) + "").replace("\n", " ");
	    	RecTable.setValueAt(value, row, col);
	    	
	    	// 名稱欄位
	    	if(col == 0)
	    	{
	    		// 空值
		    	if(value.equals(""))
		    	{
		    		// 防止重複觸發
		    		if(!editflag)
			    	{
		    			editflag = true;
			    		return;
			    	}
		    		
		    		// 詢問是否放棄資料
		    		Object[] options = {"捨棄本筆", "返回編輯"};
					int n = JOptionPane.showOptionDialog(RecTable.getParent(), "名稱不可為空!\n您想要放棄本筆資料嗎?", 
							"不合格的名稱", JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE, null, options, options[1]);
					
					// 刪除該行
    				if(n == JOptionPane.YES_OPTION)
    				{
    					RecModel.removeRow(row);
    					return;
                    }
    				
    				// 恢復編輯狀態並取回焦點
                    else
                    {
                    	RecTable.changeSelection(row, 0, false, false);
            			RecTable.editCellAt(row, 0);
            			RecTable.getEditorComponent().requestFocusInWindow();
                    }
		    	}
		    	else
		    	{
		    		for(int i = 0; i < RecTable.getRowCount(); i++)
		    		{
		    			// 發現重複名稱
		    			if(value.equals(RecTable.getValueAt(i, 0) + "") && i != row)
		    			{
		    				
		    				// 詢問是否放棄或取代
		    				Object[] options = {"取代該筆", "捨棄本筆", "返回編輯"};
		    				int n = JOptionPane.showOptionDialog(RecTable.getParent(), "名稱「" + value + "」已存在!\n您想要取代該筆資料嗎?", 
		    						"重複的名稱", JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.WARNING_MESSAGE, null, options, options[2]);
		    				
		    				// 移除目標行
		    				if(n == JOptionPane.YES_OPTION)
		    				{
		    					RecModel.removeRow(i);
		    					if(row > i) row--;
		                    }
		    				
		    				// 移除本行
		    				else if(n == JOptionPane.NO_OPTION)
		                    {
		    					RecModel.removeRow(row);
		    					return;
		                    }
		    				
		    				// 恢復編輯狀態並取回焦點
		                    else
		                    {
		                    	RecTable.changeSelection(row, 0, false, false);
		            			RecTable.editCellAt(row, 0);
		            			RecTable.getEditorComponent().requestFocusInWindow();
		                    }
		    				break;
		    			}
		    		}
		    	}
	    	}
	    	
	    	// 確實結束編輯狀態時
	    	if(RecTable.getCellEditor() == null)
	    	{
	    		if (goNext)
	    		{
		    		// 欄位一或欄位二
		    		if(col < 2)
		    		{
		    			// 關閉欄位變動觸發
		    			colflag = true;
		    			rowflag = true;
		    			
		    			// 使下一欄位進入編輯狀態並取得焦點
	                	RecTable.changeSelection(row, col + 1, false, false);
	        			RecTable.editCellAt(row, col + 1);
	        			RecTable.getEditorComponent().requestFocusInWindow();
		    		}
		    		
		    		// 欄位三且非最末行
		    		else if(row < RecTable.getRowCount() - 1)
		    		{
		    			// 選取下行
	                	RecTable.changeSelection(row + 1, 0, false, false);
		    		}
	    		}
	    		else
	    		{
	    			goNext = true;
	    		}
	    	}
	        
	    	// 恢復正常觸發
	    	if(editflag) editflag = false;
	    }

	    public void editingCanceled(ChangeEvent e) { }
	}
	
	// 匯出資料
	private void OutputData(File path)
	{
		try
		{
			FileWriter Writer = new FileWriter(path);
			
			// 從表格取得內容並寫入檔案
			for(int i = 0; i < RecModel.getRowCount(); i++)
			{
				Writer.write(RecTable.getValueAt(i, 0) + "\t");
				Writer.write(RecTable.getValueAt(i, 1) + "\t");
				Writer.write(RecTable.getValueAt(i, 2) + "\r\n");
			}
			Writer.close();
		}
		catch(IOException e) { }
	}
	
	// 匯入資料
	private void InputData(File path)
	{
		try
		{
			BufferedReader br = new BufferedReader(new FileReader(path));
			String line;

			// 清空表格
			RecModel.setRowCount(0);
			
			// 依序讀取行並加入表格
			while((line = br.readLine()) != null)
			{
				String[] RecCell = line.split("\t");
				RecModel.addRow(RecCell);
			}
		}
		catch(IOException e) { }
	}
}
