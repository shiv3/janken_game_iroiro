using System;

namespace waza_janken
{
	public class State
	{
		public int hp;
		public int atk;
		public int def;
		public State (int hp,int atk,int def)
		{
			this.hp = hp;
			this.atk = atk;
			this.def = def;
		}
	}

	//  各モンスターと技が持つタイプ
	public abstract class Type
	{
		public string name;
		public abstract State _do (int hp, int atk, int defence);
	}

	public class Gu : Type
	{
		public Gu () {this.name = "gu";}
		public override State _do (int hp,int atk,int defence)
		{
			return new State (hp,atk/2,defence*2);
		}
	}
	
	public class Cho : Type
	{
		public Cho () {this.name = "cho";}
		public override State _do (int hp,int atk,int defence)
		{
			return new State(hp,atk*2,defence/2);
		}
	}
	
	public class Pa : Type
	{
		public Pa () {this.name = "pa";}
		public override State _do (int hp,int atk,int defence)
		{
			return new State (hp*4,atk/2,defence/2);
		}
	}

	// 各モンスターが持つ技
	public class Waza
	{
		public string name;
		public Type type;

		public Waza () {}
		public Waza (string name) {this.name = name;}

		public virtual int _do(Monster m,Monster e)
		{
			Game game = new Game ();
			Console.WriteLine (m.name + "の" + this.name + "!");

			string wazatype = this.type.name;
			string entype = e.type.name;
			return game.judge (this.type.name,e.type.name);
		}
	}

	public class Kirisaku : Waza
	{
		public Kirisaku()
		{
			this.name = "きりさく";
			this.type = new Cho ();
		}
		public override int _do (Monster m,Monster e)
		{
			int state = base._do (m,e);
			switch (state)
			{
			case 1:
				Console.WriteLine ("勝ち");
				Console.WriteLine ("攻撃力×2!"); 
				e.damage (m.atk*2);
				break;
			case -1:
				Console.WriteLine ("負け");
				e.damage (m.atk/2);
				break;
			default:
				Console.WriteLine ("あいこ");
				break;
			}
			return state;
		}
	}
	
	public class Knuckle : Waza
	{
		public Knuckle()
		{
			this.name = "ナックルパンチ";
			this.type = new Gu ();
		}
		public override int _do (Monster m,Monster e)
		{
			int state = base._do (m,e);
			switch (state) {
			case 1:
				Console.WriteLine ("勝ち");
				Console.WriteLine ("攻撃力×2!"); 
				e.damage (m.atk*2);
				break;
			case -1:
				Console.WriteLine ("負け");
				e.damage (m.atk/2);
				break;
			default:
				Console.WriteLine ("あいこ");
				break;
			}
			return state;
		}
	}

	public class Henka : Waza
	{
		public Henka ()
		{
		}
		public override int _do (Monster m,Monster e)
		{
			return 0;
		}
	}

	public class Monster
	{
		public string name;
		public int hp;
		public int atk;
		public int def;
		public Type type;
		public Type type2;
		public Waza waza1;
		public string status;

		public int damage (int hp_damage)
		{
			int damage = hp_damage - this.def;
			if (damage > 0) {
				Console.WriteLine (this.name + "に" + damage + "のダメージ");
				if (this.hp < damage) {
					Console.WriteLine ("死");
					this.status = "死";
					this.hp = 0;
					return 0;
				}

				this.hp -= damage;
			} else {
				Console.WriteLine (this.name+"に0のダメージ");
			}

			return this.hp;
		}

		public void show_status ()
		{
			Console.WriteLine ("-------");
			Console.WriteLine ("name:" + this.name);
			Console.WriteLine ("hp:" + this.hp);
			Console.WriteLine ("atk:" + this.atk);
			Console.WriteLine ("def:" + this.def);
			Console.WriteLine ("type:" + this.name);
			Console.WriteLine ("status:" + this.status);
			Console.WriteLine ("-------");
		}
	}

	public class Slime : Monster
	{
		public Slime ()
		{
			this.name = "スライム";
			this.hp = 5;
			this.atk = 5;
			this.def = 5;
			this.type = new Gu ();
			this.waza1 = new Knuckle  ();
		}
	}

	public class SlimeBes : Slime
	{
		public SlimeBes ()
		{
			this.name = "スライムベス";
			this.hp *= 2;
			this.atk *= 2;
			this.def *= 2;
			this.type2 = new Pa ();
		}
	}

	public class Drakee : Monster
	{
		public Drakee ()
		{
			this.name = "ドラキー";
			this.hp = 4;
			this.atk = 6;
			this.def = 5;
			this.type = new Cho ();
			this.waza1 = new Kirisaku ();
		}
	}
	
	public class Nyan : Monster
	{
		public Nyan ()
		{
			this.name = "プリズニャン";
			this.hp = 10;
			this.atk = 3;
			this.def = 2;
			this.type = new Pa ();
		}
	}

	public class Game
	{
		public int judge (string j1,string j2)
		{
			if(j1==j2){
				return 0;
			}else if(j1=="gu"){
				return j2=="cho" ? 1: -1;
			}else if(j1=="cho"){
				return j2=="pa" ? 1 : -1;
			}else if(j1=="pa"){
				return j2=="gu" ? 1 : -1;
			}
			return 0;
		}
	}

	public class MainClass
	{
		public static void Main (string[] argv)
		{
			Monster s = new Slime();
			Monster d = new Drakee();
			Monster b = new SlimeBes();
			Nyan p = new Nyan();
			d.show_status();
			s.show_status();
			d.waza1._do(d,s);
			s.waza1._do(s,d);
			d.show_status();
			s.show_status();
		}
	}
}

