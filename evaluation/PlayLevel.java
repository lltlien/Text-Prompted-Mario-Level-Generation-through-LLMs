import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import engine.core.MarioGame;
import engine.core.MarioResult;

public class PlayLevel {
    public static void printResults(MarioResult result) {
        System.out.println("****************************************************************");
        System.out.println("Game Status: " + result.getGameStatus().toString() +
                " Percentage Completion: " + result.getCompletionPercentage());
        System.out.println("Lives: " + result.getCurrentLives() + " Coins: " + result.getCurrentCoins() +
                " Remaining Time: " + (int) Math.ceil(result.getRemainingTime() / 1000f));
        System.out.println("Mario State: " + result.getMarioMode() +
                " (Mushrooms: " + result.getNumCollectedMushrooms() + " Fire Flowers: " + result.getNumCollectedFireflower() + ")");
        System.out.println("Total Kills: " + result.getKillsTotal() + " (Stomps: " + result.getKillsByStomp() +
                " Fireballs: " + result.getKillsByFire() + " Shells: " + result.getKillsByShell() +
                " Falls: " + result.getKillsByFall() + ")");
        System.out.println("Bricks: " + result.getNumDestroyedBricks() + " Jumps: " + result.getNumJumps() +
                " Max X Jump: " + result.getMaxXJump() + " Max Air Time: " + result.getMaxJumpAirTime());
        System.out.println("****************************************************************");
    }

    public static String getLevel(String filepath) {
        String content = "";
        try {
            content = new String(Files.readAllBytes(Paths.get(filepath)));
        } catch (IOException e) {
        }
        return content;
    }

    public static void playLevel(MarioGame game, String level) {
        System.out.println("Running Interactive Play!");
        System.out.println("=========================");
        printResults(game.playInteractive(new agents.human.Agent(), level, 200, 999));
    }
    public static void playLevel(MarioGame game, String level, String imgDir) {
        System.out.println("Running Interactive Play!");
        System.out.println("=========================");
        printResults(game.playInteractive(new agents.human.Agent(), level, 200, 999, imgDir));
    }

    public static void main(String[] args) {
        MarioGame game = new MarioGame();
        // String levelPath = args[0];
        // if (args.length == 2) {
        //     // this means we passed in an imageDir
        //     String imgDir = args[1];
        //     playLevel(game, levelPath, imgDir);
        // } else {
            String level = "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n" + //
                    "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n" + //
                    "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n" + //
                    "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n" + //
                    "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n" + //
                    "------------------------------------------------------------------------------------------------------------------------------------------------k---------------------------------------k-----------\r\n" + //
                    "---------------------------------------------------------------------------1-------USS------------------SSQSSS?SSS--------SSC------------------SQS--SQS--------------------------------##-----------\r\n" + //
                    "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------###-----------\r\n" + //
                    "-------------------------------------------------------------------------------------------------------------------------------------g#---------------------------------#-----------k####-----------\r\n" + //
                    "------------Q--?-----------------------------------------------------------ggg----------------------------K---------------SSS-------g##---------------------------k-----#-----------#####-----------\r\n" + //
                    "---------Q---------SSS---------TT---------------------S--------------##########---#-------------TT------SSSSSSSSSSS-----------------###--------SQS--S?S--------SCSSS----#----------######-----------\r\n" + //
                    "---------------------K---TT----TT-----------------TT----------------##--------#---#-------------TT---------------------------------####--------------------------K-----##---------#######-----------\r\n" + //
                    "-------------------------TT----TT-----------------TT--------TT-----###--------#---##------------TT--------------------------------#####--------------------------------##--------########--------F--\r\n" + //
                    "-M----------------K------TT---gTT--------------gggTT------k-TT----####--------#---##--gg----k---TT--------------K----------------######------k------ggg--------K---K---##-------#########--------#--\r\n" + //
                    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX---XXXXXXXXXXXXXXXXXXXXXXXXXXXXX--------X---XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX----XXXXXXXXXX--XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX---XXXXXXXXXXXXXXXXXXXXXXXX\r\n" + //
                    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX---XXXXXXXXXXXXXXXXXXXXXXXXXXXXX--------X---XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX----XXXXXXXXXX--XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX---XXXXXXXXXXXXXXXXXXXXXXXX";
            playLevel(game, level);
        // }
    }
}
