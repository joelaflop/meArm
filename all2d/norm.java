import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.lang.Math;
import java.text.DecimalFormat;
import java.util.concurrent.TimeUnit;

/*<applet code="norm" width=1000 height=800></applet>*/

public class norm extends Applet implements ActionListener//, MouseListener
{
   DecimalFormat df = new DecimalFormat("######.##");
	TextField xinput,yinput,output1,output2,output3;
   Button compute;
	final double bicep = 81, forearm=81;
	final double bicepsq = Math.pow(bicep,2), forearmsq = Math.pow(forearm,2);
   double fact=0;
	double x=0,y=0;
	double oldx=0,oldy=0;
	double q1=0,q2=0;
	double a1, a2;
	double b=0, bsq=0;
	double olda1=0,oldq1=0;
	double werk;
	int mousex, mousey;
   public void init()
   {
		setBackground(Color.white);
		Panel firstRow = new Panel();
		Panel secondRow = new Panel();
		Panel thirdRow = new Panel();
		Panel fourthRow = new Panel();

		compute=new Button("Compute");
      Label xinp=new Label("Enter x component :");
		Label yinp=new Label("Enter y component:");
      Label opt1=new Label("The distance reached is: ");
		Label opt2=new Label("The first angle is: ");
		Label opt3=new Label("The second angle is: ");
      xinput=new TextField(10);
		yinput = new TextField(10);
      output1=new TextField(10);
		output2=new TextField(10);
		output3=new TextField(10);
		//MouseListener mice = new MouseListener();

      firstRow.add(xinp);
      firstRow.add(xinput);
		firstRow.add(yinp);
		firstRow.add(yinput);
		secondRow.add(compute);
      thirdRow.add(opt1);
      thirdRow.add(output1);
      fourthRow.add(opt2);
      fourthRow.add(output2);     
		fourthRow.add(opt3);
      fourthRow.add(output3);

      output1.setEditable(false);
      output2.setEditable(false);
      output3.setEditable(false);
		xinput.setText("0");
		yinput.setText("0");
      xinput.addActionListener(this);
		yinput.addActionListener(this);
      output1.addActionListener(this);
      output2.addActionListener(this);
      output3.addActionListener(this);
      compute.addActionListener(this);
		add(firstRow);
		add(secondRow);
		add(thirdRow);
		add(fourthRow);
		//addMouseListener(mice);
	}
	/*public norm()
	{
		norm.addMouseListener(this);

	}
	public void mousePressed(MouseEvent event)
	{
		mousex = event.getX();
		mousey = event.getY();	
	}*/
   public void actionPerformed(ActionEvent ae)
   {  
		olda1=a1;
		oldq1 = q1;
   	String str=ae.getActionCommand();
     	if(str.equals("Compute"))
      {
			oldx=x;
			oldy=y;
			x=Double.parseDouble(xinput.getText());
			y=Double.parseDouble(yinput.getText());
			werk = Math.sqrt((x*x)+(y*y));
         if(werk<=162)
         {  
				fact=1;
				bsq = Math.pow(x,2.0) + Math.pow(y,2.0);
				b = Math.hypot(x,y);
				q1 = Math.atan2(y,x);
				q2 = Math.acos((bsq+bicepsq-forearmsq)/(2*forearm*b));
				a1 = (q1+q2);  //in radians
				a2 =( Math.acos((bicepsq+forearmsq-bsq)/(2*forearm*bicep)));
         	output1.setText(""+df.format(b));
				output2.setText(""+df.format(Math.toDegrees(a1)));
				output3.setText(""+df.format(Math.toDegrees(a2)));
         }
         else
			{
        		fact=-1;
				x=oldx;
				y=oldy;
			}                         
      }
	repaint();
	}
   public void paint(Graphics g)
   {         
		if(fact>0 && werk<=162);
		{
			g.fillRect(230,680,160,13);
			g.drawOval(275,670,20,20);
			double nx,ny;
			double mx, my;
			double i=0;
			double step = .5;
			double tempb = b;
			Dimension d = getSize();
			g.fillRect(230,680,160,13); 
			g.drawOval(275,670,20,20);
			for(double j=0;j<b && werk<=162;j+=step)
			{
				nx = oldx + (x-oldx)*j/b;
				ny = oldy + (y-oldy)*j/b;
				bsq = Math.pow(nx,2.0) + Math.pow(ny,2.0);
				b = Math.hypot(nx,ny);
				q1 = Math.atan2(ny,nx);
				q2 = Math.acos((bsq+bicepsq-forearmsq)/(2*forearm*b));
				a1 = (q1+q2);  //in radians	
				a2 =(Math.acos((bicepsq+forearmsq-bsq)/(2*forearm*bicep)));  //System.out.println("before draw");

				g.clearRect(0,0,d.width,d.height);
				g.fillRect(230,680,160,13); 
				g.drawOval(275,670,20,20);

				g.drawLine(285,680,285+((int)((3*bicep*Math.cos(a1)))),680-((int)(3*bicep*Math.sin(a1)))); //paintingggggg
				g.drawLine(285+((int)(3*bicep*Math.cos(a1))),680-((int)(3*bicep*Math.sin(a1))),285+((int)(3*b*(Math.cos(q1)))),680-((int)((3*b*Math.sin(q1))))); 	
 				g.drawOval(275+(int)((3*bicep*Math.cos(a1))),670-(int)(3*bicep*Math.sin(a1)),20,20);
				g.drawArc(284+((int)(3*b*(Math.cos(q1)))),647-((int)((3*b*Math.sin(q1)))),50,50,200,120);
				g.drawArc(284+((int)(3*b*(Math.cos(q1)))),647-((int)((3*b*Math.sin(q1)))),50,50,200,-170);
				//g.drawLine(285+((int)(3*b*(Math.cos(q1)))),680-((int)((3*b*Math.sin(q1)))),335+((int)(3*b*(Math.cos(q1)))),630-((int)((3*b*Math.sin(q1)))));

				try 
				{
    				Thread.sleep(20);
				}
				catch(InterruptedException ex) 
				{
    				Thread.currentThread().interrupt();
				}
				System.out.println("in for, j: "+j+"  nx: "+nx+"    ny: "+ny);
				

			}//for ends here
			bsq = Math.pow(x,2.0) + Math.pow(y,2.0);
			b = Math.hypot(x,y);
			q1 = Math.atan2(y,x);
			q2 = Math.acos((bsq+bicepsq-forearmsq)/(2*forearm*b));
			a1 = (q1+q2);  //in radians
			a2 =( Math.acos((bicepsq+forearmsq-bsq)/(2*forearm*bicep)));

			if(werk<=162)
			{	//paintingggggggg
				g.clearRect(0,0,d.width,d.height);
				g.drawLine(285,680,285+((int)((3*bicep*Math.cos(a1)))),680-((int)(3*bicep*Math.sin(a1))));
				g.drawLine(285+((int)(3*bicep*Math.cos(a1))),680-((int)(3*bicep*Math.sin(a1))),285+((int)(3*b*(Math.cos(q1)))),680-((int)((3*b*Math.sin(q1))))); 	
				g.drawOval(275,670,20,20);
 				g.drawOval(275+(int)((3*bicep*Math.cos(a1))),670-(int)(3*bicep*Math.sin(a1)),20,20);				
				g.fillRect(230,680,160,13); //System.out.println("after draw");	
				g.drawArc(284+((int)(3*b*(Math.cos(q1)))),647-((int)((3*b*Math.sin(q1)))),50,50,200,120);
				g.drawArc(284+((int)(3*b*(Math.cos(q1)))),647-((int)((3*b*Math.sin(q1)))),50,50,200,-170);
				//g.drawLine(285+((int)(3*b*(Math.cos(q1)))),680-((int)((3*b*Math.sin(q1)))),335+((int)(3*b*(Math.cos(q1)))),630-((int)((3*b*Math.sin(q1)))));
			}	
			else if(fact==-1||werk>162) 
			{
				g.clearRect(0,0,d.width,d.height);
    			output1.setText("0");
     			g.drawString("Sorry, this point is unreachable with this arm ;)",10,200); 
				g.drawLine(285,680,285+((int)((3*bicep*Math.cos(a1)))),680-((int)(3*bicep*Math.sin(a1))));
				g.drawLine(285+((int)(3*bicep*Math.cos(a1))),680-((int)(3*bicep*Math.sin(a1))),285+((int)(3*b*(Math.cos(q1)))),680-((int)((3*b*Math.sin(q1))))); 	
				g.drawOval(275,670,20,20);
 				g.drawOval(275+(int)((3*bicep*Math.cos(a1))),670-(int)(3*bicep*Math.sin(a1)),20,20);				
				g.fillRect(230,680,160,13); //System.out.println("after draw");	
				g.drawArc(284+((int)(3*b*(Math.cos(q1)))),647-((int)((3*b*Math.sin(q1)))),50,50,200,120);
				g.drawArc(284+((int)(3*b*(Math.cos(q1)))),647-((int)((3*b*Math.sin(q1)))),50,50,200,-170);
				//g.drawLine(285+((int)(3*b*(Math.cos(q1)))),680-((int)((3*b*Math.sin(q1)))),335+((int)(3*b*(Math.cos(q1)))),630-((int)((3*b*Math.sin(q1)))));
			}
		}
	}
}
