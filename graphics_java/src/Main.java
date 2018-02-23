package src;

import java.util.Random;
import org.graphstream.graph.*;
import org.graphstream.graph.implementations.*;


public class Main
{
	private static final String style = getStyleSheet();
	private static final int nb_colors = 10;

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
			n.addAttribute("link_room", rm);
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
				catch (Exception e)
				{
					System.err.println("SNA : Creating Edge " + rm.id + "-" + rm2.id);
				}
			}
		}

		graph.display(true);
		sleep(3);

		int nb_turn = 0;

		while (true)
		{
			nb_turn++;
			sleep(2);
			if (turn_loop(nb_turn, graph, lem))
				break ;
		}
	}

	public static boolean turn_loop(int nb_turn, Graph graph, Lemin lem)
	{
		boolean end = true;

		for (Node n : graph.getEachNode())
		{
			String type = n.getAttribute("ui.class");
			if ((type.equals("isStart") || type.equals("isEnd")) == false)
			{
				n.setAttribute("ui.class", "default");
				n.setAttribute("ui.label", ((src.Room)n.getAttribute("link_room")).id);
			}
		}
		for (Ant an : lem.listAnts)
		{
			Room rm = an.listMap.get(nb_turn);
			if (rm != null)
			{
				end = false;
				Node n = graph.getNode(rm.id);
				if (n.getAttribute("ui.class").equals("isEnd") == false)
				{
					n.setAttribute("ui.class", "marked" + ((an.id - 1) % nb_colors));
					n.setAttribute("ui.label", n.getAttribute("ui.label") + " <=> " + an.id);
				}
			}
		}
		return (end);
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

	private static String getStyleSheet()
	{
		String normalStyle = 
					"node {" +
					"	shape: box;" +
				    "	fill-color: black;" +
				    "	text-mode: normal;" +
				    "	text-color: blue;" +
				    "}" +
				    "node.isStart {" +
				    "	fill-color: green;" +
				    "}" +
				    "node.isEnd {" +
				    "	fill-color: red;" +
				    "}" +
				    "edge {" +
				    "	fill-color: black;" +
				    "}";
		Random ran = new Random();
		for (int i = 1; i <= nb_colors; i++)
		{
			int r = ran.nextInt(8) * 16 + 4 * 16;
			int g = ran.nextInt(8) * 16 + 4 * 16;
			int b = ran.nextInt(8) * 16 + 8 * 16;

			normalStyle +=
				"node.marked" + i + " {" + 
				"	fill-color: rgb(" + r + ", " + g + ", " + b + ");" +
				"}";
		}
		return (normalStyle);
	}
}
