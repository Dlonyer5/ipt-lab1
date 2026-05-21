from django.http import JsonResponse

def user_service(request):
    return JsonResponse({"service": "User Service", "status": "running"})