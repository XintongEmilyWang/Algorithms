package epidemic;

import java.util.HashSet;

public class SIRS {
	static class Node{
		public State state;
		public final String name;
		public int trans;
		public final HashSet<Edge> inEdges;
		public final HashSet<Edge> outEdges;
		public Node(String name, State state){
			this.name = name;
			this.state = state;
			trans = 0;
			inEdges = new HashSet<Edge>();
			outEdges = new HashSet<Edge>();
		}
		public Node addEdge(Node node){
			Edge e = new Edge(this, node);
			outEdges.add(e);
			node.inEdges.add(e);
			return this;
		}		
	}

	static class Edge{
		public final Node from;
		public final Node to;
		public Edge(Node from, Node to) {
			this.from = from;
			this.to = to;
		}
		@Override
		public boolean equals(Object obj) {
			Edge e = (Edge)obj;
			return e.from == from && e.to == to;
		}
	}
	//Transition is the state from susceptible to Infectious
	public enum State{Susceptible, Transition, Infectious, Removed};
	public static int T1 = 4;//time remains infected before removed, subject to change
	public static int T2 = 4;//time remains removed before susceptible, subject to change
	public static double prob = 0.25;
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int time = 0;
		//set up graph
		Node r = new Node("r", State.Susceptible);
		Node s = new Node("s", State.Susceptible);
		Node t = new Node("t", State.Susceptible);
		Node u = new Node("u", State.Susceptible);
		Node v = new Node("v", State.Susceptible);
		Node w = new Node("w", State.Susceptible);
		Node x = new Node("x", State.Susceptible);
		Node y = new Node("y", State.Infectious);
		Node z = new Node("z", State.Infectious);
		HashSet<Node> graph = new HashSet<Node>();
		graph.add(r);
		graph.add(s);
		graph.add(t);
		graph.add(u);
		graph.add(v);
		graph.add(w);
		graph.add(x);
		graph.add(y);
		graph.add(z);
		r.addEdge(s);
		s.addEdge(t);
		t.addEdge(u);
		u.addEdge(v);
		v.addEdge(w);
		w.addEdge(r);
		x.addEdge(y);
		x.addEdge(r);
		y.addEdge(t);
		y.addEdge(z);
		z.addEdge(x);
		z.addEdge(v);
		
		while (true){
			boolean spread = false;
			for(Node n: graph){
				if (n.state == State.Infectious){					
					spread = true;
					System.out.println("Node " + n.name + " is in infected state at time " + time + "!");
					HashSet<Node> neighbor = new HashSet<Node>();
					for(Edge e: n.outEdges){
						neighbor.add(e.to);
						if(e.to.state == State.Susceptible){
							System.out.println("Node " + n.name + " has potential infecting neighbor " + e.to.name + "!");
						}
					}

					for(Node node: neighbor){
						if(node.state == State.Susceptible){
							if ((Math.random()*100) < (prob*100)){
								node.state = State.Transition;
								System.out.println("Node " + node.name + " will get infected at time " + (time+1) + "!");
							}
						}else{
							continue;
						}
					}
				}
			}
			
			//if none of the node is infectious, the disease dies out
			if(!spread){
				System.out.println("The disease dies out at time " + time + "!");
				break;
			}
			
			time++;
			
			for(Node i: graph){
				if(i.state == State.Removed){
					i.trans++;
					if(i.trans == T2){
						i.state = State.Susceptible;
						System.out.println("Node " + i.name + " turns from removed to susceptible state at time " + time + "!");
						i.trans = 0;
					}else{
						System.out.println("Node " + i.name + " is in removed state at time " + time + "!");
					}
				}else if (i.state == State.Transition){
					i.state = State.Infectious;
					System.out.println("Node " + i.name + " is infected at time " + time + "!");
				}else if(i.state == State.Infectious){
					i.trans++;
					if(i.trans == T1){
						i.state = State.Removed;
						System.out.println("Node " + i.name + " is in removed state at time " + time + "!");
						i.trans = 0;
					}
				}
			}
		}
	}

}
