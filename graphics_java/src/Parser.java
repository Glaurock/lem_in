package src;

import java.util.Scanner;

import org.graphstream.graph.*;
import org.graphstream.graph.implementations.*;

public class Parser
{
	private static boolean particularRoom = false;
	private static boolean nextIsStart = false;

	public static Lemin loadData()
	{
		Scanner sc_in = new Scanner(System.in);
		Lemin res = null;
		int	mode = 0;
		int nb_turn = 0;

		while (sc_in.hasNextLine())
		{
			String line = sc_in.nextLine();
			System.out.println(line);
			if (mode == 0)
			{
				res = new Lemin(Integer.parseInt(line));
				mode++;
			}
			else if (mode == 1)
			{
				if (storeRooms(line, res))
				{
					mode++;
				}
			}
			else if (mode == 2)
			{
				if (storeEdges(line, res))
				{
					mode++;
				}
			}
			else if (mode == 3)
			{
				nb_turn++;
				if (line.length() == 0)
					continue ;
				storeRoad(line, nb_turn, res);
			}
			else
			{
				break ;
			}
		}
		return (res);
	}

	private static boolean storeRooms(String line, Lemin res)
	{
		if (line.equals("##start"))
		{
			particularRoom = true;
			nextIsStart = true;
		}
		else if (line.equals("##end"))
		{
			particularRoom = true;
			nextIsStart = false;
		}
		else if (line.matches("^#[^#].*"))
		{
			System.err.println("Nothing to be done, matched as commentary " + line);
		}
		else if (line.length() == 0)
		{
			return (true);
		}
		else
		{
			Room rm;

			String[] splited = line.split(" ");
			if (splited.length == 3)
			{
				rm = new Room(splited[0], Integer.parseInt(splited[1]), Integer.parseInt(splited[2]));
				if (particularRoom)
				{
					if (nextIsStart)
					{
						rm.isStart = true;
					}
					else
					{
						rm.isEnd = true;
					}
					particularRoom = false;
					nextIsStart = false;
				}
				res.addRoom(rm);
			}
			else
			{
				storeEdges(line, res);
				return (true);
			}
		}
		return (false);
	}

	public static boolean storeEdges(String line, Lemin res)
	{
		if (line.length() == 0)
			return (true);
		String[] splited = line.split("-");
		res.searchForRoom(splited[0]).addNeighboors(res.searchForRoom(splited[1]));
		return (false);
	}

	public static void storeRoad(String line, int nb_turn, Lemin res)
	{
		String[] splited = line.split(" ");
		
		for (String str : splited)
		{
			String[] splited2 = str.split("-");
			splited2[0] = splited2[0].substring(1);
			res.listAnts[Integer.parseInt(splited2[0]) - 1].listMap.put(nb_turn, res.searchForRoom(splited2[1]));
		}
	}
}