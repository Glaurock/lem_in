package src;

import java.util.HashMap;

public class Ant
{
	private static int increment = 1;

	public int id;
	public HashMap <Integer, Room> listMap;

	public Ant()
	{
		this.id = increment;
		this.listMap = new HashMap<>();
		increment++;
	}

	public String toString()
	{
		return ("Ant " + this.id);
	}
}