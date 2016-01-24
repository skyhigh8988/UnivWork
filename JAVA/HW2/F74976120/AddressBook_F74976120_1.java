import java.util.*;
import java.lang.*;
import java.io.*;

public class AddressBook_F74976120_1
{		
	public static void main(String args[])
	{
		AddressBook_F74976120_1 addressbook = new AddressBook_F74976120_1();
	}
	
	private ContactObject_F74976120_1[] contact_list = new ContactObject_F74976120_1[0];
	//private ArrayList<ContactObject_F74976120_1> contact_list = new ArrayList();
	public AddressBook_F74976120_1()
	{
		try
		{
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));// get the input from console
        		String input = "";// used to be assigned the value of input
        		boolean is_exit=false;
        		while(true)	// check the input is null
			{
				int choice = -1;
				System.out.println("0.Exit  1.Insert  2.Delete  3.Update  4.Query by FirstName  5.Show All"); 		  
				System.out.print("Input Choice:");
				input = in.readLine();
				try
				{
					choice = Integer.parseInt(input);
				}
				catch(NumberFormatException nexp)
				{
				}
				switch(choice)
				{
					case 0:
						is_exit = true;
						break;
					case 1:
						InsertContact();
						break;
					case 2:
						DeleteContact();
						break;
					case 3:
						UpdateContact();
						break;	
					case 4:
						PrintByQuery();
						break;		
					case 5:
						showAll();
						break;	
					default:
						break;			
				}
				if(is_exit) 
				{
					System.out.println("System Exit");
					break;
				}
			}
		}
		catch(Exception exp)
		{
			exp.printStackTrace();
		}
	}
	
	public void PrintByQuery()
	{
		try
		{
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));// get the input from console
			System.out.print("Input Query Name:");
			String query_name = in.readLine(); // only one person updated
			System.out.println("First Name is like:" + query_name);
			// Query Process
			
			for(int i = 0; i < contact_list.length; i++)
			{
				// 關鍵字符合則印出
				if(contact_list[i].getName().contains(query_name))
				{
					System.out.println("Name:" + contact_list[i].getName() +
							" Phone:" + contact_list[i].getPhone() +
							" Email:" + contact_list[i].getEmail() +
							" Address:" + contact_list[i].getAddress() +
							" Sex:" + contact_list[i].getSex() +
							" Career:" + contact_list[i].getCareer()
							);
				}
			}
			
			// Array List Version
			/*for(int i = 0; i < contact_list.size(); i++)
			{
				if(contact_list.get(i).getName().contains(query_name))
				{
					System.out.println("Name:" + contact_list.get(i).getName() +
							" \tPhone:" + contact_list.get(i).getPhone() +
							" \tEmail:" + contact_list.get(i).getEmail() +
							" \tAddress:" + contact_list.get(i).getAddress() +
							" \tSex:" + contact_list.get(i).getSex() +
							" \tCareer:" + contact_list.get(i).getCareer()
							);
				}
			}*/
			//
			System.out.println("==========================");
		}
		catch(Exception exp)
		{
			exp.printStackTrace();
		}
	}
	
	public void showAll()
	{
		System.out.println("----All Contact Info------");
		// showAll Process
		
		// 依序印出
		for(int i = 0; i < contact_list.length; i++)
		{
			System.out.println("Name:" + contact_list[i].getName() +
					" Phone:" + contact_list[i].getPhone() +
					" Email:" + contact_list[i].getEmail() +
					" Address:" + contact_list[i].getAddress() +
					" Sex:" + contact_list[i].getSex() +
					" Career:" + contact_list[i].getCareer()
					);
		}
		
		// Array List Version
		/*for(int i = 0; i < contact_list.size(); i++)
		{
			System.out.println("Name:" + contact_list.get(i).getName() +
					" \tPhone:" + contact_list.get(i).getPhone() +
					" \tEmail:" + contact_list.get(i).getEmail() +
					" \tAddress:" + contact_list.get(i).getAddress() +
					" \tSex:" + contact_list.get(i).getSex() +
					" \tCareer:" + contact_list.get(i).getCareer()
					);
		}*/
		//
		System.out.println("==========================");
	}
	
	public void InsertContact()
	{
		/* A new array of contact must be declared to extend the list of contact*/
		try
		{
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));// get the input from console
			String Name = "", Sex = "", Career = "", Phone = "", Email = "", Address = "";
			System.out.print("Input Name:");
			Name = in.readLine();
			System.out.print("Input Phone:");
			Phone = in.readLine();
			System.out.print("Input Email:");
			Email = in.readLine();
			System.out.print("Input Address:");
			Address = in.readLine();
			System.out.print("Input Sex:");
			Sex = in.readLine();
			System.out.print("Input Career:");
			Career = in.readLine();
			//insert process.
			
			// 暫存暫列之宣告及複製內容
			ContactObject_F74976120_1[] temp_list = new ContactObject_F74976120_1[contact_list.length];
			for (int i = 0; i < contact_list.length; i++)
			{
				temp_list[i] = new ContactObject_F74976120_1(contact_list[i].getName(), contact_list[i].getPhone(), contact_list[i].getEmail(), contact_list[i].getAddress(), contact_list[i].getSex(), contact_list[i].getCareer());
			}
			
			// 重新分配大小
			contact_list = new ContactObject_F74976120_1[temp_list.length + 1];
			
			// 從暫存陣列取回內容及插入新增資料
			for (int i = 0; i < temp_list.length; i++)
			{
				contact_list[i] = new ContactObject_F74976120_1(temp_list[i].getName(), temp_list[i].getPhone(), temp_list[i].getEmail(), temp_list[i].getAddress(), temp_list[i].getSex(), temp_list[i].getCareer());
			}
			contact_list[temp_list.length] = new ContactObject_F74976120_1(Name, Phone, Email, Address, Sex, Career);
			
			// Array List Version
			/*contact_list.add(new ContactObject_F74976120_1(Name, Phone, Email, Address, Sex, Career));*/
			//
			System.out.println("==========================");
		}
		catch(Exception exp)
		{
			exp.printStackTrace();
		}			 	
	}
	
	public void DeleteContact()
	{
		try
		{
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));// get the input from console
			System.out.println("----Contact Decided to Delete?------");
			System.out.print("Deleted List:");
			String delete_name = in.readLine();// More than one contact are required to delete, please used the form of  A,B,C
			// delete process
			
			// 拆字
			String[] temp = delete_name.split(",");
			Arrays.sort(temp);
			
			// 暫存陣列及計數器
			ContactObject_F74976120_1[] temp_list = new ContactObject_F74976120_1[contact_list.length];
			int delete_count = 0;
			
			for(int i = 0; i < contact_list.length; i++)
			{
				// 姓名包含於欲刪除陣列中則delete_count+1否則複製內容至暫存陣列
				if(Arrays.binarySearch(temp, contact_list[i].getName()) >= 0)
				{
					delete_count++;
				}
				else
				{
					temp_list[i] = new ContactObject_F74976120_1(contact_list[i].getName(), contact_list[i].getPhone(), contact_list[i].getEmail(), contact_list[i].getAddress(), contact_list[i].getSex(), contact_list[i].getCareer());
				}
			}
			
			// 重新分配大小
			contact_list = new ContactObject_F74976120_1[temp_list.length - delete_count];
			
			// 從暫存陣列取回內容
			for (int i = 0, j = 0; i < contact_list.length; i++)
			{
				// 為被刪除項目改複製下筆資料
				while (temp_list[i + j] == null) j++;
				contact_list[i] = new ContactObject_F74976120_1(temp_list[i + j].getName(), temp_list[i + j].getPhone(), temp_list[i + j].getEmail(), temp_list[i + j].getAddress(), temp_list[i + j].getSex(), temp_list[i + j].getCareer());
			}

			// Array List Version
			/*for(int i = 0; i < contact_list.size(); i++)
			{
				if(Arrays.binarySearch(temp, contact_list.get(i).getName()) >= 0)
				{
					contact_list.remove(i);
				}
			}*/
			//
			System.out.println("==========================");
		}
		catch(Exception exp)
		{
			exp.printStackTrace();
		}
	}
	
	public void UpdateContact()
	{
		try
		{
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));// get the input from console
			System.out.println("----Contact Decided to Update?------");
			System.out.print("Update Contact:");
			String update_name = in.readLine();// only one person updated
			System.out.println("Choose Attribute:1.Name  2.Phone  3.Email  4.Address  5.Sex  6.Career");
			System.out.print("Update Information:");
			String update_info = in.readLine();// select the attribute and fill the value you want to update such as: 2,062543154 where 2 represents Phone 
			// update process
			
			// 拆字
			String[] temp = update_info.split(",");
			int choice = Integer.parseInt(temp[0]);
		
			for(int i = 0; i < contact_list.length; i++)
			{
				// 名字與輸入值相符則依choice更新對應資料
				if(contact_list[i].getName().equals(update_name))
				{
					switch(choice)
					{
						case 1:
							contact_list[i].setName(temp[1]);
							break;
						case 2:
							contact_list[i].setPhone(temp[1]);
							break;
						case 3:
							contact_list[i].setEmail(temp[1]);
							break;
						case 4:
							contact_list[i].setAddress(temp[1]);
							break;
						case 5:
							contact_list[i].setSex(temp[1]);
							break;			
						case 6:
							contact_list[i].setCareer(temp[1]);
							break;	
						default:
							break;
					}
				}
			}

			// Array List Version
			/*for(int i = 0; i < contact_list.size(); i++)
			{
				if(contact_list.get(i).getName().equals(update_name))
				{
					switch(choice)
					{
						case 1:
							contact_list.get(i).setName(temp[1]);
							break;
						case 2:
							contact_list.get(i).setPhone(temp[1]);
							break;
						case 3:
							contact_list.get(i).setEmail(temp[1]);
							break;
						case 4:
							contact_list.get(i).setAddress(temp[1]);
							break;
						case 5:
							contact_list.get(i).setSex(temp[1]);
							break;			
						case 6:
							contact_list.get(i).setCareer(temp[1]);
							break;	
						default:
							break;
					}
				}
			}*/
			//
			System.out.println("==========================");
		}
		catch(Exception exp)
		{
			exp.printStackTrace();
		}
	}
}

