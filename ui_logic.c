// created by emacs {navid  oct 25 2014}

#include <gtk/gtk.h>
#include <glib.h>
#include "ui_logic.h"
#include "ui_signals.h"


int main(int argc, char **argv)
{
	GtkWidget *mainwin, *graphwin;
	GtkWidget *frame;
	GtkWidget *drawing_area;
	GtkBuilder *builder;
	GtkWidget *frame_from_ui;
	GtkRequisition *minimum_size_for_frame_ui;
	GtkSpinButton *input_numofants, *input_numofedges, *input_numofvertices,
	    *input_evaporation_rate;
	GtkButton *button_solve_problem , *button_generating_random_graph;
	GtkToggleButton *button_drawing_mode;
	GPtrArray *widget_array;
	GtkAdjustment *adjustment_input_numofvertices,*adjustment_input_numofants,*adjustment_evaporation_rate,*adjustment_input_numofedges;
	_mode mode = RANDOM_MODE;

	ui_points = g_array_sized_new(FALSE,TRUE,sizeof(struct _points),RESERVED_SIZE_OF_ARRAY_POINTS);
	if(!ui_points)
		g_error("ui_points is null , fatal error in line:%d.",__LINE__);
	// array for capsulizing information in widget_array for signal
	widget_array = g_ptr_array_new();

	gtk_init(&argc, &argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, mainwin_ui_name, NULL);
	mainwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	graphwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	// after loading frame_from_ui,load it to mainwin
	frame_from_ui = gtk_builder_get_object(builder, mainwin_ui_frame_name);
	gtk_container_add(GTK_CONTAINER(mainwin), frame_from_ui);

	// getting preffered size from frame_from_ui for fixing size of mainwin currectly
	minimum_size_for_frame_ui = malloc(sizeof(GtkRequisition));
	gtk_widget_get_preferred_size(frame_from_ui, minimum_size_for_frame_ui,NULL);
	
	// loading objects from ui file
	input_numofants = gtk_builder_get_object(builder,input_numofants_name);
	input_numofedges = gtk_builder_get_object(builder,input_numofedges_name);
	input_numofvertices = gtk_builder_get_object(builder,input_numofvertices_name);
	input_evaporation_rate = gtk_builder_get_object(builder,input_evaporation_rate_name);
	button_solve_problem = gtk_builder_get_object(builder,button_solve_problem_name);
	button_drawing_mode = gtk_builder_get_object(builder,button_drawing_mode_name);
	button_generating_random_graph = gtk_builder_get_object(builder,button_generating_random_graph_name);
	
	// setting for object loaded from ui file
	adjustment_input_numofvertices = gtk_adjustment_new(MIN_NUMOFVERTICES,MIN_NUMOFVERTICES,MAX_NUMOFVERTICES,INCREMENT_RATE,ZERO,ZERO);
	adjustment_input_numofedges = gtk_adjustment_new(DEFAULT_NUMOFEDGES,DEFAULT_NUMOFEDGES,ZERO,ZERO,ZERO,ZERO);
	adjustment_input_numofants = gtk_adjustment_new(MIN_NUMOFANTS,MIN_NUMOFANTS,MAX_NUMOFANTS,INCREMENT_RATE,ZERO,ZERO);
	adjustment_evaporation_rate = gtk_adjustment_new(MIN_EVAPORATION_RATE,MIN_EVAPORATION_RATE,MAX_EVAPORATION_RATE,INCREMENT_RATE,ZERO,ZERO);
	gtk_spin_button_set_adjustment(input_numofvertices,adjustment_input_numofvertices);
	gtk_spin_button_set_adjustment(input_numofedges,adjustment_input_numofedges);
	gtk_spin_button_set_adjustment(input_numofants,adjustment_input_numofants);
	gtk_spin_button_set_adjustment(input_evaporation_rate,adjustment_evaporation_rate);

	// setting some options of graphwin and mainwin
	gtk_window_set_title(GTK_WINDOW(mainwin), mainwin_title);
	gtk_window_set_title(GTK_WINDOW(graphwin), graphwin_title);
	gtk_widget_set_size_request(graphwin, GRAPH_WIN_WIDTH,GRAPH_WIN_HEIGHT);
	gtk_widget_set_size_request(mainwin, minimum_size_for_frame_ui->width,minimum_size_for_frame_ui->height);
	gtk_window_set_resizable(GTK_WINDOW(mainwin), RESIZABLE);
	gtk_window_set_resizable(GTK_WINDOW(graphwin), RESIZABLE);
	frame = gtk_frame_new(NULL);
	// gtk_frame_set_shadow only accept frame as first argumant , should not send window
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
	gtk_container_add(GTK_CONTAINER(graphwin), frame);
	drawing_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(drawing_area, DRAWING_AREA_WIDTH,DRAWING_AREA_HEIGHT);
	gtk_container_add(GTK_CONTAINER(frame), drawing_area);

	// adding BUTTON PRESS AND MOTION MASK to gtk events
	gtk_widget_set_events(drawing_area,gtk_widget_get_events(drawing_area) | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);

	// signals
	g_signal_connect(mainwin, EVENT_DESTROY, G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(graphwin, EVENT_DESTROY, G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(graphwin, EVENT_CONFIGURE_EVENT, G_CALLBACK(on_configure_event), NULL);
	g_signal_connect(drawing_area, EVENT_MOTION_NOTIFY_EVENT,G_CALLBACK(on_motion_notify_event), NULL);
	g_signal_connect(drawing_area, EVENT_BUTTON_PRESS_EVENT,G_CALLBACK(on_button_press_event), &mode);
	g_signal_connect(drawing_area, EVENT_DRAW, G_CALLBACK(on_draw), NULL);
	g_signal_connect(mainwin, EVENT_DELETE_EVENT, G_CALLBACK(on_delete_event),NULL);
	
	// widget_array initialize
	// passing array of {mode,GtkWidget(input_numofvertices),GtkWidget(input_numofedges)} to singal for GtkToggleButton
	g_ptr_array_add(widget_array,&mode);
	g_ptr_array_add(widget_array,input_numofvertices);
	g_ptr_array_add(widget_array,input_numofedges);
	
	// signal for object loaded from builder
	g_signal_connect(button_drawing_mode,EVENT_TOGGLED,G_CALLBACK(on_toggled_button_drawing_mode),widget_array);
	g_signal_connect(button_solve_problem,EVENT_CLICKED,G_CALLBACK(on_clicked_button_solve_problem),NULL);
	g_signal_connect(button_generating_random_graph,EVENT_CLICKED,G_CALLBACK(on_clicked_button_generating_random_graph),NULL);
	g_signal_connect(input_numofvertices,EVENT_VALUE_CHANGED,G_CALLBACK(on_value_changed_input_numofvertices),input_numofedges);

	// g_signal_connect(graphwin,"clicked",G_CALLBACK(graph_window_clicked),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(graphwin),GRAPH_WIN_CONTAINER_BORDER_WIDTH);

	gtk_widget_show(mainwin);
	gtk_widget_show_all(graphwin);

	gtk_main();
	return 0;
}