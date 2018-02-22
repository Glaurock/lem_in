package src;

import org.graphstream.graph.*;
import org.graphstream.graph.implementations.*;


public class Main
{
	private static String style = "node {" +
									"	shape: box;" +
								    "	fill-color: grey;" +
								    "}" +
								    "node.isStart {" +
								    "	fill-color: green;" +
								    "}" +
								    "node.isEnd {" +
								    "	fill-color: red;" +
								    "}" +
								    "node.marked {" +
								    "	fill-color: blue;" +
								    "}" +
								    "edge {" +
								    "	fill-color: black;" +
								    "}";

	public static void main(String[] args)
	{		
		Lemin lem = Parser.loadData();
		Graph graph = new MultiGraph("Lem_in Grapher");
		graph.setNullAttributesAreErrors(true);
		graph.addAttribute("ui.quality");
		graph.addAttribute("ui.antialias");
		graph.addAttribute("ui.stylesheet", style);

		for (Room rm : lem.listRooms)
		{
			Node n = graph.addNode(rm.id);
			n.addAttribute("ui.label", rm.id);
			n.addAttribute("ui.class", "default");
			if (rm.isStart)
			{
				n.addAttribute("ui.class", "isStart");
			}
			else if (rm.isEnd)
			{
				n.addAttribute("ui.class", "isEnd");
			}
		}
		for (Room rm : lem.listRooms)
		{
			for (Room rm2 : rm.neighboors)
			{
				try
				{
					graph.addEdge(rm.id + "-" + rm2.id, rm.id, rm2.id);
				}
				catch(Exception e)
				{
				}
			}
		}

		graph.display(true);

		sleep(2);

		// Turn loop
		int nb_turn = 0;

		while (true)
		{
			boolean end = true;

			for (Node n : graph.getEachNode())
			{
				String type = n.getAttribute("ui.class");
				if ((type.equals("isStart") || type.equals("isEnd")) == false)
				{
					n.setAttribute("ui.class", "default");
				}
			}
			nb_turn++;
			for (Ant an : lem.listAnts)
			{
				Room rm = an.listMap.get(nb_turn);
				if (rm != null)
				{
					end = false;
					Node n = graph.getNode(rm.id);
					if (n.getAttribute("ui.class").equals("isEnd") == false)
						n.setAttribute("ui.class", "marked");
				}
			}
			sleep(1);
			if (end)
				break ;
		}
	}

	public static void sleep(int sec)
	{
		try
		{
			Thread.sleep(sec * 1000);
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
}
