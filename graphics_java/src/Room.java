package src;

import java.util.ArrayList;

public class Room
{
	public boolean isStart = false;
	public boolean isEnd = false;
	public String id = null;
	public int x = 0;
	public int y = 0;
	public ArrayList<Room> neighboors;

	public Room(String id, int x, int y)
	{
		this.id = id;
		this.x = x;
		this.y = y;
		this.neighboors = new ArrayList<>();
	}

	public void addNeighboors(Room rm)
	{
		if (neighboors.contains(rm) == false)
		{
			neighboors.add(rm);
			rm.addNeighboors(this);
		}
	}

	public String toString()
	{
		return ("id " + this.id + " x : " + this.x + " y : " + this.y);
	}
}