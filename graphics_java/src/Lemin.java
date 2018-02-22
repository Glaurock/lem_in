package src;

import java.util.ArrayList;

public class Lemin
{
	public Ant[] listAnts;
	public ArrayList<Room> listRooms;

	public Lemin(int nb_ant)
	{
		listAnts = new Ant[nb_ant];
		for (int i = 0; i < nb_ant; i++) {
			listAnts[i] = new Ant();
		}
		listRooms = new ArrayList<>();
	}

	public void addRoom(Room rm)
	{
		this.listRooms.add(rm);
	}

	public Room searchForRoom(String str)
	{
		for (Room rm : listRooms)
		{
			if (rm.id.equals(str))
				return (rm);
		}
		System.err.println("SNA");
		System.exit(1);
		return (null);
	}

	public String toString()
	{
		String str = "";

		for (Room rm : listRooms)
		{
			str += rm + "\n";
			for (Room rm2 : rm.neighboors)
			{
				str += "\t" + rm2.id + "\n";
			}
		}
		return (str);
	}
}