class ContactObject_F74976120_1 extends Contact_F74976120_1
{
	String Name = "";
	String Sex = "";
	String Career = "";
	
	ContactObject_F74976120_1(String name, String phone, String email, String address, String sex, String career)
	{
		//
		super(phone, email, address);
		Name = name;
		Sex = sex;
		Career = career;
		//
	}
	
	public void setName(String n)
	{
		//
		Name = n;
		//
	}
	
	public void setSex(String s)
	{
		//
		Sex = s;
		//
	}
	
	public void setCareer(String c)
	{
		//
		Career = c;
		//
	}
	
	public String getName()
	{
		//
		// To Do
		//
		return Name;
	}
	
	public String getSex()
	{
		//
		// To Do
		//
		return Sex;
	}
	
	public String getCareer()
	{
		//
		// To Do
		//
		return Career;
	}
}

class Contact_F74976120_1
{
	String Phone = "";
	String Email = "";
	String Address = "";
	
	Contact_F74976120_1(String phone, String email, String address)
	{
		//
		Phone = phone;
		Email = email;
		Address = address;
		//
	}
	
	public void setPhone(String p)
	{
		//
		Phone = p;
		//
	}
	
	public void setEmail(String e)
	{
		//
		Email = e;
		//
	}
	
	public void setAddress(String a)
	{
		//
		Address = a;
		//
	}
	
	public String getPhone()
	{
		//
		// To Do
		//
		return Phone;
	}
	
	public String getEmail()
	{
		//
		// To Do
		//
		return Email;
	}
	
	public String getAddress()
	{
		//
		// To Do
		//
		return Address;
	}
}