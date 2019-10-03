import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.lang.Math;
import java.text.DecimalFormat;
import java.util.concurrent.TimeUnit;

/*<applet code="meArmApplet" width=1000 height=800></applet>*/

public class armapplet  extends Applet implements ActionListener
{
   DecimalFormat df = new DecimalFormat("######.##");
	TextField xinput,yinput,output1,output2,output3;
   Button compute;
	final double bicep = 81, forearm=81;
	final double bicepsq = Math.pow(81,2), forearmsq = Math.pow(81,2);
   double fact=0;
	double x=0,y=0;
	double q1=0,q2=0;
	double a1, a2;
	double b=0, bsq=0;
	double olda1=0,oldq1=0;
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
	}
   public void actionPerformed(ActionEvent ae)
   {  
		olda1=a1;
		oldq1 = q1;
   	String str=ae.getActionCommand();
     	if(str.equals("Compute"))
      {
			x=Double.parseDouble(xinput.getText());
			y=Double.parseDouble(yinput.getText());
			bsq = Math.pow(x,2.0) + Math.pow(y,2.0);
			b = Math.hypot(x,y);
			q1 = Math.atan2(y,x);
			q2 = Math.acos((bsq+bicepsq-forearmsq)/(2*forearm*b));
			a1 = (q1+q2);  //in radians
			a2 = (Math.acos((bicepsq+forearmsq-bsq)/(2*forearm*bicep)));
			olda1 = a1;
			oldq1 = q1;
         if(bsq<=26406)
         {  
				fact=1;
         	output1.setText(""+df.format(b));
				output2.setText(""+df.format(Math.toDegrees(a1)));
				output3.setText(""+df.format(Math.toDegrees(a2)));
         }
         else
        		fact=-1;                         
      }
		repaint();
	}
   public void paint(Graphics g)
   {         
   	if(fact==-1) 
		{
      	output1.setText("0");
         g.drawString("Sorry, this point is unreachable with this arm",10,200); 
		}
		else if(fact >0);
		{
			g.fillRect(230,780,160,13);
			g.drawOval(275,770,20,20);
			double red=0, green=0,blue=0;
			double frequency=.05;
			double freq =1;
			double olddega1=Math.toDegrees(olda1);
			double dega1= Math.toDegrees(a1);
			double olddegq1= Math.toDegrees(oldq1);
			double degq1=Math.toDegrees(q1);
			int i=0;
					g.drawLine(285,780,285+((int)((3*bicep*Math.cos(a1)))),780-((int)(3*bicep*Math.sin(a1))));
					g.drawLine(285+((int)(3*bicep*Math.cos(a1))),780-((int)(3*bicep*Math.sin(a1))),285+((int)(3*b*(Math.cos(q1)))),780-((int)((3*b*Math.sin(q1))))); 
					g.drawOval(275,770,20,20);
 					g.drawOval(275+(int)((3*bicep*Math.cos(a1))),770-(int)(3*bicep*Math.sin(a1)),20,20);
					g.fillRect(230,780,160,13);
			//	update(g);
				//g.setPaintMode();
				System.out.println("olda1: "+olda1+" --> a1: "+a1+"     oldq1: "+oldq1+" --> q1: " +q1);

			}
			/*g.fillRect(230,780,160,13);
			g.drawOval(275,770,20,20);
			g.drawLine(285,780,285+((int)((3*bicep*Math.cos(a1)))),780-((int)(3*bicep*Math.sin(a1))));
			//repaint();                //bicep
			g.drawOval(275+(int)((3*bicep*Math.cos(a1))),770-(int)(3*bicep*Math.sin(a1)),20,20);	 
			g.drawLine(285+((int)(3*bicep*Math.cos(a1))),780-((int)(3*bicep*Math.sin(a1))),285+((int)(3*b*(Math.cos(q1)))),780-((int)((3*b*Math.sin(q1)))));  //forearm*/
	}
}
/*
			while((int)olddega1<=(int)dega1)
			{
				oldq1=Math.toRadians(olddegq1);
				olda1=Math.toRadians(olddega1);
			   oldx=
				oldy=
				bsq = Math.pow(x,2.0) + Math.pow(y,2.0);
				b = Math.hypot(x,y);
				q1 = Math.atan2(y,x);
				q2 = Math.acos((bsq+bicepsq-forearmsq)/(2*forearm*b));
				a1 = (q1+q2);  //in radians
				a2 =( Math.acos((bicepsq+forearmsq-bsq)/(2*forearm*bicep)));
				   red   = Math.sin(frequency*i + 0) * 127 + 128;
 					green = Math.sin(frequency*i + 2) * 127 + 128;
  					blue  = Math.sin(frequency*i + 4) * 127 + 128;	
					i++;
					//g.setColor(new Color((int)red,(int)green,(int)blue));
					//g.drawLine(285,780,285+((int)((3*bicep*Math.cos(olda1)))),780-((int)(3*bicep*Math.sin(olda1))));
					//g.drawLine(285+((int)(3*bicep*Math.cos(olda1))),780-((int)(3*bicep*Math.sin(olda1))),285+((int)(3*b*(Math.cos(oldq1)))),780-((int)((3*b*Math.sin(oldq1))))); 
					//g.setColor(Color.black);
					//g.drawOval(275,770,20,20);
 					//g.drawOval(275+(int)((3*bicep*Math.cos(olda1))),770-(int)(3*bicep*Math.sin(olda1)),20,20);
					//g.fillRect(230,780,160,13);
				if((int)olddegq1<(int)degq1)
	  			{System.out.print("   w1 i1   ");
					g.setColor(new Color((int)red,(int)green,(int)blue));
					g.drawLine(285,780,285+((int)((3*bicep*Math.cos(olda1)))),780-((int)(3*bicep*Math.sin(olda1))));
					g.drawLine(285+((int)(3*bicep*Math.cos(olda1))),780-((int)(3*bicep*Math.sin(olda1))),285+((int)(3*b*(Math.cos(oldq1)))),780-((int)((3*b*Math.sin(oldq1))))); 
					g.setColor(Color.black);
					g.drawOval(275,770,20,20);
 					g.drawOval(275+(int)((3*bicep*Math.cos(olda1))),770-(int)(3*bicep*Math.sin(olda1)),20,20);
					g.fillRect(230,780,160,13);
					oldq1+=freq*(Math.PI/180); 
					olddegq1++;
				}
				else if((int)olddegq1>(int)degq1)
				{System.out.print("   w1 i2   ");
					g.setColor(new Color((int)red,(int)green,(int)blue));
					g.drawLine(285,780,285+((int)((3*bicep*Math.cos(olda1)))),780-((int)(3*bicep*Math.sin(olda1))));
					g.drawLine(285+((int)(3*bicep*Math.cos(olda1))),780-((int)(3*bicep*Math.sin(olda1))),285+((int)(3*b*(Math.cos(oldq1)))),780-((int)((3*b*Math.sin(oldq1))))); 
					g.setColor(Color.black);
					g.drawOval(275,770,20,20);
 					g.drawOval(275+(int)((3*bicep*Math.cos(olda1))),770-(int)(3*bicep*Math.sin(olda1)),20,20);
					g.fillRect(230,780,160,13);
					oldq1-=freq*(Math.PI/180); 
					olddegq1--;
				}
				olda1+=freq*(Math.PI/180); 
				olddega1++;
				try {
    				Thread.sleep(5);
				} catch(InterruptedException ex) {
    				Thread.currentThread().interrupt();
				}
				System.out.println("olda1: "+olda1+" --> a1: "+a1+"     oldq1: "+oldq1+" --> q1: " +q1);
			}
			while((int)olddega1>(int)dega1)
			{				
					oldq1=Math.toRadians(olddegq1);
					olda1=Math.toRadians(olddega1);

				   red   = Math.sin(frequency*i + 0) * 127 + 128;
 					green = Math.sin(frequency*i + 2) * 127 + 128;
  					blue  = Math.sin(frequency*i + 4) * 127 + 128;	
					i++;
					//g.setColor(new Color((int)red,(int)green,(int)blue));
					//g.drawLine(285,780,285+((int)((3*bicep*Math.cos(olda1)))),780-((int)(3*bicep*Math.sin(olda1))));
					//g.drawLine(285+((int)(3*bicep*Math.cos(olda1))),780-((int)(3*bicep*Math.sin(olda1))),285+((int)(3*b*(Math.cos(oldq1)))),780-((int)((3*b*Math.sin(oldq1))))); 
					//g.setColor(Color.black);
					//g.drawOval(275,770,20,20);
 					//g.drawOval(275+(int)((3*bicep*Math.cos(olda1))),770-(int)(3*bicep*Math.sin(olda1)),20,20);
					//g.fillRect(230,780,160,13);
				if((int)olddegq1<(int)degq1)
	  			{System.out.print("   w2 i1   ");
					g.setColor(new Color((int)red,(int)green,(int)blue));
					g.drawLine(285,780,285+((int)((3*bicep*Math.cos(olda1)))),780-((int)(3*bicep*Math.sin(olda1))));
					g.drawLine(285+((int)(3*bicep*Math.cos(olda1))),780-((int)(3*bicep*Math.sin(olda1))),285+((int)(3*b*(Math.cos(oldq1)))),780-((int)((3*b*Math.sin(oldq1))))); 
					g.setColor(Color.black);
					g.drawOval(275,770,20,20);
 					g.drawOval(275+(int)((3*bicep*Math.cos(olda1))),770-(int)(3*bicep*Math.sin(olda1)),20,20);
					g.fillRect(230,780,160,13);
					oldq1+=freq*(Math.PI/180); 
					olddegq1++;
				}
				else if((int)olddegq1>(int)degq1)
				{System.out.print("   w2 i2   ");
					g.setColor(new Color((int)red,(int)green,(int)blue));
					g.drawLine(285,780,285+((int)((3*bicep*Math.cos(olda1)))),780-((int)(3*bicep*Math.sin(olda1))));
					g.drawLine(285+((int)(3*bicep*Math.cos(olda1))),780-((int)(3*bicep*Math.sin(olda1))),285+((int)(3*b*(Math.cos(oldq1)))),780-((int)((3*b*Math.sin(oldq1))))); 
					g.setColor(Color.black);
					g.drawOval(275,770,20,20);
 					g.drawOval(275+(int)((3*bicep*Math.cos(olda1))),770-(int)(3*bicep*Math.sin(olda1)),20,20);
					g.fillRect(230,780,160,13);
					oldq1-=(Math.PI/180); 
					olddegq1--;
				} 
				olda1-=freq*(Math.PI/180); 
				olddega1--;
				try {
    				Thread.sleep(5);
				} catch(InterruptedException ex) {
    				Thread.currentThread().interrupt();
				}

*/
